#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

int s(int x) {
//YOUR CODE STARTS HERE
if (x==0){
return 0;
}
else
return(x%10+s(x/10));

}

int recursive_sum(int x) {
//YOUR CODE STARTS HERE
if(x>=10)
{
return(recursive_sum(s(x)));
}
else
return x;
}

// Function: main
int main(int argc, char** argv) {

  int x;
  while(scanf("%d", &x) == 1) {
    printf("%d\n", recursive_sum(x));
  }

  return 1;
}


