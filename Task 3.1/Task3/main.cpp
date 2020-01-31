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

using namespace std;

long numberOfIteration = 10000000;

chrono::time_point<chrono::high_resolution_clock> start;

int testValue = 0;

void t1() { testValue += 1; }
void t2() { testValue += 2; }

void startTimer() {
    start = chrono::high_resolution_clock::now();
}

void stopTimer(string title) {
    chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
    long long elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    
    cout << title << " - " << elapsed << " ms" << endl;
}

void evenOdd() {
    startTimer();

    for (int i = 0; i < numberOfIteration; i++) {
        if (i % 2 == 0) {
            t1();
        }
        else {
            t2();
        }
    }
    
    stopTimer("evenOdd");
}

void randomPath() {
    startTimer();
 
    for (int i = 0; i < numberOfIteration; i++) {
        if ((rand() % 2) == 0) {
            t1();
        }
        else {
            t2();
        }
    }
    
    stopTimer("randomPath");
}

int main(int argc, const char * argv[]) {
   
    evenOdd();
    randomPath();
    
    return 0;
}
