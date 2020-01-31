//
//  main.cpp
//  Task 2.2
//
//  Created by Женя Баян on 30/01/2020.
//  Copyright © 2020 -. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

const unsigned int arraySize = 1e+8;

std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

void startTimer() {
    startTime = std::chrono::high_resolution_clock::now();
}

long getTimerValue() {
    endTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
}

void test() {
    static int sourceArray[arraySize];
    int manyTimes = 10;
    
    for (int stride = 16; stride < 512; stride += 2) {
        int allTime = 0;
        for (int times = 0; times < manyTimes; times++) {
            startTimer();
            for (int i = 0; i < arraySize; i += stride) {
                sourceArray[i]++;
            }
            allTime += getTimerValue();
        }
        
        cout << allTime/manyTimes << " " << stride << endl;
    }
    
}

int main(int argc, const char * argv[]) {

    test();
    return 0;
}
