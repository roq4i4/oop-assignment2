#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <Memory.cpp>
using namespace std;

enum class StepResult { OK, HALTED, INVALID_INSTRUCTION, PC_OUT_OF_RANGE };

class CPU {
    int PC;
    string IR;
    bool halted;
    Memory memory;
    char opcode, X, Y, R;
    string errormsg = "error: invalid instruction";
    void Fetch();
    bool Decode();
    void Execute();
    public:
    int GetPC();
    void SetPC(int pc);
    string GetIR();
    void SetIR(string ir);
    string GetErrorMsg();
    StepResult Step();
    void Reset();
};

#endif