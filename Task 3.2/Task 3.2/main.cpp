//
//  main.cpp
//  Task 3.2
//
//  Created by Женя Баян on 31/01/2020.
//  Copyright © 2020 -. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
chrono::time_point<chrono::high_resolution_clock> start;
std::clock_t c_start;

int testValue = 0;
int x = 0;
int numberOfIterations = 1000000;

#pragma optimize( "", off )

void t0() { testValue += 1; }
void t1() { testValue += 2; }
void t2() { testValue += 3; }
void t3() { testValue += 4; }
void t4() { testValue += 5; }
void t5() { testValue += 6; }
void t6() { testValue += 7; }
void t7() { testValue += 8; }
void t8() { testValue += 9; }
void t9() { testValue += 10; }

#pragma optimize( "", on )

void startAlternativeTimer() {
    c_start = std::clock();
}

void stopAlternativeTimer() {
    std::clock_t c_end = std::clock();
    
    long double time_elapsed_ms = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
    std::cout << "CPU time used: " << time_elapsed_ms << " ms\n";
}

void startTimer() {
    start = chrono::high_resolution_clock::now();
}

void stopTimer(string title) {
    chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
    long long elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    cout << title << " - " << elapsed << " ns" << endl;
}

long long stopAndGetTime() {
    chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
}

int getRandomValue(int maxValue) {
    return rand() % (maxValue + 1);
}

#pragma optimize( "", off )

typedef void (*FunctionsArray) ();

void getFunctionsTime(FunctionsArray functions[], int size) {
    
    startTimer();
    
    for (int i = 0; i < numberOfIterations; i++) {
        int randomValue = getRandomValue(size);
        
        functions[randomValue]();
    }
    
    stopTimer("");
}

void switchCaseTest4() {

    startTimer();
    
    for (int i = 0; i < numberOfIterations; i++) {
        int randomValue = getRandomValue(3);
        
        if (randomValue == 0) { t0(); }
        else if (randomValue == 1) { t1(); }
        else if (randomValue == 2) { t2(); }
        else if (randomValue == 3) { t3(); }
    }
    
    stopTimer("4");
}

void switchCaseTest7() {
    startTimer();

    for (int i = 0; i < numberOfIterations; i++) {
        int randomValue = getRandomValue(1000);
        
        if (randomValue == 0) { t0(); }
        else if (randomValue == 1) { t1(); }
        else if (randomValue == 2) { t2(); }
        else if (randomValue == 3) { t3(); }
        else if (randomValue == 4) { t4(); }
        else if (randomValue == 5) { t5(); }
        else if (randomValue == 6) { t6(); }
    }

    stopTimer("7");
}

void switchCaseTest10() {
    startTimer();

    for (int i = 0; i < numberOfIterations; i++) {
        int randomValue = getRandomValue(9);
    
        if (randomValue == 0) { t0(); }
        else if (randomValue == 1) { t1(); }
        else if (randomValue == 2) { t2(); }
        else if (randomValue == 3) { t3(); }
        else if (randomValue == 4) { t4(); }
        else if (randomValue == 5) { t5(); }
        else if (randomValue == 6) { t6(); }
        else if (randomValue == 7) { t7(); }
        else if (randomValue == 8) { t8(); }
        else if (randomValue == 9) { t9(); }
    }

    stopTimer("10");
}

void functionArray4() {
    
    FunctionsArray functions[] =
     {
         t0,
         t1,
         t2,
         t3,
     };
    
    getFunctionsTime(functions, 3);
}

void functionArray7() {
    
    FunctionsArray functions[] =
     {
         t0,
         t1,
         t2,
         t3,
         t4,
         t5,
         t6
     };
    
    getFunctionsTime(functions, 6);
}

void functionArray10() {
    
    FunctionsArray functions[] =
     {
         t0,
         t1,
         t2,
         t3,
         t4,
         t5,
         t6,
         t7,
         t8,
         t9
     };
    
    getFunctionsTime(functions, 9);
}

// ----- MAIN -------

void switchCaseTest(int numberOfAddresses) {

    for (int aNumber = 0; aNumber < numberOfAddresses; aNumber++) {
        
        startTimer();
        
        for (int i = 0; i < numberOfIterations; i++) {
            
            int randomValue = getRandomValue(aNumber);

            if (randomValue == 0) { t0(); }
            else if (randomValue == 1) { t1(); }
            else if (randomValue == 2) { t2(); }
            else if (randomValue == 3) { t3(); }
            else if (randomValue == 4) { t4(); }
            else if (randomValue == 5) { t5(); }
            else if (randomValue == 6) { t6(); }
            else if (randomValue == 7) { t7(); }
            else if (randomValue == 8) { t8(); }
            else if (randomValue == 9) { t9(); }
        }
        
        stopTimer("");
    }
}

#pragma optimize( "", on )

int main(int argc, const char * argv[]) {

    cout << endl << "switchCase" << endl << endl;
    switchCaseTest4();
    switchCaseTest7();
    switchCaseTest10();

    cout << endl << "functionArray" << endl << endl;
    functionArray4();
    functionArray7();
    functionArray10();
//
//    switchCaseTest(10);

    return 0;
}
