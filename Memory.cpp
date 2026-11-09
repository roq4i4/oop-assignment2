#include "Memory.h"

Memory::Memory()
{
    Reset();
}

string Memory::GetCell(int addr)
{
    return Utils::DecToHex(cells[addr], 2) + Utils::DecToHex(cells[addr + 1], 2);
}

string Memory::GetSingleCell(int addr)
{
    return Utils::DecToHex(cells[addr], 2);
}

void Memory::SetCell(int addr, int value)
{
    string hexValue = Utils::DecToHex(value, 4);
    cells[addr] = Utils::HexToDec(hexValue.substr(0, 2));
    cells[addr + 1] = Utils::HexToDec(hexValue.substr(2, 2));
}

void Memory::SetSingleCell(int addr, int value)
{
    if (addr >= 0 && addr < 256){
        cells[addr] = value % 256;
    }
    else {
        std:: cout << "Error: Address Out of Bounds!\n";
    }
}

string Memory::GetRegister(int r)
{
    return Utils::DecToHex(registers[r], 2);
}

void Memory::SetRegister(int r, int value)
{
    registers[r] = value;
}

void Memory::SetScreenBuffer(string buffer)
{
    screenBuffer = buffer;
}

void Memory::DisplayMemory(ostream& out, int pc)
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
        out << "Cell " << Utils::DecToHex(i, 2) << " : " << Utils::DecToHex(cells[i], 2) << endl;
    }
}

void Memory::DisplayRegisters(ostream& out)
{
    for (int i = 0; i < 16; i++){
        out << "R" << Utils::DecToHex(i, 1) << ": " << Utils::DecToHex(registers[i], 2) << endl;
    }
}

void Memory::DisplayScreen(ostream& out)
{
    out << screenBuffer;
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