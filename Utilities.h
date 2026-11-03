#include <iostream>
#include <string>
#include <fstream>
#include <Memory.cpp>
using namespace std;

class Utils{
    public:
    static int HexToDec(string hex);
    static string DecToHex(int dec, int width);
    static bool  IsValidHex(string hex, int width);
};
class ProgramLoader{
    bool IsValidProgram(string filename);
    public:
    void LoadProgram(string filename, int startAddress, Memory &memory);
};