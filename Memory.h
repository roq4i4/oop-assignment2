#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
#include "Utilities.h"
using namespace std;
class Memory {
    int cells[256];
    int registers[16];
    string screenBuffer;
    public:
    Memory();
    string GetCell(int addr);
    string GetSingleCell(int addr);
    void SetCell(int addr, int value);
    void SetSingleCell (int addr, int value);
    string GetRegister(int r);
    void SetRegister(int r, int value);
    void SetScreenBuffer(string buffer);
    void DisplayMemory(ostream& out, int pc);
    void DisplayRegisters(ostream& out);
    void DisplayScreen(ostream& out);
    void Reset();
};

#endif