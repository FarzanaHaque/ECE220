#include "RealNumber.h"
/*
INTRO PARAGRAPH
Real number has value, and acts like a standard real number when doing operations on itself, returning a real
Magnitude, returns abs value
if you do real OP rational you'll return a real number, using decimal_value to get info from your arg
if you do real OP polar you'll return a polar number
if it's * or /, you keep the same phase, and either multiply or divide the magnitude with the magComponent of the arg
if it's + or - convert polar number to the form a+ib then add the sum ( (a+realnumber) +ib) which you can convert back to polar coordinates 
*/


//to_String converts real and imaginary components to string of type a+bi
string RealNumber::to_String(void){
    stringstream my_output;
    my_output << value;
    return my_output.str();
}


//Empty Constructor        
RealNumber::RealNumber() {
    NumberType=REAL;
    value=0;//default value
}


//Complete Constructor
RealNumber::RealNumber(double rval) {
    NumberType=REAL;
    value=rval;
}


//Copy Constructor
RealNumber::RealNumber(const RealNumber& other){
    NumberType=REAL;
    value=other.value;
}


//Setter function
void RealNumber::set_value(double rval){
    value=rval;
}


//Getter function
double RealNumber::get_value() const{
    return value;
}


//Class member functions
double RealNumber::magnitude(){
    if(value<0)
        return(-1*value);
    else
        return value;
}


//Operation overload for RealNumber (op) RealNumber
RealNumber RealNumber::operator + (const RealNumber& arg)
{
    RealNumber result;
    result.value = value+arg.value;
    return result;
}


RealNumber RealNumber::operator - (const RealNumber& arg)
{
    RealNumber result;
    result.value = value-arg.value;
    return result;
}


RealNumber RealNumber::operator * (const RealNumber& arg) {
    RealNumber result;
    result.value = value*arg.value;
    return result;
}


RealNumber RealNumber::operator / (const RealNumber& arg)
{
    RealNumber result;
    result.value = value/arg.value;
    return result;
}




//Operation overload for RealNumber (op) PolarNumber
PolarNumber RealNumber::operator + (const PolarNumber& arg){
    double x, y, add;
    x = arg.get_magComponent() * cos (arg.get_phaseComponent());
    y = arg.get_magComponent() * sin (arg.get_phaseComponent());
    //add real components together
    add = x + get_value();
    //resolve back to polar
    double new_phaseComponent = atan(y/add) + M_PI;
    double new_magComponent = sqrt(add*add + y*y);
    return PolarNumber (new_magComponent, new_phaseComponent);
}




PolarNumber RealNumber::operator - (const PolarNumber& arg){
    double x, y, sub;
    x = arg.get_magComponent() * cos (arg.get_phaseComponent());
     y = arg.get_magComponent() * sin (arg.get_phaseComponent());
    //add real components together
    sub = x - get_value();
    //resolve back to polar
    double new_phaseComponent = atan(y/sub);
    double new_magComponent = sqrt(sub*sub + y*y);
    return PolarNumber (new_magComponent, new_phaseComponent);
}


PolarNumber RealNumber::operator * (const PolarNumber& arg)
{
    PolarNumber result;
    result.set_magComponent(value*arg.get_magComponent());
    result.set_phaseComponent(arg.get_phaseComponent());
    return result;
}




PolarNumber RealNumber::operator / (const PolarNumber& arg)
{
    PolarNumber result;
    result.set_magComponent(value/arg.get_magComponent());
    result.set_phaseComponent(-arg.get_phaseComponent());
    return result;
}


//Operation overload for RealNumber (op) RationalNumber
RealNumber RealNumber::operator + (const RationalNumber& arg){
    RealNumber result;
    result.value = value + arg.decimal_value();
    return result;
}


RealNumber RealNumber::operator - (const RationalNumber& arg){
    RealNumber result;
    result.value = value - arg.decimal_value();
    return result;
}


RealNumber RealNumber::operator * (const RationalNumber& arg){
    RealNumber result;
    result.value = value * arg.decimal_value();
    return result;
}


RealNumber RealNumber::operator / (const RationalNumber& arg)
{
    RealNumber result;
    result.value = value / arg.decimal_value();
    return result;
}
