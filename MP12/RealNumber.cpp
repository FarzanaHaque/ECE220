#include "RealNumber.h"

//to_String converts real and imaginary components to string of type a+bi
string RealNumber::to_String(void){
	stringstream my_output;
	my_output << value;
	return my_output.str();
}
/*Class constructors, used to generating a new instance of the class.  Note that in the class constructors, ALL class variables, including the variables inherited from the base class, must be assigned a value.  In the example of RealNumber, this means that each constructor will need to assign a value to the variables value and NumberType.  In the case of the empty constructor you may assume a default value of value = 0. */
RealNumber::RealNumber(){ //empty constructor
NumberType=REAL;
value=0;//default value
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
