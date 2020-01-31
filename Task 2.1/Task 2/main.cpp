//
//  main.cpp
//  Task 2
//
//  Created by Женя Баян on 30/01/2020.
//  Copyright © 2020 -. All rights reserved.
//

#include "pch.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>

#include <ctime>
#include <chrono>

#include <fstream>
#include <string>
#include <iostream>

//----
#ifndef CPUID_H
#define CPUID_H

#ifdef _WIN32
#include <limits.h>
#include <intrin.h>
typedef unsigned __int32  uint32_t;

#else
#include <stdint.h>
#endif
//------

class CPUID {
  uint32_t regs[4];

public:
  explicit CPUID(unsigned i) {
#ifdef _WIN32
    __cpuid((int *)regs, (int)i);

#else
    asm volatile
      ("cpuid" : "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])
       : "a" (i), "c" (0));
    // ECX is set to zero for CPUID function 4
#endif
  }

  const uint32_t &EAX() const {return regs[0];}
  const uint32_t &EBX() const {return regs[1];}
  const uint32_t &ECX() const {return regs[2];}
  const uint32_t &EDX() const {return regs[3];}
};

#endif // CPUID_H

using namespace std;

template <typename T>
std::string NumberToString(T Number)
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

#include <limits.h>
#include <x86intrin.h>

void printCacheInfo() {
    for (int i = 1; i < 4; i++) {
        int CPUInfo[4];
        CPUID cpuid(4);

        int nMaxThread = (CPUInfo[0] & 0x03ffc000) >> 14;
        int nSysLineSize = (CPUInfo[1] & 0x0fff);
        int nPhysicalLinePartitions = (CPUInfo[1] & 0x03ff000) >> 12;
        int nWaysAssociativity = (CPUInfo[1]) >> 22;
        int nNumberSets = CPUInfo[2];
        int nCacheSize = (nWaysAssociativity + 1) * (nPhysicalLinePartitions + 1) * (nSysLineSize + 1) * (nNumberSets + 1);

        cout << "Cache level : " << i << endl;
        cout << "Max thread : " << nMaxThread + 1 << endl;
        cout << "Line size : " << nSysLineSize + 1 << endl;
        cout << "Partitions : " << nPhysicalLinePartitions + 1 << endl;
        cout << "Ways : " << nWaysAssociativity + 1 << endl;
        cout << "Sets : " << nNumberSets + 1 << endl;
        cout << "Chache size : " << nCacheSize << endl;
        cout << " ----------------------------- " << endl;
    }
}

int main(int argc, char **argv)
{
    printCacheInfo();

    startTestCacheSizeFromStride();

    std::cin.get();
    return 0;
}
