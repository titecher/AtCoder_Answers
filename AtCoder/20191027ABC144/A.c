#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void) {
  int A,B;
  scanf("%d %d", &A,&B);
  
  if(A>9 || B>9)
  {
    printf("%d",-1);
  }else{
  	printf("%d",A*B);
  }
}