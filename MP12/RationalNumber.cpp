#include "RationalNumber.h"
/*
INTRO PARAGRAPH
Rational number has numberator and denominator, and acts like a standard rational number when doing operations on itself, returning a rational
Magnitude, returns abs value, gcd returns the greatest common divisor of 2 numbers
if you do rational OP real you'll return a real number, using get_value to get info from your arg
if you do rationaal OP polar you'll return a polar number
if it's * or /, you keep the same phase, and either multiply or divide the magnitude with the magComponent of the arg
if it's + or - convert polar number to the form a+ib then add the sum ( (a+rationallnumber) +ib) which you can convert back to polar coordinates 

*/

//to_String converts numerator and denominator to string of type num/denom
string RationalNumber::to_String(void){
    stringstream my_output;
    my_output << numerator << "/" << denominator;
    return my_output.str();
}


//Empty Constructor        
RationalNumber::RationalNumber() {
    NumberType=RATIONAL;
    numerator=0;
    denominator=0;
}


//Complete Constructor
RationalNumber::RationalNumber(int numer, int denom) {
    NumberType=RATIONAL;
    numerator=numer;
    denominator=denom;
}


//Copy Constructor
RationalNumber::RationalNumber(const RationalNumber& other){
    NumberType=RATIONAL;
    numerator=other.numerator;
    denominator=other.denominator;
}


//Getter functions
int RationalNumber::get_numerator() const{
    return numerator;
}


int RationalNumber::get_denominator() const{
    return denominator;
}


//Setter functions
void RationalNumber::set_numerator(int numer){
    numerator=numer;
}


void RationalNumber::set_denominator(int denom){
    denominator=denom;
}


//Class member functions
void RationalNumber::set_value(int numer,int denom){
    numerator=numer;
    denominator=denom;
}


int RationalNumber::gcd(int a,int b){
    if (a==0)
        return b;
    return gcd (b%a, a);
}


double RationalNumber::magnitude(){
    if((numerator/denominator)<0)
        return(-1*(numerator/denominator));
    else
        return (numerator/denominator);
}


double RationalNumber::decimal_value() const{
    double n, d;
    n = numerator;
    d = denominator;
    return (n/d);
}






//Operation overload for RationalNumber (op) RationalNumber
RationalNumber RationalNumber::operator + (const RationalNumber& arg){
    RationalNumber result;
    result.numerator=numerator*arg.denominator+denominator*arg.numerator;
    result.denominator=denominator*arg.denominator;
    int gcdvar=gcd(result.numerator,result.denominator);
    //to reduce divide numerator & denominator by gcd
    result.numerator=result.numerator/gcdvar;
    result.denominator=result.denominator/gcdvar;
        return result;
}


RationalNumber RationalNumber::operator - (const RationalNumber& arg){
    RationalNumber result;
    result.numerator=numerator*arg.denominator-denominator*arg.numerator;
    result.denominator=denominator*arg.denominator;
    int gcdvar=gcd(result.numerator,result.denominator);
    //to reduce divide numerator & denominator by gcd
    result.numerator=result.numerator/gcdvar;
    result.denominator=result.denominator/gcdvar;
        return result;
}


RationalNumber RationalNumber::operator * (const RationalNumber& arg)
{
    RationalNumber result;
    result.numerator=numerator*arg.numerator;
    result.denominator=denominator*arg.denominator;
    int gcdvar=gcd(result.numerator,result.denominator);
    //to reduce divide numerator & denominator by gcd
    result.numerator=result.numerator/gcdvar;
    result.denominator=result.denominator/gcdvar;
    return result;
}


RationalNumber RationalNumber::operator / (const RationalNumber& arg){
    RationalNumber result;
    result.numerator=numerator*arg.denominator;
    result.denominator=denominator*arg.numerator;
    int gcdvar=gcd(result.numerator,result.denominator);
    //to reduce divide numerator & denominator by gcd
    result.numerator=result.numerator/gcdvar;
    result.denominator=result.denominator/gcdvar;
    return result;
}






//Operation overload for RationalNumber (op) PolarNumber
PolarNumber RationalNumber::operator + (const PolarNumber& arg){
    double x, y, add;
    x = arg.get_magComponent() * cos (arg.get_phaseComponent());
    y = arg.get_magComponent() * sin (arg.get_phaseComponent());
    //add real components together
    add = x + decimal_value();
    //resolve back to polar
    double new_phaseComponent = atan(y/add);
    double new_magComponent = sqrt(add*add + y*y);
    return PolarNumber (new_magComponent, new_phaseComponent);
}


PolarNumber RationalNumber::operator - (const PolarNumber& arg){
    double x, y, sub;
    x = arg.get_magComponent() * cos (arg.get_phaseComponent());
    y = arg.get_magComponent() * sin (arg.get_phaseComponent());
    //add real components together
    sub = x - decimal_value();
    //resolve back to polar
    double new_phaseComponent = atan(y/sub)-M_PI;
    double new_magComponent = sqrt(sub*sub + y*y);
    return PolarNumber (new_magComponent, new_phaseComponent);
}


PolarNumber RationalNumber::operator * (const PolarNumber& arg){
    PolarNumber result;
    result.set_magComponent(decimal_value()*arg.get_magComponent());
      result.set_phaseComponent(arg.get_phaseComponent());
    return result;
}


PolarNumber RationalNumber::operator / (const PolarNumber& arg){
    PolarNumber result;
    result.set_magComponent(decimal_value()/arg.get_magComponent());
    result.set_phaseComponent(-arg.get_phaseComponent());
    return result;
}


//Operation overload for RationalNumber (op) RealNumber
RealNumber RationalNumber::operator + (const RealNumber& arg){
    RealNumber result;
    result.set_value(decimal_value()+arg.get_value());
    return result;
}


RealNumber RationalNumber::operator - (const RealNumber& arg){
    RealNumber result;
    result.set_value(decimal_value()-arg.get_value());
    return result;
}


RealNumber RationalNumber::operator * (const RealNumber& arg){
    RealNumber result;
    result.set_value(decimal_value()*arg.get_value());
    return result;
}


RealNumber RationalNumber::operator / (const RealNumber& arg)
{
    RealNumber result;
    result.set_value(decimal_value()/arg.get_value());
    return result;
}

