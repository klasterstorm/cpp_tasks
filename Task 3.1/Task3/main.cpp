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

using namespace std;

chrono::time_point<chrono::high_resolution_clock> start;

int testValue = 0;
int testValue2 = 0;

long values[1000000000];

#pragma optimize( "", off )

void t1() {
    testValue += 1;
}
void t2() {
    testValue += 2;
}

void startTimer() {
    start = chrono::high_resolution_clock::now();
}

void stopTimer(string title) {
    chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
    long long elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    cout << title << " - " << elapsed << " ms" << endl;
}

long long stopAndGetTime() {
    chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
    
    return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
}

void setupRandomValues(long blockSize) {
    for (long i = 0; i < blockSize; i++) {
        values[i] = rand() % 2;
    }
}

long long getLoopTime(int numberOfIteration) {
    startTimer();

    for (int i = 0; i < numberOfIteration; i++) {
        testValue += 3;
    }
    
    return stopAndGetTime();
}

long long evenOdd(int numberOfIteration) {
    long long loopTime = getLoopTime(numberOfIteration);
    
    startTimer();

    for (long i = 0; i < numberOfIteration; i++) {
        if (i % 2 == 0) {
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
        if (values[i] == 0) {
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
    
    long maxNumberOfIterations = 1000000000;
    int initialBlockSize = 10000;
    int blockStride = 10;
    
    setupRandomValues(maxNumberOfIterations);
    
    ofstream outputFile;
    outputFile.open ("outputFile.txt");
   
    for (int blockSize = initialBlockSize; blockSize < maxNumberOfIterations; blockSize *= blockStride) {
        outputFile << evenOdd(blockSize) << endl;
    }
    
    cout << endl;
    outputFile << "------" << endl;
    
    for (int blockSize = initialBlockSize; blockSize < maxNumberOfIterations; blockSize *= blockStride) {
        outputFile << randomPath(blockSize) << endl;
    }
    
    outputFile.close();
    
    return 0;
}
