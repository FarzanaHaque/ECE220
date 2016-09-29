#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* I wrote a program implementing halley's method to solve for the roots for a given 4th degree polynomial
First i had to implement 6 functions, absolute value, evaluating a polynomial, evaluating the 1st degree,2nd degree derivative, finding the upper bound of the number of roots and halley's method. we're given a,b,c,d,e,l,r from our file. if the upper bound of # of roots is zero or less then we know we have no roots in the given interval
otherwise we should for the root using halley's method. we use an x starting at l. Each time we call halley's method we print a line. Halley's method works by making xnew a function of xold, we update xnew during every loop in the newfindr function. If xnew-xold <0.000001 we know it's accurate enough for us and xnew is our root. If after 10,000 iteration of the halley loop for a given intial x, we know there's probably not a root in the given interval. Everytime we print a line from the newrfind_halley function, then we increment x by 0.5 and call newrfind_halley until x reaches r. THus finding all the roots of the polynomial in the given interval l to r.
*/
double abs_double(double y)
{
    //Change this to return the absolute value of y i.e |y|
	if(y<0) //y is negative
		return (y*-1); //return additive inverse
	else
		return y; //otherwise return the same
    return 0;
}

double fx_val(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the polynomial at the value x
	return a*(pow(x,4))+b*(pow(x,3))+c*(pow(x,2))+d*x+e;    //ax^4+bx^3+cx^2+dx+e
	return 0;
}

double fx_dval(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the derivative of the polynomial at the value x
 	//derivative = 4ax^3+3bx^2+2cx+d 
	return 4*a*(pow(x,3))+3*b*x*x+2*c*x+d; 
 return 0;
}

double fx_ddval(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the double derivative of the polynomial at the value x
	//12ax^2+6bx+2c
	return 12*a*x*x+6*b*x+2*c    ;
	return 0;
}


double newrfind_halley(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the root found starting from the initial point x using Halley's method
int i=0; //checks how many iterations of halley we've done
int roots=1; //automatically set to one if we do 1000 iteration and no roots then we set roots? to 0
    double xold=x; //set xold to original x
	double xnew=xold-(2*fx_val(a,b,c,d,e,xold)*fx_dval(a,b,c,d,e,xold))/(2*pow(abs_double(fx_dval(a,b,c,d,e,xold)),2)-fx_val(a,b,c,d,e,xold)*fx_ddval(a,b,c,d,e,xold)); //given equation
while((((abs_double(xnew-xold))>0.000001)&&(i<10000))) 
{
xold=xnew; //updates xold
xnew=xold-(2*fx_val(a,b,c,d,e,xold)*fx_dval(a,b,c,d,e,xold))/(2*pow(abs_double(fx_dval(a,b,c,d,e,xold)),2)-fx_val(a,b,c,d,e,xold)*fx_ddval(a,b,c,d,e,xold)); //equation again
i=i+1;//increment i
if (i>=10000)
{
	printf("No roots found.\n"); //did 10,000 tries still no roots, probably diverging bc do nearby root
	roots=0;
}
}
if(roots) //if roots still equals 1 then you know the progam terminated bc found xnew extremely close to xold aka a root
printf("Root found: %lf\n",xnew);
	return 0;
}

int rootbound(double a, double b, double c, double d, double e, double r, double l)
{
    //Change this to return the upper bound on the number of roots of the polynomial in the interval (l, r)
	double vl=0;
	//set the first cooeficient as co1 and onward
	double co1=a;
	double co2=4*a*l+b;
double co3= 6*a*l*l+3*b*l+c;
double co4=4*a*l*l*l+2*b*l*l+3*c*l+d;
double co5=a*l*l*l*l+b*l*l*l+c*l*l+d*l+e; //these are the coefficients for p(x+l)
if((co1*co2)<0) 
	vl=vl+1; //there's only a sign change if the product of 2 coefficients next to each other are negative
if((co3*co2)<0)
	vl=vl+1;
if((co3*co4)<0)
	vl=vl+1;
if((co4*co5)<0)
	vl=vl+1;
//now same for r
	double vr=0;
	double co1r=a;
	double co2r=4*a*r+b;
double co3r= 6*a*r*r+3*b*r+c;
double co4r=4*a*r*r*r+2*b*r*r+3*c*r+d;
double co5r=a*r*r*r*r+b*r*r*r+c*r*r+d*r+e; //these are the coefficients for p(x+l)
if((co1r*co2r)<0) 
	vr=vr+1;
if((co3r*co2r)<0) 
	vr=vr+1;
if((co3r*co4r)<0) 
	vr=vr+1;
if((co4r*co5r)<0) 
	vr=vr+1;    
int answer=abs_double((vl-vr)); 
return answer;
return 0;
}

int main(int argc, char **argv)
{
	double a, b, c, d, e, l, r;
	FILE *in;

	if (argv[1] == NULL) {
		printf("You need an input file.\n");
		return -1;
	}
	in = fopen(argv[1], "r");
	if (in == NULL)
		return -1;
	fscanf(in, "%lf", &a);
	fscanf(in, "%lf", &b);
	fscanf(in, "%lf", &c);
	fscanf(in, "%lf", &d);
	fscanf(in, "%lf", &e);
	fscanf(in, "%lf", &l);
	fscanf(in, "%lf", &r);
    
    //The values are read into the variable a, b, c, d, e, l and r.
    //You have to find the bound on the number of roots using rootbound function.
    //If it is > 0 try to find the roots using newrfind function.
    //You may use the fval, fdval and fddval funtions accordingly in implementing the halleys's method.
 if(rootbound(a,b,c,d,e,r,l)>=0) //means upper bound of roots in interval is zero or negative aka there are no roots
	printf("The polynomial has no roots in the given interval");
 else 
{
	double x=l; //starting value of x
	while(x<=r) //ending value of x
{
	newrfind_halley(a,b,c,d,e,x); //do halley's method
	x=x+0.5; //increase x by step size of 0.5
}
}   
    fclose(in);
    
    return 0;
}
