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
const long dataSize = 123000000;

void testArray() {
    
}

void getArrayTime() {
    
    double *firstStorage = new double[dataSize];
    double *secondStorage = new double[dataSize];
    
    for (long i = 0; i < dataSize; i++)
    {
        firstStorage[i] = 1;
    }
    
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < dataSize; i++)
    {
        secondStorage[i] = firstStorage[i];
    }
    
    end = std::chrono::high_resolution_clock::now();
    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Array time > " << elapsed << "ms\n";
}

void getMemcpy() {
    
    double *firstStorage = new double[dataSize];
    double *secondStorage = new double[dataSize];
    
    for (long i = 0; i < dataSize; i++)
    {
        firstStorage[i] = 1;
    }
    
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    
    memcpy(secondStorage, firstStorage, dataSize);
    
    end = std::chrono::high_resolution_clock::now();
    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Memcpy time > " << elapsed << "ms\n";
}

void getMemMove() {
    
    double *firstStorage = new double[dataSize];
    double *secondStorage = new double[dataSize];
    
    for (long i = 0; i < dataSize; i++)
    {
        firstStorage[i] = 1;
    }
    
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    
    memmove (secondStorage, firstStorage, dataSize);
    
    end = std::chrono::high_resolution_clock::now();
    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "MemMove time > " << elapsed << "ms\n";
}

int main(int argc, const char * argv[]) {
    getArrayTime();
    getMemcpy();
    getMemMove();
    
    return 0;
}


//

