#include <iostream>
#include <sstream>
#include "Machine.h"

using namespace std;

Machine::Machine()
{
    programLoaded = false;
}

int Machine::ReadHexInput(string prompt, int minVal, int maxVal)
{
    string input;
    int value;

    while (true)
    {
        cout << prompt;
        cin >> input;

        stringstream ss(input);

        if ((ss >> hex >> value) && value >= minVal && value <= maxVal)
            return value;

        cout << "Invalid input\n";
    }
}

void Machine::LoadProgramFromFile()
{
    string filename;


    cout << "File name: ";
    cin >> filename;

    int addr = ReadHexInput("Start address (hex): ", 0, 254);

    if (addr % 2 != 0)
    {
        cout << "Invalid start address\n";
        return;
    }

    Reset();

    programLoaded = loader.LoadHexFile(filename, addr, memory);

    if (programLoaded)
    {
        cpu.SetPC(addr);
        cout << "Program loaded successfully\n";
    }
    else
    {
        cout << "Failed to load program\n";
    }
}

void Machine::OverwriteRegister()
{
    int reg = ReadHexInput("Register number (hex): ", 0, 15);
    int value = ReadHexInput("Value (hex): ", 0, 255);

    cpu.GetRegisters().Set(reg, value);
}

void Machine::OverwriteMemory()
{
    int addr = ReadHexInput("Address (hex): ", 0, 255);
    int value = ReadHexInput("Value (hex): ", 0, 255);

    memory.Set(addr, value);
}

void Machine::RunProgram(bool stepMode)
{
    if (!programLoaded)
    {
        cout << "Load a program first\n";
        return;
    }

    if (stepMode)
    {
        if (cpu.IsHalted())
        {
            cout << "Program halted\n";
            return;
        }

        cpu.Fetch(memory);
        cpu.Execute(memory);
    }
    else
    {
        int steps = 0;

        while (!cpu.IsHalted() && steps < MAX_STEPS)
        {
            cpu.Fetch(memory);
            cpu.Execute(memory);
            steps++;
        }

        if (steps >= MAX_STEPS)
            cout << "Stopped: reached max steps\n";
    }

    DisplayState();
}

void Machine::DisplayState()
{
    cout << "\nPC: " << cpu.GetPC();
    cout << "\nIR: " << cpu.GetIR() << "\n";

    cpu.GetRegisters().Display();
    memory.DisplayScreen();
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