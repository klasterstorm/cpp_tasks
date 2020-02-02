//
//  main.cpp
//  Task3
//
//  Created by Женя Баян on 28/01/2020.
//  Copyright © 2020 -. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
#pragma optimize( "", off )

using namespace std;

chrono::time_point<chrono::high_resolution_clock> start;

int testValue = 0;
int testValue2 = 10;

int randomValues[100000000];
int evenOddValues[100000000];


void t1() {
    testValue += 1;
    testValue2 *= 12 + 4;
    testValue2 *= testValue;
}

void t2() {
    testValue2 += 1;
    testValue *= 12 + 4;
    testValue *= testValue;
}

void startTimer() {
    start = chrono::high_resolution_clock::now();
}

long long stopAndGetTime() {
    chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
    
    return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
}

void setupRandomValues(long blockSize) {
    for (long i = 0; i < blockSize; i++) {
        randomValues[i] = rand() % 2;
    }
}

void setupEvenOddValues(long blockSize) {
    for (long i = 0; i < blockSize; i++) {
        evenOddValues[i] = i % 2;
    }
}

long long getLoopTime(int numberOfIteration) {
    startTimer();

    for (int i = 0; i < numberOfIteration; i++) {
        testValue += 1;
    }
    
    return stopAndGetTime();
}

long long evenOdd(int numberOfIteration) {
    long long loopTime = getLoopTime(numberOfIteration);
    
    startTimer();

    for (long i = 0; i < numberOfIteration; i++) {
        if (evenOddValues[i] == 0) {
            t1();
        }
        else {
            t2();
        }
    }
    
    long long finishTime = stopAndGetTime() - loopTime;
    
    cout << finishTime << " - evenOdd " << numberOfIteration << endl;
    return finishTime;
}

long long randomPath(int numberOfIteration) {
    long long loopTime = getLoopTime(numberOfIteration);
    
    startTimer();
 
    for (long i = 0; i < numberOfIteration; i++) {
        if (randomValues[i] == 0) {
            t1();
        }
        else {
            t2();
        }
    }
    
    long long finishTime = stopAndGetTime() - loopTime;
    
    cout << finishTime << " - randomPath " << numberOfIteration << endl;
    return finishTime;
}

#pragma optimize( "", on )

int main(int argc, const char * argv[]) {
    
    long maxNumberOfIterations = 2000000;
    int initialBlockSize = 1000;
    
    setupRandomValues(maxNumberOfIterations);
    setupEvenOddValues(maxNumberOfIterations);
    
    ofstream outputFile;
    outputFile.open ("Task3.1_output.txt");
   
    for (int blockSize = initialBlockSize; blockSize < maxNumberOfIterations; blockSize *= 2) {
        outputFile << "evenOdd" << " " << blockSize << " " << evenOdd(blockSize) << endl;
    }
    
    cout << endl;
    
    for (int blockSize = initialBlockSize; blockSize < maxNumberOfIterations; blockSize *= 2) {
        outputFile << "randomPath" << " " << blockSize << " " << randomPath(blockSize) << endl;
    }
    
    outputFile.close();
    
    return 0;
}
