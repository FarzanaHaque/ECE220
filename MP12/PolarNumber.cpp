#include "PolarNumber.h"

//to_String converts mag and phase components to string of type a<b
string PolarNumber::to_String(void){

        stringstream my_output;
	my_output << magComponent<< "<"<<180.0*phaseComponent/M_PI;
        return my_output.str();

}
PolarNumber::PolarNumber(){ //empty constructor
NumberType=POLAR;
magComponent=0;//default value
phaseComponent=0;
}
PolarNumber::PolarNumber(double magnitude,double phase){//complete constructor
NumberType=POLAR;
magComponent=magnitude;
phaseComponent=phase;
}
//copy constructor


PolarNumber::PolarNumber(const PolarNumber& other){
NumberType=POLAR;
magComponent=other.magComponent;
phaseComponent=other.phaseComponent;
}
//set mag
void PolarNumber::set_magComponent(double mval){
magComponent=mval;
}
//set phase
void PolarNumber::set_phaseComponent(double phval){
phaseComponent=phval;
}
//get mag
double PolarNumber::get_magComponent() const{
    return magComponent;
}
//get phase
double PolarNumber::get_phaseComponent() const{
    return phaseComponent;
}
void PolarNumber::set_value(double mval,double phval){
magComponent=mval;
phaseComponent=phval;
}


//Operator for +
PolarNumber PolarNumber::operator + (const PolarNumber& arg)
{
    PolarNumber result;
/*
    result.magComponent=magComponent+arg.magComponent;
    result.phaseComponent=phaseComponent+arg.phaseComponent;
    result.phaseComponent=result.phaseComponet%(2*M_PI);
*/
//found this math formular for stackexchange
result.magComponent=sqrt((magComponent*magComponent)+(arg.magComponent*arg.magComponent)+2*magComponent*arg.magComponent*cos(arg.phaseComponent-phaseComponent));
result.phaseComponent=phaseComponent+atan2(arg.magComponent*sin(arg.phaseComponent-arg.phaseComponent),magComponent*cos(arg.phaseComponent-phaseComponent));
    return result;
}


//Operator for -
PolarNumber PolarNumber::operator - (const PolarNumber& arg)
{    PolarNumber result;
result.magComponent=sqrt((magComponent*magComponent)+(arg.magComponent*arg.magComponent)+2*magComponent*arg.magComponent*cos(arg.phaseComponent+180-phaseComponent));
result.phaseComponent=phaseComponent+atan2(arg.magComponent*sin(arg.phaseComponent+180-arg.phaseComponent),magComponent*cos(arg.phaseComponent+180-phaseComponent));
    return result;
}


//Operator for *
PolarNumber PolarNumber::operator * (const PolarNumber& arg)
{
    PolarNumber result;
result.magComponent=magComponent*arg.magComponent;
result.phaseComponent=phaseComponent+arg.phaseComponent;
    return result;
}
PolarNumber PolarNumber::operator * (const RealNumber& arg){
PolarNumber result;
result.phaseComponent=phaseComponent;
result.magComponent=magComponent*arg.get_value();
return result;
}

//Operator for /
PolarNumber PolarNumber::operator / (const PolarNumber& arg)
{
    PolarNumber result;
result.magComponent=magComponent/arg.magComponent;
result.phaseComponent=phaseComponent-arg.phaseComponent;
    return result;
}
PolarNumber PolarNumber::operator / (const RealNumber& arg){
PolarNumber result;
result.phaseComponent=phaseComponent;
result.magComponent=magComponent/arg.get_value();
return result;
}
