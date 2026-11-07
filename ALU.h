#ifndef ALU_H
#define ALU_H

#include <iostream>
using namespace std;

class ALU {
        static double DecodeFloat(double value);
        static int EncodeFloat(double value);
        public :
        static int AddInt(int a, int b);
        static int AddFloat(int a, int b);
        static int Or(int a, int b);
        static int And(int a, int b);
        static int Xor(int a, int b);
        static int RotateRight(int value, int times);
};
#endif
