#ifndef MACHINE_H
#define MACHINE_H

#include <string>
#include "CPU.h"
#include "Memory.h"
#include "RegisterFile.h"
#include "ProgramLoader.h"
#include "InstructionDecoder.h"
#include "ALU.h"

class Machine
{
private:
    CPU cpu;
    Memory memory;
    RegisterFile regs;
    ProgramLoader loader;
    ALU alu;
    InstructionDecoder decoder;
    bool programLoaded;

public:
    Machine();

    void ShowMenu();
    bool LoadProgramFromFile(string filename, int startAddr);
    void OverwriteRegister(int reg, int value);
    void OverwriteMemory(int addr, int value);
    void RunAll();
    void RunStep();
    void FetchDecodeExecute();
    void DisplayState();
    bool ValidateStartAddress(int addr);
    void Reset();
    void Shutdown();
};

#endif