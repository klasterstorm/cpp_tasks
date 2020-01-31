// Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <ctime>
#include <chrono>

using namespace std;

template <typename T>
std::string NumberToString(T Number)
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

#include <limits.h>
#include <intrin.h>
std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
POINT op;
HWND hWnd = GetConsoleWindow();
HDC hDC = GetDC(hWnd);

const unsigned __int64 arraySize = 1e+8;
static int sourceArray[arraySize];
int offsetX, offsetY;
float scaleX, scaleY;
int maxX, maxY;
int valueOfDivisionX, valueOfDivisionY;

// const uint32_t &EAX() const { return regs[0]; }
// const uint32_t &EBX() const { return regs[1]; }
// const uint32_t &ECX() const { return regs[2]; }
// const uint32_t &EDX() const { return regs[3]; }

//  0xffc00000 -> 11111111110000000000000000000000
//  0x3ff800   -> 1111111111100000000000
//  0x7ff      -> 11111111111

//  0x1C0003F  -> 111000000000 0000000111 1110000000   (ebx)
//  0x1C004122 -> 11100 000 0 0 0000 100000100100 010000 (eax)
//  0x3F       -> 111111 (ecx)

void startTimer() {
	startTime = std::chrono::high_resolution_clock::now();
}

int getFinishTimerNano() {
	endTime = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
}

int getFinishTimerMilli() {
	endTime = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}

int getNuberOfInt(int n) {
	if (n == 0) return 1;
	int cnt = 0;
	while (n)
	{
		n /= 10;
		cnt++;
	}
	return cnt;
}

void textOutFromInt(HDC hDC, int x, int y, int n) {
	wchar_t buffer[256];
	wsprintfW(buffer, L"%d", n);
	TextOut(hDC, x, y, buffer, getNuberOfInt(n));
}

void textOutFromString(HDC hDC, int x, int y, string s) {
	wchar_t buffer[256];
	wsprintfW(buffer, L"%s", s);
	TextOut(hDC, x, y, buffer, 2);
}

void printCacheInfo() {
	for (int i = 1; i < 4; i++) {
		int CPUInfo[4];
		__cpuidex(CPUInfo, 4, i);

		int nCacheType = (CPUInfo[0] & 0x1f);
		int nCacheLevel = (CPUInfo[0] & 0xe0) >> 5;
		int bSelfInit = (CPUInfo[0] & 0x100) >> 8;
		int bFullyAssociative = (CPUInfo[0] & 0x200) >> 9;
		int nMaxThread = (CPUInfo[0] & 0x03ffc000) >> 14;
		int nSysLineSize = (CPUInfo[1] & 0x0fff);
		int nPhysicalLinePartitions = (CPUInfo[1] & 0x03ff000) >> 12;
		int nWaysAssociativity = (CPUInfo[1]) >> 22;
		int nNumberSets = CPUInfo[2];
		int nCacheSize = (nWaysAssociativity + 1) * (nPhysicalLinePartitions + 1) * (nSysLineSize + 1) * (nNumberSets + 1);

		cout << "Cache level : " << i << endl;
		cout << "Max thread : " << nMaxThread + 1 << endl;
		cout << "Line size : " << nSysLineSize + 1 << endl;
		cout << "Partitions : " << nPhysicalLinePartitions + 1 << endl;
		cout << "Ways : " << nWaysAssociativity + 1 << endl;
		cout << "Sets : " << nNumberSets + 1 << endl;
		cout << "Chache size : " << nCacheSize << endl;
		cout << " ----------------------------- " << endl;
	}
}

void printGraph(LPCWSTR nameY, int nameSizeY, LPCWSTR nameX, int nameSizeX) {

	SelectObject(hDC, GetStockObject(WHITE_PEN)); //Выбираем перо WHITE_PEN в контекст

	MoveToEx(hDC, 0 + offsetX, 0 + offsetY, &op);
	LineTo(hDC, (maxX * scaleX) + offsetX, 0 + offsetY);
	TextOut(hDC, ((maxX / 2)* scaleX) + offsetX, 30 + offsetY, nameX, nameSizeX);
	for (int i = 0; i <= maxX; i += valueOfDivisionX) {
		if (i >= maxX) break;
		textOutFromInt(hDC, i*scaleX + offsetX, 10 + offsetY, i);
	}

	MoveToEx(hDC, 0 + offsetX, 0 + offsetY, &op);
	LineTo(hDC, 0 + offsetX,  - (maxY*scaleY) + offsetY);
	TextOut(hDC, -120 + offsetX, ((-maxY / 2)*scaleY) + offsetY, nameY, nameSizeY);
	for (int i = 0; i <= maxY; i += valueOfDivisionY) {
		if (i >= maxY) break;
		textOutFromInt(hDC, -30 + offsetX,  - i*scaleY + offsetY, i);
	}

}

void changeGraphValue(int x, int y) {
	if (x > maxX || y  > maxY) return;
	static int X = 0, Y = 0;
	static bool first = true;
	if (!first) {
		MoveToEx(hDC, X*scaleX + offsetX, -Y * scaleY + offsetY, &op);
		LineTo(hDC, x*scaleX + offsetX, -y*scaleY + offsetY);
	}
	X = x;
	Y = y;
	first = false;
	return;
}

void startTestCacheTimeFromStride() {

	offsetX = 200;
	offsetY = 400;
	scaleX = 1;
	scaleY = 3;
	maxX = 400;
	maxY = 90;
	valueOfDivisionX = 64;
	valueOfDivisionY = 10;
	printGraph(L"time (ms)", 9, L"stride", 6);

	int manyTimes = 10;

	for (int stride = 16; stride < 512; stride += 2) {
		int allTime = 0;
		for (int times = 0; times < manyTimes; times++) {
			startTimer();
			for (int i = 0; i < arraySize; i += stride) {
				sourceArray[i]++;
			}
			allTime += getFinishTimerMilli();
		}
		changeGraphValue(stride, allTime/manyTimes);
	}
}

void startTestCacheSizeFromStride() {

	offsetX = 200;
	offsetY = 400;
	scaleX = 1;
	scaleY = 0.01;
	maxX = 700;
	maxY = 32000;
	valueOfDivisionX = 64;
	valueOfDivisionY = 2000;
	printGraph(L"time (ns)",9, L"array size (kB)", 16);

	int manyTimes = 10000;

	for (int blockSize = 1; blockSize < 1000000; blockSize += 300) {

		int *arrayTest = new int[blockSize];
		int allTime = 0;
		for (int times = 0; times < manyTimes; times++) {
			startTimer();
			for (int i = 0; i < blockSize; i += 16) {
				arrayTest[i]++;
			}
			allTime += getFinishTimerNano();
		}
		changeGraphValue((blockSize*sizeof(int)/1000), allTime / manyTimes);
	}
}

int main(int argc, char **argv)
{
	printCacheInfo();

	//startTestCacheTimeFromStride();
	//startTestCacheSizeFromStride();

	ReleaseDC(hWnd, hDC);
	std::cin.get();
	return 0;
}



