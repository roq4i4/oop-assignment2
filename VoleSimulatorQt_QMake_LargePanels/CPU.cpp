#include "CPU.h"
#include "ALU.h"
#include "Utilities.h"
void CPU::Fetch()
{
    string byte1 = memory.GetSingleCell(PC);
    string byte2 = memory.GetSingleCell(PC + 1);
    IR = byte1 + byte2;
    PC += 2;
}

bool CPU::Decode()
{
    opcode = IR[0];
    switch (opcode) {
        case '1':
            R  =IR[1];
            X = IR[2];
            Y = IR[3];
            return true;
        case '2':
            R  =IR[1];
            X = IR[2];
            Y = IR[3];
            return true;
        case '3':
            R  =IR[1];
            X = IR[2];
            Y = IR[3];
            return true;
        case '4':
            R  =IR[2];
            X = IR[3];
            Y = 0;
            return true;
        case '5':
            R  =IR[1];
            X = IR[2];
            Y = IR[3];
            return true;
        case '6':
            R  =IR[1];
            X = IR[2];
            Y = IR[3];
            return true;
        case '7':
            R  =IR[1];
            X = IR[2];
            Y = IR[3];
            return true;
        case '8':
            R  =IR[1];
            X = IR[2];
            Y = IR[3];
            return true;
        case '9':
            R  =IR[1];
            X = IR[2];
            Y = IR[3];
            return true;
        case 'A':
            R  =IR[1];
            X = IR[3];
            Y = 0;
            return true;
        case 'B':
            R  =IR[1];
            X = IR[2];
            Y = IR[3];
            return true;
        case 'C':
            halted = true;
            return true;
        default:
            return false;
    }
}

void CPU::Execute()
{
    int regR = Utils::HexToDec(string(1, R));
    switch (opcode) {
        case '1':{
            int addr = Utils::HexToDec(string(1, X) + string(1, Y));
            memory.SetRegister(regR, Utils::HexToDec(memory.GetCell(addr)));
            break;
        }
        case '2':{
            int value = Utils::HexToDec(string(1, X) + string(1, Y));
            memory.SetRegister(regR, value);
            break;
        }
        case '3':{
            if (Y == 'F'&& X == 'F') {
                memory.SetScreenBuffer(memory.GetRegister(regR));
            } else {
                int addr = Utils::HexToDec(string(1, X) + string(1, Y));
                memory.SetCell(addr, Utils::HexToDec(memory.GetRegister(regR)));
            }
            break;
        }
        case '4':{
            int targetReg = Utils::HexToDec(string(1, X));
            int sourceReg = Utils::HexToDec(string(1, R));
            memory.SetRegister(targetReg, Utils::HexToDec(memory.GetCell(sourceReg)));
            break;
        }
        case '5':{
            int regX = Utils::HexToDec(string(1, X));
            int regY = Utils::HexToDec(string(1, Y));
            memory.SetRegister(regR, ALU::AddInt(Utils::HexToDec(memory.GetRegister(regX)), Utils::HexToDec(memory.GetRegister(regY))));
            break;
        }
        case '6':{
            int regX = Utils::HexToDec(string(1, X));
            int regY = Utils::HexToDec(string(1, Y));
            memory.SetRegister(regR, ALU::AddFloat(Utils::HexToDec(memory.GetRegister(regX)), Utils::HexToDec(memory.GetRegister(regY))));
            break;
        }
        case '7':{
            int regX = Utils::HexToDec(string(1, X));
            int regY = Utils::HexToDec(string(1, Y));
            memory.SetRegister(regR, ALU::Or(Utils::HexToDec(memory.GetRegister(regX)), Utils::HexToDec(memory.GetRegister(regY))));
            break;
        }
        case '8':{
            int regX = Utils::HexToDec(string(1, X));
            int regY = Utils::HexToDec(string(1, Y));
            memory.SetRegister(regR, ALU::And(Utils::HexToDec(memory.GetRegister(regX)), Utils::HexToDec(memory.GetRegister(regY))));
            break;
        }
        case '9':{
            int regX = Utils::HexToDec(string(1, X));
            int regY = Utils::HexToDec(string(1, Y));
            memory.SetRegister(regR, ALU::Xor(Utils::HexToDec(memory.GetRegister(regX)), Utils::HexToDec(memory.GetRegister(regY))));
            break;
        }
        case 'A':{
            int times = Utils::HexToDec(string(1, X));
            memory.SetRegister(regR, ALU::RotateRight(Utils::HexToDec(memory.GetRegister(regR)), times));
            break;
        }
        case 'B':{
            if(memory.GetRegister(regR) == memory.GetRegister(0)) {
                PC = Utils::HexToDec(string(1, X) + string(1, Y));
            }
            break;
        }
        case 'C':{
            halted = true;
            break;
        }
    }
}

CPU::CPU(Memory& mem) : memory(mem)
{
    PC = 0;
    IR = "";
    halted = false;
}

bool CPU::IsHalted()
{
    if (halted){return true;}
    else{return false; }
}

int CPU::GetPC()
{
    return PC;
}

void CPU::SetPC(int pc)
{
    PC = pc;
}

string CPU::GetIR()
{
    return IR;
}

void CPU::SetIR(string ir)
{
    IR = ir;
}

string CPU::GetErrorMsg()
{
    return errormsg;
}

StepResult CPU::Step()
{
    if (halted) {
        return StepResult::HALTED;
    }
    Fetch();
    if (!Decode()) {
        if (PC < 0 || PC >= 256) {
            return StepResult::PC_OUT_OF_RANGE;
        }
        return StepResult::INVALID_INSTRUCTION;
    }
    Execute();
    if (halted) {
        return StepResult::HALTED;
    }
    return StepResult::OK;
}

void CPU::Reset()
{
    memory.Reset();
    PC = 0;
    IR = "";
    halted = false;
}
