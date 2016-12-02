#include "PolarNumber.h"
/*
for polar, when adding/subtracting with nonpolar we break it into components, add it back together, then turn it into another polar
for multiplying/dividing nonpolars, we keep the same phase and either multiply or divide the magnitude
for adding/subtracting polars we break into components, put it back together and then return another polar
for mult/divide, you mult/divide the magnitudes and add/subtract the phases
*/
//to_String converts mag and phase components to string of type a<b
string PolarNumber::to_String(void){

        stringstream my_output;
	my_output << magComponent<< "<"<<180.0*phaseComponent/M_PI;
        return my_output.str();

}
//Empty Constructor
PolarNumber::PolarNumber() {
    NumberType=POLAR;
    magComponent=0;
    phaseComponent=0;
}


//Complete Constructor
PolarNumber::PolarNumber(double magnitude, double phase) {
    NumberType=POLAR;
    magComponent=magnitude;
    phaseComponent=phase;
}


//Copy Constructor
PolarNumber::PolarNumber( const PolarNumber& other ){
    NumberType=POLAR;
    magComponent=other.magComponent;
    phaseComponent=other.phaseComponent;
}


//Setter functions
void PolarNumber::set_magComponent(double mval) {
    magComponent=mval;
}


void PolarNumber::set_phaseComponent(double phval){
    phaseComponent=phval;
}


//Getter functions
double PolarNumber::get_magComponent() const {
    return magComponent;
}


double PolarNumber::get_phaseComponent() const{
    return phaseComponent;
}




//Operation overload for PolarNumber (op) PolarNumber
PolarNumber PolarNumber::operator + (const PolarNumber& arg){
    double x1, x2, y1, y2, x, y;
    //break down into components
    x1 = magComponent * cos (phaseComponent);
    y1 = magComponent * sin (phaseComponent);
    x2 = arg.magComponent * cos (arg.phaseComponent);
    y2 = arg.magComponent * sin (arg.phaseComponent);
    //add components together
    x = x1 + x2;
    y = y1 + y2;
    //resolve back to polar form
    double new_phaseComponent = atan(y/x);
    double new_magComponent = sqrt((x*x) + (y*y));
    return PolarNumber(new_magComponent, new_phaseComponent);
}




PolarNumber PolarNumber::operator - (const PolarNumber& arg){
    double x1, x2, y1, y2, x, y;
    //break down into components
    x1 = magComponent * cos (phaseComponent);
    y1 = magComponent * sin (phaseComponent);
    x2 = arg.magComponent * cos (arg.phaseComponent);
    y2 = arg.magComponent * sin (arg.phaseComponent);
    //subtract components
    x = x1 - x2;
    y = y1 - y2;
    //resolve back to polar form
    double new_phaseComponent = atan(y/x)-M_PI;
    double new_magComponent = sqrt((x*x) + (y*y));
    return PolarNumber (new_magComponent, new_phaseComponent);
}


PolarNumber PolarNumber::operator * (const PolarNumber& arg){
    PolarNumber result;
    result.magComponent=magComponent*arg.magComponent;
    result.phaseComponent=phaseComponent+arg.phaseComponent;
    return result;
}


PolarNumber PolarNumber::operator / (const PolarNumber& arg)
{
    PolarNumber result;
    result.magComponent=magComponent/arg.magComponent;
    result.phaseComponent=phaseComponent-arg.phaseComponent;
    return result;
}






//Operation overload for PolarNumber (op) RealNumber        
PolarNumber PolarNumber::operator + (const RealNumber& arg) {
    double x, y, add;
    x = magComponent * cos (phaseComponent);
    y = magComponent * sin (phaseComponent);
    //add real components together
    add = x + arg.get_value();
    //resolve back to polar
    double new_phaseComponent = atan(y/add)+M_PI;
    double new_magComponent = sqrt(add*add + y*y);
    return PolarNumber (new_magComponent, new_phaseComponent);
}


PolarNumber PolarNumber::operator - (const RealNumber& arg){
    double x, y, sub;
    x = magComponent * cos (phaseComponent);
    y = magComponent * sin (phaseComponent);
    //add real components together
    sub = x - arg.get_value();
    //resolve back to polar
    double new_phaseComponent = atan(y/sub)+M_PI;
    double new_magComponent = sqrt(sub*sub + y*y);
    return PolarNumber (new_magComponent, new_phaseComponent);
}


PolarNumber PolarNumber::operator * (const RealNumber& arg){
    PolarNumber result;
    result.phaseComponent=phaseComponent;
    result.magComponent=magComponent*arg.get_value();
    return result;
}


PolarNumber PolarNumber::operator / (const RealNumber& arg){
    PolarNumber result;
    result.phaseComponent=phaseComponent;
    result.magComponent=magComponent/arg.get_value();
    return result;
}




//Operation overload for PolarNumber (op) RationalNumber    
PolarNumber PolarNumber::operator + (const RationalNumber& arg) {
    double x, y, add;
    x = magComponent * cos (phaseComponent);
    y = magComponent * sin (phaseComponent);
    //add real components together
    add = x + arg.decimal_value();
    //resolve back to polar
    double new_phaseComponent = atan(y/add);
    double new_magComponent = sqrt(add*add + y*y);
    return PolarNumber (new_magComponent, new_phaseComponent);
}


PolarNumber PolarNumber::operator - (const RationalNumber& arg){
    double x, y, sub;
    x = magComponent * cos (phaseComponent);
    y = magComponent * sin (phaseComponent);
    //add real components together
    sub = x - arg.decimal_value();
    //resolve back to polar
    double new_phaseComponent = atan(y/sub);
    double new_magComponent = sqrt(sub*sub + y*y);
    return PolarNumber (new_magComponent, new_phaseComponent);
}


PolarNumber PolarNumber::operator * (const RationalNumber& arg){
    PolarNumber result;
    result.phaseComponent=phaseComponent;
    result.magComponent=magComponent*arg.decimal_value();
    return result;
}


PolarNumber PolarNumber::operator / (const RationalNumber& arg){
    PolarNumber result;
    result.phaseComponent=phaseComponent;
    result.magComponent=magComponent/arg.decimal_value();
    return result;
}

