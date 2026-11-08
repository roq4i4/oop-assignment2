#include "Memory.h"

int Memory::GetCell(int addr)
{
    return cells[addr];
}

void Memory::SetCell(int addr, int value)
{
    cells[addr] = value;
}

int Memory::GetRegister(int r)
{
    return registers[r];
}

void Memory::SetRegister(int r, int value)
{
    registers[r] = value;
}

void Memory::SetScreenBuffer(string buffer)
{
    screenBuffer = buffer;
}

void Memory::DisplayMemory(ostream out, int pc)
{
    for (int i = 0; i < 256; i++)
    {
        if (i == pc)
        {
            out << "PC-> ";
        }
        else
        {
            out << "     ";
        }
        out << "Cell " << i << ": " << cells[i] << endl;
    }
}

void Memory::DisplayRegisters(ostream out)
{
    for (int i = 0; i < 16; i++){
        out << "R" << i << ": " << registers[i] << endl;
    }
}

void Memory::DisplayScreen()
{
    cout << screenBuffer;
}

void Memory::Reset()
{
    for (int i = 0; i < 256; i++)
    {
        cells[i] = 0;
    }
    for (int i = 0; i < 16; i++)
    {
        registers[i] = 0;
    }
    screenBuffer = "";
}