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

    // Functions used by the graphical interface
    std::string LoadProgram(const std::string& filename, int startAddress);
    void SetRegisterValue(int reg, int value);
    void SetMemoryValue(int address, int value);
    std::string RunOneStep();
    std::string RunAllSteps();
    std::string GetRegistersText();
    std::string GetMemoryText();
    std::string GetScreenText();
    std::string GetPCText();
    std::string GetIRText();
    bool IsProgramLoaded();

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
