// LabAssembler1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
const unsigned __int64 arraySize = 9e+8;
static char sourceArray[arraySize];
static char targetArray[arraySize];

void initSourceArray() {
	for (unsigned int i = 0; i < arraySize; i++) {
		sourceArray[i] = 'q';
	}
}

void startTimer() {
	startTime = std::chrono::high_resolution_clock::now();
}

void finishTimer() {
	endTime = std::chrono::high_resolution_clock::now();
	int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	cout << "Time: " << elapsed_seconds << "ms\n";
}

void checkLoop() {
	cout << "loop"<< endl;
	startTimer();
	for (unsigned int i = 0; i < arraySize; i++) {
		targetArray[i] = sourceArray[i];
	}
	finishTimer();
	cout << "-----------------------" << endl;
}

void checkMemcpy() {
	cout << "memcpy" << endl;
	startTimer();
	::memcpy(targetArray, sourceArray, arraySize);
	finishTimer();
	cout << "-----------------------" << endl;
}

void checkCopy() {
	cout << "copy" << endl;
	startTimer();
	::copy(sourceArray, sourceArray + arraySize, targetArray);
	finishTimer();
	cout << "-----------------------" << endl;
}

extern "C" void movsqcpy();

int main()
{
	initSourceArray();
	checkLoop();
	checkMemcpy();
	checkCopy();
	
	//for (unsigned int i = 0; i < arraySize; i++) {
		//cout << targetArray[i];
	//}
}
