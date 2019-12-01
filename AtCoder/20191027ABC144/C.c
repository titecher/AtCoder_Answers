#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int main(void) {
  long int A;
  scanf("%ld", &A);
  double aa = pow(A,0.5);
  long int i;
  long int fac,tor,dist;
  dist = A;
  //printf("%f\n",aa);
  for(i=1;i<aa+1;i++)
  {
  	if(((long int)A/i)*i==A)
    {
   		fac =i;
      	tor =((long int)A/i);
      	if(dist > fac + tor - 2)
        {
          	printf("%ld %ld %ld %ld\n",i,((long int)A/i),dist,fac + tor - 2);
        	dist = fac + tor - 2;	
        }
    }
  }
	printf("%ld",dist);
}