#ifndef ALU_H
#define ALU_H
class ALU {
    private:
   static double DecodeFloat (int bits);
   static int EncodeFloat (double value );
    public:
   static int AddInt(int a, int b);
   static int AddFloat(int a, int b);
   static int Or(int a, int b);
    static int And(int a, int b);
   static int Xor(int a, int b);
   static int RotateRight(int value , int times);

};
#endif