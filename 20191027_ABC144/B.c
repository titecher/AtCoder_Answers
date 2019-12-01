#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void) {
  int A;
  scanf("%d", &A);
  int i,flag=0;
  for(i=1;i<10;i++)
  {
  	if((int)(A/i)*i==A && (int)(A/i)<10)
    {
   		flag = 1;
    }
  }
  if(flag == 1)
  {
	  printf("Yes");
  }else{
  		printf("No");
  }
}