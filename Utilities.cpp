#include "Utilities.h"

int Utils::HexToDec(string hex)
{
    int dec = 0;
    for (char c : hex) {
        dec *= 16;
        if (c >= '0' && c <= '9') {
            dec += c - '0';
        } else if (c >= 'A' && c <= 'F') {
            dec += c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
            dec += c - 'a' + 10;
        }
    }
    return dec;
}

string Utils::DecToHex(int dec, int width)
{
    string hex = "";
    if (dec == 0) {
        hex = "0";
    } else {
        while (dec > 0) {
            int remainder = dec % 16;
            if (remainder < 10) {
                hex = char(remainder + '0') + hex;
            } else {
                hex = char(remainder - 10 + 'A') + hex;
            }
            dec /= 16;
        }
    }
    while (hex.length() < width) {
        hex = "0" + hex;
    }
    return hex;
}


bool Utils::IsValidHex(string hex, int width)
{
    if (hex.length() != width) {
        return false;
    }
    for (char c : hex) {
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) {
            return false;
        }
    }
    return true;
}

bool ProgramLoader::IsValidProgram(string filename)
{
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    return true;
}

void ProgramLoader::LoadProgram(string filename, int startAddress, Memory &memory)
{
}
