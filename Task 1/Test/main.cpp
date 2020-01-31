//
//  main.cpp
//  Test
//
//  Created by Женя Баян on 13/11/2019.
//  Copyright © 2019 Женя Баян. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

const long dataSize = 100000000;
double *testStorage = new double[dataSize];

chrono::time_point<chrono::high_resolution_clock> start;

void startTimer() {
    start = chrono::high_resolution_clock::now();
}

void stopTimer(string title) {
    chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
    long long elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    
    cout << title << " - " << elapsed << " ms" << endl;
}

void initTestStorage() {
    for (long i = 0; i < dataSize; i++)
    {
        testStorage[i] = 1;
    }
}

// ---- Array methods ----

void getArrayTime() {
    double *secondStorage = new double[dataSize];
    
    startTimer();
    
    for (int i = 0; i < dataSize; i++)
    {
        secondStorage[i] = testStorage[i];
    }
    
    stopTimer("getArrayTime");
}

void getMemcpy() {
    double *secondStorage = new double[dataSize];
    
    startTimer();
    
    memcpy(secondStorage, testStorage, dataSize);
    
    stopTimer("getMemcpy");
}

void getMemMove() {
    double *secondStorage = new double[dataSize];
    
    startTimer();
    
    memmove (secondStorage, testStorage, dataSize);
    
    stopTimer("getMemMove");
}

int main(int argc, const char * argv[]) {
    initTestStorage();
    
    getArrayTime();
    getMemcpy();
    getMemMove();
    
    return 0;
}

