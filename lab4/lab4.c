#include <stdio.h>
#include "prime.h"

int main(){
  // Write the code to take a number n from user and print all the prime numbers between 1 and n
	int number;
	//int answer;
	printf("Enter the value of n: ");
	scanf("%d", &number);
	//answer= is_prime(number);
	printf("Printing primes less than or equal to %d:\n" ,number);
	int i;	
	for (i=2;i<=number;i++)
	{
		if(is_prime(i) ==1)
		{
			printf("%d ",i);
		}
	}

  return 0;
}

