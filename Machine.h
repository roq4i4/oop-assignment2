#ifndef MACHINE_H
#define MACHINE_H

#include <string>
#include "Utilities.h"
#include "ALU.h"
#include "Memory.h"
#include "CPU.h"

class Machine
{
private:
    Memory memory;
    CPU cpu;
    bool programLoaded;
    static const int MAX_STEPS = 10000;

public:
    Machine();

    void Run();
    void ShowMenu();
    void LoadProgramFromFile();
    void OverwriteRegister();
    void OverwriteMemory();
    void RunProgram(bool stepMode);
    void DisplayState();
    int ReadHexInput(std::string prompt, int minVal, int maxVal);
    void Reset();
};

#endif