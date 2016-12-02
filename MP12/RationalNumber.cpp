#include "RationalNumber.h"

//to_String converts numerator and denominator to string of type num/denom
string RationalNumber::to_String(void){
	stringstream my_output;
	my_output << numerator << "/" << denominator;
	return my_output.str();
}
RationalNumber::RationalNumber(){ //empty constructor
NumberType=RATIONAL;
numerator=0;//default value
denominator=1;
}
RationalNumber::RationalNumber(int numer,int denom){//complete constructor
NumberType=RATIONAL;
numerator=numer;
denominator=denom;
}
//copy constructor
RationalNumber::RationalNumber(const RationalNumber& other){
NumberType=RATIONAL;
numerator=other.numerator;
denominator=other.denominator;
}
//setter num
void RationalNumber::set_numerator(int numer){
numerator=numer;
}
//setter denom
void RationalNumber::set_denominator(int denom){
denominator=denom;
}
//get numer
int RationalNumber::get_numerator() const{
    return numerator;
}
int RationalNumber::get_denominator() const{
    return denominator;
}
void RationalNumber::set_value(int numer,int denom){
numerator=numer;
denominator=denom;
}
int RationalNumber::gcd(int a,int b){
  if ( a==0 )
    return b;
  return gcd ( b%a, a );


}


double RationalNumber::magnitude(){
if((numerator/denominator)<0)
    return(-1*(numerator/denominator));
else
    return (numerator/denominator);
}
double RationalNumber::decimal_value() const{
return numerator/denominator;
}


//Operator for +
RationalNumber RationalNumber::operator + (const RationalNumber& arg)
{
        RationalNumber result;
        result.numerator=numerator*arg.denominator+denominator*arg.numerator;
    result.denominator=denominator*arg.denominator;
    result.numerator=gcd(result.numerator,result.denominator)*result.numerator;
    result.denominator=gcd(result.numerator,result.denominator)*result.denominator;    
        return result;
}
RealNumber RationalNumber::operator + (const RealNumber& arg)
{
    RealNumber result;
    result.set_value(decimal_value()+arg.get_value());
    return result;
}
//Operator for -
RationalNumber RationalNumber::operator - (const RationalNumber& arg)
{
        RationalNumber result;
        result.numerator=numerator*arg.denominator-denominator*arg.numerator;
    result.denominator=denominator*arg.denominator;
    result.numerator=gcd(result.numerator,result.denominator)*result.numerator;
    result.denominator=gcd(result.numerator,result.denominator)*result.denominator;    
        return result;
}
PolarNumber RationalNumber::operator + (const PolarNumber& arg){
    double x, y, add;
    x = arg.get_magComponent() * cos (arg.get_phaseComponent());
    y = arg.get_magComponent() * sin (arg.get_phaseComponent());
    //add real components together
    add = x + decimal_value();
    //resolve back to polar
    double new_phaseComponent = tan(y/add);
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
    double new_phaseComponent = tan(y/sub);
    double new_magComponent = sqrt(sub*sub + y*y);
    return PolarNumber (new_magComponent, new_phaseComponent);
}
RealNumber RationalNumber::operator - (const RealNumber& arg)
{
    RealNumber result;
    result.set_value(decimal_value()-arg.get_value());
    return result;
}
//Operator for *
RationalNumber RationalNumber::operator * (const RationalNumber& arg)
{
    RationalNumber result;
    result.numerator=numerator*arg.numerator;
    result.denominator=denominator*arg.denominator;
    result.numerator=gcd(result.numerator,result.denominator)*result.numerator;
    result.denominator=gcd(result.numerator,result.denominator)*result.denominator;    
    return result;
}
RealNumber RationalNumber::operator * (const RealNumber& arg)
{
    RealNumber result;
    result.set_value(decimal_value()*arg.get_value());
    return result;
}
PolarNumber RationalNumber::operator * (const PolarNumber& arg)
{
    PolarNumber result;
    result.set_magComponent(decimal_value()*arg.get_magComponent());
	result.set_phaseComponent(arg.get_phaseComponent());
    return result;
}
//Operator for /
RationalNumber RationalNumber::operator / (const RationalNumber& arg)
{
    RationalNumber result;
result.numerator=numerator*arg.denominator;
result.denominator=denominator*arg.numerator;
    result.numerator=gcd(result.numerator,result.denominator)*result.numerator;
    result.denominator=gcd(result.numerator,result.denominator)*result.denominator;    
    return result;
}
RealNumber RationalNumber::operator / (const RealNumber& arg)
{
    RealNumber result;
    result.set_value(decimal_value()/arg.get_value());
    return result;
}
PolarNumber RationalNumber::operator / (const PolarNumber& arg)
{
    PolarNumber result;
    result.set_magComponent(decimal_value()/arg.get_magComponent());
	result.set_phaseComponent(arg.get_phaseComponent());
    return result;
}
