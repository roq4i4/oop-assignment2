#include <iostream>
#include <sstream>
#include "Machine.h"

using namespace std;

Machine::Machine() : memory(), cpu(memory), programLoaded(false)
{
}

int Machine::ReadHexInput(string prompt, int minVal, int maxVal)
{
    string input;
    int value;

    while (true)
    {
        std::cout << prompt;
        cin >> input;

        stringstream ss(input);

        if ((ss >> hex >> value) && value >= minVal && value <= maxVal)
            return value;

        std::cout << "Invalid input\n";
    }
}


std::string Machine::LoadProgram(const std::string& filename, int startAddress)
{
    if (startAddress < 0 || startAddress > 254 || startAddress % 2 != 0)
        return "Start address must be an even hex address from 00 to FE.";
    Reset();
    std::string error = ProgramLoader::LoadFile(filename, startAddress, memory);
    if (error.empty()) {
        cpu.SetPC(startAddress);
        programLoaded = true;
        return "Program loaded successfully.";
    }
    return error;
}

void Machine::SetRegisterValue(int reg, int value)
{
    if (reg >= 0 && reg < 16 && value >= 0 && value <= 255)
        memory.SetRegister(reg, value);
}

void Machine::SetMemoryValue(int address, int value)
{
    if (address >= 0 && address < 256 && value >= 0 && value <= 255) {
        if (address == 255) memory.SetSingleCell(address, value);
        else memory.SetCell(address, value);
    }
}

std::string Machine::RunOneStep()
{
    if (!programLoaded) return "Load a program first.";
    if (cpu.IsHalted()) return "Program halted.";
    StepResult result = cpu.Step();
    if (result == StepResult::HALTED) return "Program halted.";
    if (result == StepResult::INVALID_INSTRUCTION) return cpu.GetErrorMsg();
    if (result == StepResult::PC_OUT_OF_RANGE) return "Program counter out of range.";
    return "Executed one instruction.";
}

std::string Machine::RunAllSteps()
{
    if (!programLoaded) return "Load a program first.";
    int steps = 0;
    while (!cpu.IsHalted() && steps < MAX_STEPS) {
        StepResult result = cpu.Step();
        steps++;
        if (result == StepResult::HALTED) return "Program halted.";
        if (result == StepResult::INVALID_INSTRUCTION) return cpu.GetErrorMsg();
        if (result == StepResult::PC_OUT_OF_RANGE) return "Program counter out of range.";
    }
    if (steps >= MAX_STEPS) return "Stopped: reached maximum steps.";
    return "Execution finished.";
}

std::string Machine::GetRegistersText()
{
    std::ostringstream out; memory.DisplayRegisters(out); return out.str();
}
std::string Machine::GetMemoryText()
{
    std::ostringstream out; memory.DisplayMemory(out, cpu.GetPC()); return out.str();
}
std::string Machine::GetScreenText()
{
    std::ostringstream out; memory.DisplayScreen(out); return out.str();
}
std::string Machine::GetPCText() { return Utils::DecToHex(cpu.GetPC(), 2); }
std::string Machine::GetIRText() { return cpu.GetIR(); }
bool Machine::IsProgramLoaded() { return programLoaded; }

void Machine::LoadProgramFromFile()
{
    string filename;


    std::cout << "File name: ";
    if (! (cin >> filename)){
        std::cout << "File does not exist\n";
        return;
    }

    int addr = ReadHexInput("Start address (hex): ", 0, 254);

    if (addr % 2 != 0)
    {
        std::cout << "Invalid start address\n";
        return;
    }

    Reset();

    string error = ProgramLoader:: LoadFile(filename, addr, memory);

    if (error.empty())
    {
        cpu.SetPC(addr);
        programLoaded = true;
        std::cout << "Program loaded successfully\n";
    }
    else
    {
        programLoaded = false;
        std::cout << error << "\n";
    }
}

void Machine::OverwriteRegister()
{
    int reg = ReadHexInput("Register number (hex): ", 0, 15);
    int value = ReadHexInput("Value (hex): ", 0, 255);

    memory.SetRegister(reg, value);
}

void Machine::OverwriteMemory()
{
    int addr = ReadHexInput("Address (hex): ", 0, 255);
    int value = ReadHexInput("Value (hex): ", 0, 255);
    if (addr == 255){
        memory.SetSingleCell(addr, value);
    }
    else{
        memory.SetCell(addr, value);
    }
}

void Machine::RunProgram(bool stepMode)
{
    if (!programLoaded)
    {
        std::cout << "Load a program first\n";
        return;
    }

    if (stepMode)
    {
        if (cpu.IsHalted())
        {
            std::cout << "Program halted\n";
            return;
        }

        StepResult result = cpu.Step();
        if (result == StepResult::HALTED)
        {
            std::cout << "Program halted\n";
        }
        else if (result == StepResult::INVALID_INSTRUCTION)
        {
            std::cout << cpu.GetErrorMsg() << "\n";
        }
        else if (result == StepResult::PC_OUT_OF_RANGE)
        {
            std::cout << "Program counter out of range\n";
        }
    }
    else
    {
        int steps = 0;

        while (!cpu.IsHalted() && steps < MAX_STEPS)
        {
            StepResult result = cpu.Step();
            if (result == StepResult::HALTED)
            {
                std::cout << "Program halted\n";
                break;
            }
            else if (result == StepResult::INVALID_INSTRUCTION)
            {
                std::cout << cpu.GetErrorMsg() << "\n";
                break;
            }
            else if (result == StepResult::PC_OUT_OF_RANGE)
            {
                std::cout << "Program counter out of range\n";
                break;
            }
            steps ++;
        }
        if (steps >= MAX_STEPS)
                std::cout << "Stopped: reached max steps\n";
    }
    DisplayState();
}

void Machine::DisplayState()
{
    std::cout << "\nPC: " << Utils::DecToHex(cpu.GetPC(), 2) << "\n";
    std::cout << "\nIR: " << cpu.GetIR() << "\n";
    std::cout << "\nRegisters:\n";
    memory.DisplayRegisters(std::cout);
    std::cout << "\nMemory:\n";
    memory.DisplayMemory(std::cout, cpu.GetPC());
    std::cout << "\nScreen:\n";
    memory.DisplayScreen(std::cout);
}

void Machine::Reset()
{
    cpu.Reset();
    memory.Reset();
    programLoaded = false;
}

void Machine::ShowMenu()
{
    int choice;

    do
    {
        cout << "\n1. Load Program";
        cout << "\n2. Overwrite Register";
        cout << "\n3. Overwrite Memory";
        cout << "\n4. Run All";
        cout << "\n5. Run Step";
        cout << "\n6. Display State";
        cout << "\n7. Reset";
        cout << "\n0. Exit";
        cout << "\nChoose: ";

        cin >> choice;

        if (choice == 1)
            LoadProgramFromFile();
        else if (choice == 2)
            OverwriteRegister();
        else if (choice == 3)
            OverwriteMemory();
        else if (choice == 4)
            RunProgram(false);
        else if (choice == 5)
        {
            RunProgram(true);
            cin.ignore();
            cin.get();
        }
        else if (choice == 6)
            DisplayState();
        else if (choice == 7)
            Reset();

    } while (choice != 0);

    cout << "Goodbye\n";
}

void Machine::Run()
{
    ShowMenu();
}