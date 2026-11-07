#include <iostream>
#include "Machine.h"

using namespace std;

Machine::Machine()
{
    programLoaded = false;
}

bool Machine::ValidateStartAddress(int addr)
{
    return addr >= 0 && addr < 255 && addr % 2 == 0;
}

bool Machine::LoadProgramFromFile(string filename, int startAddr)
{
    if (!ValidateStartAddress(startAddr))
    {
        cout << "Invalid start address\n";
        return false;
    }

    Reset();

    programLoaded = loader.LoadHexFile(filename, startAddr, memory);

    if (programLoaded)
    {
        cpu.SetPC(startAddr);
        cout << "Program loaded successfully\n";
    }
    else
    {
        cout << "Failed to load program\n";
    }

    return programLoaded;
}

void Machine::OverwriteRegister(int reg, int value)
{
    if (reg >= 0 && reg < 16)
        regs.Set(reg, value);
    else
        cout << "Invalid register\n";
}

void Machine::OverwriteMemory(int addr, int value)
{
    if (addr >= 0 && addr < 256)
        memory.Set(addr, value);
    else
        cout << "Invalid address\n";
}

void Machine::FetchDecodeExecute()
{
    cpu.Fetch(memory);
    cpu.Execute(decoder, regs, memory, alu);
}

void Machine::RunStep()
{
    if (!programLoaded)
    {
        cout << "Load a program first\n";
        return;
    }

    if (cpu.IsHalted())
    {
        cout << "Program halted\n";
        return;
    }

    FetchDecodeExecute();
    DisplayState();
}

void Machine::RunAll()
{
    if (!programLoaded)
    {
        cout << "Load a program first\n";
        return;
    }

    while (!cpu.IsHalted())
    {
        FetchDecodeExecute();
    }

    DisplayState();
}

void Machine::DisplayState()
{
    cout << "\nPC: " << cpu.GetPC();
    cout << "\nIR: " << cpu.GetIR() << "\n";

    regs.Display();
    memory.DisplayScreen();
}

void Machine::Reset()
{
    cpu.Reset();
    memory.Reset();
    regs.Reset();
    programLoaded = false;
}

void Machine::Shutdown()
{
    cout << "Goodbye\n";
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
        {
            string filename;
            int address;

            cout << "File name: ";
            cin >> filename;

            cout << "Start address: ";
            cin >> address;

            LoadProgramFromFile(filename, address);
        }
        else if (choice == 2)
        {
            int reg, value;

            cout << "Register number: ";
            cin >> reg;

            cout << "Value: ";
            cin >> value;

            OverwriteRegister(reg, value);
        }
        else if (choice == 3)
        {
            int address, value;

            cout << "Address: ";
            cin >> address;

            cout << "Value: ";
            cin >> value;

            OverwriteMemory(address, value);
        }
        else if (choice == 4)
        {
            RunAll();
        }
        else if (choice == 5)
        {
            RunStep();
            cin.ignore();
            cin.get();
        }
        else if (choice == 6)
        {
            DisplayState();
        }
        else if (choice == 7)
        {
            Reset();
        }

    } while (choice != 0);

    Shutdown();
}