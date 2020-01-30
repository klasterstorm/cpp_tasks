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

void t1() {
    int y = 200 * 100 / 200;
}

void t2() {
    int x = 4393 * 484 + 32;
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
    long elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Array time > " << elapsed << "ms\n";
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
    long elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Array time > " << elapsed << "ms\n";
}

int main(int argc, const char * argv[]) {
   
    test();
    test2();
    return 0;
}
