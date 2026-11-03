#include "CPU.h"
#include "Utilities.h"
void CPU::Fetch()
{
    IR = memory.GetCell(PC) + memory.GetCell(PC + 1);
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
    switch (opcode) {
        Utils:: HexToDec(string(1, R));
        case '1':
            memory.SetRegister(R, memory.GetCell(Utils::HexToDec(string(1, X) + string(1, Y))));
            break;
        case '2':
            memory.SetRegister(R, Utils::HexToDec(string(1, X) + string(1, Y)));
            break;
        case '3':
            if (Y == 'F'&& X == 'F') {
                memory.SetScreenBuffer(string(1, memory.GetRegister(R)));
            } else {
                memory.SetCell(Utils::HexToDec(string(1, X) + string(1, Y)), memory.GetRegister(R));
            }
            break;
        case '4':
            memory.SetRegister(X, memory.GetRegister(R));
            break;
        case '5':
            X = Utils::HexToDec(string(1, X));
            Y = Utils::HexToDec(string(1, Y));
            memory.SetRegister(R, ALU::AddInt(memory.GetRegister(X), memory.GetRegister(Y)));
            break;
        case '6':
            X = Utils::HexToDec(string(1, X));
            Y = Utils::HexToDec(string(1, Y));
            memory.SetRegister(R, ALU::AddFloat(memory.GetRegister(X), memory.GetRegister(Y)));
            break;
        case '7':
           X = Utils::HexToDec(string(1, X));
            Y = Utils::HexToDec(string(1, Y));
            memory.SetRegister(R, ALU::Or(memory.GetRegister(X), memory.GetRegister(Y)));
            break;
        case '8':
            X = Utils::HexToDec(string(1, X));
            Y = Utils::HexToDec(string(1, Y));
            memory.SetRegister(R, ALU::And(memory.GetRegister(X), memory.GetRegister(Y)));
            break;
        case '9':
            X = Utils::HexToDec(string(1, X));
            Y = Utils::HexToDec(string(1, Y));
            memory.SetRegister(R, ALU::Xor(memory.GetRegister(X), memory.GetRegister(Y)));
            break;
        case 'A':
            X = Utils::HexToDec(string(1, X));
            memory.SetRegister(R, ALU::RotateRight(Utils::DecToHex(memory.GetRegister(R), 2), X));
            break;
        case 'B':
            if(memory.GetRegister(R) == memory.GetRegister(0)) {
                PC = Utils::HexToDec(string(1, X) + string(1, Y));
            }
            else{}
            break;
    }
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
