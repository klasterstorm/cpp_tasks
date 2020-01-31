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

int value1 = 0;
int value2 = 0;

void t1() {
    value1 += 1;
}

void t2() {
    value2 += 1;
}

void test() {
    chrono::time_point<chrono::high_resolution_clock> start, end;
    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < numberOfIteration; i++) {
        if (i % 2 == 0) {
            t1();
        }
        else {
            t2();
        }
    }
    
    end = chrono::high_resolution_clock::now();
    long elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "% time > " << elapsed << "ms\n";
}

void test2() {
    chrono::time_point<chrono::high_resolution_clock> start, end;
    start = chrono::high_resolution_clock::now();
 
    for (int i = 0; i < numberOfIteration; i++) {
        if ((rand() % 2) == 0) {
            t1();
        }
        else {
            t2();
        }
    }
    
    end = chrono::high_resolution_clock::now();
    long elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "rand time > " << elapsed << "ms\n";
}

int main(int argc, const char * argv[]) {
   
    test();
    test2();
    return 0;
}

//3.2 Косвенный переход
// Массив указателей
// И мы переходим по функциям в массиве
// Динамический массив (увеличиваем размер массива по мере надобности)
