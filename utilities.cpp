#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include "Memory.h"j

using namespace std;

// Converts hexadecimal string to decimal
int Utils::HexToDec(string s) {
    int result = 0;

    for (char c : s) {
        result *= 16;

        if (c >= '0' && c <= '9')
            result += c - '0';
        else if (c >= 'A' && c <= 'F')
            result += c - 'A' + 10;
        else if (c >= 'a' && c <= 'f')
            result += c - 'a' + 10;
    }

    return result;
}

// Converts decimal value to hexadecimal string
string Utils::DecToHex(int value, int width) {
    stringstream ss;

    ss << uppercase << hex
       << setw(width) << setfill('0') << value;

    return ss.str();
}

// Checks if a string contains valid hexadecimal characters
bool Utils::IsValidHex(string s, int expectedLen) {
    if (s.length() != expectedLen)
        return false;

    for (char c : s) {
        if (!isxdigit(static_cast<unsigned char>(c)))
            return false;
    }

    return true;
}

// Reads and parses the program file
string ProgramLoader::ParseFile(string filename, vector<int>& words) {
    ifstream file(filename);

    if (!file.is_open())
        return "Error: Cannot open file.";

    string line;

    while (getline(file, line)) {
        // Remove comments
        size_t first = line.find_first_not_of(" \t\n\r");
        if (first == string::npos)
            continue;
        size_t last = line.find_last_not_of(" \t\n\r");
        line = line.substr(first, (last - first + 1));

        size_t commentPos = line.find(';');
        if (commentPos != string::npos){
            line = line.substr(0, commentPos);
            last = line.find_last_not_of(" \t\n\r");
            if (last != string::npos)
                line = line.substr(0, last + 1);
            else
                continue;
        }
        
        stringstream ss(line);
        string word;

        while (ss >> word) {
            if (!Utils::IsValidHex(word, 4)){
                file.close();
                return "Error: Invalid instruction: " + word;
            }
            words.push_back(Utils::HexToDec(word));
        }
    }

    file.close();

    return "";
}

// Loads program words into memory
string ProgramLoader::LoadFile(string filename, int startAddr, Memory& mem) {
    vector<int> words;

    string error = ParseFile(filename, words);

    if (!error.empty())
        return error;

    for (int i = 0; i < words.size(); i++) {
        mem.SetCell(startAddr + (i * 2), words[i]);
    }
    return "";
}
