#include<iostream>
#include "ALU.h"
#include<cmath>
using namespace std;

int ALU::AddInt(int a, int b){
    return (a+b)%256;
}
int ALU::AddFloat(int a, int b){
    double num1 = DecodeFloat(a);
    double num2 = DecodeFloat(b);
    double result = num1+num2;
    return EncodeFloat(result);
}
int ALU::Or(int a, int b){
    return (a|b)%256;
}
int ALU::And(int a, int b){
    return(a&b)%256;
}
int ALU::Xor(int a, int b){
    return (a^b)%256;
}
int ALU::RotateRight(int value, int times){
    times= times % 8;
    if(times == 0){ return value %256;}
    int rotateval= (value>>times)|(value<<(8-times));
    return rotateval % 256;

}
double ALU::DecodeFloat(int bits){
    bits= bits %256;
    int sign = (bits >>7)&1;
    int exponent = (bits >>4) & 0x7;
   int  mantissa = bits & 0xf;
   if (bits ==0) {return 0.0;}
   double fraction = mantissa/16.0;
   double power = pow ( 2.0 , exponent-4) ;
   double value = fraction*power;
if (sign==1){value= -1*value;}
return value ;
}
int ALU::EncodeFloat(double value){
    if ( value==0){return 0 ;}
    int sign =0;
    if (value<0){
        sign=1;
        value= -1 * value;

    }
   int realexponent =0;
   int realmantissa =0;
   double minerror =99999.0;
   for (int exp =0 ; exp<=7 ; exp++){
    double power = pow(2.0, exp-4);
    int mant= round((value/power)* 16.0);
    if ( mant>=0 && mant<=15) {
        double actualval= (mant/16.0)*power;
        double error = std ::abs(value - actualval);

    
    if (error<minerror){
        minerror= error;
        realexponent= exp;
        realmantissa = mant;
    }
    }
   } 
   int result = (sign<<7)|(realexponent<<4)|realmantissa;
   return result % 256;
}