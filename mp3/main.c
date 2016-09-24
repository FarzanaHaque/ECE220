#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* we are given the approximate solution of vout(n+1) which requires knowing vout(n-1) & vout (n), I wrote a for loop that goes n + 1 (0 to N) times, and prints the value of the Voutcurr each time, during each loop i'd make sure to update voutprev to voutcur, and voutcur to voutnew
*/
int main()
{
	double omega1, omega2, omegac, T, dt;
	int N;

	//Scan the inputs from the user.
	scanf("%lf %lf %lf", &omega1, &omega2, &omegac);
	
	T = 3 * 2 * M_PI / omega1;      // Total time
    	N = 20 * T / (2 * M_PI / omega2);   // Total number of time steps
    	dt = T / N;             // Time step

	int i;
	double Voutnew = 0, Voutcur = 0, Voutprev = 0;
	//printf("Entering Loop\n");
	//Write your code here!

	for(i=0;i<=N;i++)
	{//This is the equation given which I broke into parts to increase readability & debugging purposes
		Voutnew=((1/((sqrt(2))*dt*omegac))-(1/(dt*dt*omegac*omegac)))*Voutprev;
		Voutnew=Voutnew+(((2/(dt*dt*omegac*omegac)) -1)*Voutcur);
		Voutnew=Voutnew +sin((omega1*i*dt))+0.5*sin((omega2*i*dt));
		Voutnew=Voutnew* (1/(((1/(((sqrt(2))*dt*omegac))) +(1/(dt*dt*omegac*omegac))))); //+ parenthesis
		

	printf("%lf\n",Voutcur); //print out V(n)
	Voutprev=Voutcur; //update voutprev
	Voutcur=Voutnew; //update voutcur
        


	}


	return 0;
}

