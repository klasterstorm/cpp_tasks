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
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

double *testStorage;
int manyTimes = 1000;

chrono::time_point<chrono::high_resolution_clock> start;

void startTimer() {
    start = chrono::high_resolution_clock::now();
}

void stopTimer(string title) {
    chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
    long long elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    cout << title << " - " << elapsed << " ms" << endl;
}

long long stopAndGetTime() {
    chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
    
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

void initTestStorage(int blockSize) {
    testStorage = new double[blockSize];
    
    for (long int i = 0; i < blockSize; i++)
    {
        testStorage[i] = 1;
    }
}

// ---- Array methods ----

long long getArrayTime(int blockSize) {
    double *secondStorage = new double[blockSize];
    
    startTimer();
    for (int i = 0; i < manyTimes; i++) {
        for (long int i = 0; i < blockSize; i++)
        {
            secondStorage[i] = testStorage[i];
        }
    }
    
    return stopAndGetTime() / manyTimes;
}

long long getMemcpy(int blockSize) {
    double *secondStorage = new double[blockSize];
    
    startTimer();
    
    for (int i = 0; i < manyTimes; i++) {
        memcpy(secondStorage, testStorage, blockSize);
    }
    
    return stopAndGetTime() / manyTimes;
}

long long getMemMove(int blockSize) {
    double *secondStorage = new double[blockSize];
    
    startTimer();
    
    for (int i = 0; i < manyTimes; i++) {
        memmove(secondStorage, testStorage, blockSize);
    }
    
    return stopAndGetTime() / manyTimes;
}

int getDataWeight(int blockSize) {
    return blockSize * 8 / 1024 / 1024;
}

int main(int argc, const char * argv[]) {
    
    ofstream outputFile;
    outputFile.open ("output.txt");
    
    for (int blockSize = 1000000; blockSize < 130000000; blockSize *= 2) {
        initTestStorage(blockSize);
        
        outputFile << "Loop" << " " << getDataWeight(blockSize) << " " << getArrayTime(blockSize) << endl;
        outputFile << "Memcpy" << " " << getDataWeight(blockSize) << " " << getMemcpy(blockSize) << endl;
        outputFile << "MemMove" << " " << getDataWeight(blockSize) << " " << getMemMove(blockSize) << endl;
    }
    
    outputFile.close();
    
    return 0;
}

//с частичным учителейм обучение

