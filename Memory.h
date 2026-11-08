#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
using namespace std;
class Memory {
    int cells[256];
    int registers[16];
    string screenBuffer;
    public:
    int GetCell(int addr);
    void SetCell(int addr, int value);
    int GetRegister(int r);
    void SetRegister(int r, int value);
    void SetScreenBuffer(string buffer);
    void DisplayMemory(ostream out, int pc);
    void DisplayRegisters(ostream out);
    void DisplayScreen();
    void Reset();
};

#endif