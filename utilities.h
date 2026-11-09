#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>

using namespace std;

class Memory;

class Utils {
public:
    static int HexToDec(string s);
    static string DecToHex(int value, int width);
    static bool IsValidHex(string s, int expectedLen);
};

class ProgramLoader {
public:
    static string LoadFile(string filename, int startAddr, Memory& mem);

private:
    static string ParseFile(string filename, vector<int>& words);
};

#endif
