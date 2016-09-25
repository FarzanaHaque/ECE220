#include "prime.h"
#include <math.h>
//int main(){}
int is_prime(int n){
int i;
int answer=1;
  // Return 1 if n is a prime, and 0 if it is not
 for(i=2;i<n;i++)
{
 if((fmod(n,i)==0))
  {
	answer=0;

  }
 }
return answer;
  return 0;
}

