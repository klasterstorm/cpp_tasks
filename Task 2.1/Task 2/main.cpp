#include <algorithm>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <limits.h>
#include <x86intrin.h>
typedef unsigned __int32  uint32_t;
#else
#include <stdint.h>
#endif

using namespace std;

#define MAX_INTEL_TOP_LVL 4

class CPUID {
    uint32_t regs[4];

    public:
    explicit CPUID(unsigned funcId, unsigned subFuncId) {
#ifdef _WIN32
        __cpuidex((int *)regs, (int)funcId, (int)subFuncId);

#else
        asm volatile
            ("cpuid" : "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])
             : "a" (funcId), "c" (subFuncId));
        // ECX is set to zero for CPUID function 4
#endif
    }

    const uint32_t &EAX() const {return regs[0];}
    const uint32_t &EBX() const {return regs[1];}
    const uint32_t &ECX() const {return regs[2];}
    const uint32_t &EDX() const {return regs[3];}
};


int
get_intel_l3_info(unsigned *size, unsigned *assoc, unsigned *linesize) {
    int regs[4];
    int i;

    __cpuid(regs, 0); /* Maximum Input Value */
    int max_leaf = regs[0];
    if (max_leaf < 2) {
        return -1; /* no way to find L3 cache info */
    }

    __cpuid(regs, 1); /* Additional Information */
    int family = (regs[0] >> 8) & 0xF;
    int model = (regs[0] >> 4) & 0xF;

    __cpuid(regs, 2); /* Cache and TLB Information */

    regs[0] &= 0xFFFFFF00; /* least significant byte of EAX is invalid */
    for (i = 0; i < 4; i++) {
        if (regs[i] < 0) { /* invalid if most significant bit set */
            regs[i] = 0;
        }
    }

    unsigned char *descriptors = (unsigned char *) regs;

    const int kb = 1024;
    const int mb = 1024 * kb;

#define RETINFO(s, a, l) *size = (s); *assoc = (a); *linesize = (l); return 0

    int use_leaf_4 = 0;
    for (i = 0; i < 32; i++) {
        switch(descriptors[i]) {
        case 0x22: RETINFO(512 * kb, 4, 64);
        case 0x23: RETINFO(1 * mb, 8, 64);
        case 0x25: RETINFO(2 * mb, 8, 64);
        case 0x29: RETINFO(4 * mb, 8, 64);
        case 0x40: RETINFO(0, 0, 0); /* no L3 cache */
        case 0x46: RETINFO(4 * mb, 4, 64);
        case 0x47: RETINFO(8 * mb, 8, 64);
        case 0x49:
            if (family == 0x0F && model == 0x06) {
                RETINFO(4 * mb, 16, 64);
            }
            break;
        case 0x4A: RETINFO(6 * mb, 12, 64);
        case 0x4B: RETINFO(8 * mb, 16, 64);
        case 0x4C: RETINFO(12 * mb, 12, 64);
        case 0x4D: RETINFO(16  * mb, 16, 64);
        case 0xD0: RETINFO(512 * kb, 4, 64);
        case 0xD1: RETINFO(1 * mb, 4, 64);
        case 0xD6: RETINFO(1 * mb, 8, 64);
        case 0xD7: RETINFO(2 * mb, 8, 64);
        case 0xD8: RETINFO(4 * mb, 8, 64);
        case 0xDC: RETINFO(1 * mb + 512 * kb, 12, 64);
        case 0xDD: RETINFO(3 * mb, 12, 64);
        case 0xDE: RETINFO(6 * mb, 12, 64);
        case 0xE2: RETINFO(2 * mb, 16, 64);
        case 0xE3: RETINFO(4 * mb, 16, 64);
        case 0xE4: RETINFO(8 * mb, 16, 64);
        case 0xEA: RETINFO(12 * mb, 24, 64);
        case 0xEB: RETINFO(18 * mb, 24, 64);
        case 0xEC: RETINFO(24 * mb, 24, 64);

        case 0xFF:
            use_leaf_4 = 1;
            break;
        }
    }

    if (!use_leaf_4 || max_leaf < 4) {
        return -1; /* failed, no L3 info found */
    }

    i = 0;
    while(1) {
        __cpuidex(regs, 4, i); /* Deterministic Cache Parameters */
        if ((regs[0] & 0x1F) == 0) {
            return RETINFO(0, 0, 0); /* no L3 cache */
        }
        if (((regs[0] >> 5) & 0x7) == 3) {
            int lsize = (regs[1] & 0xFFF) + 1;
            int partitions = ((regs[1] >> 12) & 0x3FF) + 1;
            int ways = ((regs[1] >> 22) & 0x3FF) + 1;
            int sets = regs[2] + 1;
            RETINFO(ways * partitions * lsize * sets,
                ways, lsize);
        }
        i++;
    }
}
