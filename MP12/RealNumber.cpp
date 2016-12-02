#include "RealNumber.h"

//to_String converts real and imaginary components to string of type a+bi
string RealNumber::to_String(void){
	stringstream my_output;
	my_output << value;
	return my_output.str();
}
RealNumber::RealNumber(double rval){//complete constructor
NumberType=REAL;
value=rval;
}
//copy constructor


RealNumber::RealNumber(const RealNumber& other){
NumberType=REAL;
value=other.value;
}
//getter
double RealNumber::get_value() const{//getter function, ask why const??
    return value;
}
//setter
void RealNumber::set_value(double rval){
value=rval;
}
double RealNumber::magnitude(){
if(value<0)
    return(-1*value);
else
    return value;
}
//Operator for +
RealNumber RealNumber::operator + (const RealNumber& arg)
{
    RealNumber result;
    result.value=value+arg.value;
    return result;
}
RealNumber RealNumber::operator + (const RationalNumber& arg)
{
    RealNumber result;
    result.value=value+arg.decimal_value();
    return result;
}

PolarNumber RealNumber::operator + (const PolarNumber& arg){
    double x, y, add;
    x = arg.get_magComponent() * cos (arg.get_phaseComponent());
    y = arg.get_magComponent() * sin (arg.get_phaseComponent());
    //add real components together
    add = x + get_value();
    //resolve back to polar
    double new_phaseComponent = tan(y/add);
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
    double new_phaseComponent = tan(y/sub);
    double new_magComponent = sqrt(sub*sub + y*y);
    return PolarNumber (new_magComponent, new_phaseComponent);
}

//Operator for -
RealNumber RealNumber::operator - (const RealNumber& arg)
{
    RealNumber result;
    result.value=value-arg.value;
    return result;
}
RealNumber RealNumber::operator - (const RationalNumber& arg)
{
    RealNumber result;
    result.value=value-arg.decimal_value();
    return result;
}
//Operator for *
RealNumber RealNumber::operator * (const RealNumber& arg)
{
    RealNumber result;
result.value=value*arg.value;
    return result;
}
RealNumber RealNumber::operator * (const RationalNumber& arg)
{
    RealNumber result;
    result.value=value*arg.decimal_value();
    return result;
}
PolarNumber RealNumber::operator * (const PolarNumber& arg)
{
    PolarNumber result;
    result.set_magComponent(value*arg.get_magComponent());
	result.set_phaseComponent(arg.get_phaseComponent());
    return result;
}
//Operator for /
RealNumber RealNumber::operator / (const RealNumber& arg)
{
    RealNumber result;
result.value=value/arg.value;
    return result;
}
RealNumber RealNumber::operator / (const RationalNumber& arg)
{
    RealNumber result;
    result.value=value/arg.decimal_value();
    return result;
}
PolarNumber RealNumber::operator / (const PolarNumber& arg)
{
    PolarNumber result;
    result.set_magComponent(value/arg.get_magComponent());
	result.set_phaseComponent(arg.get_phaseComponent());
    return result;
}
