#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int main(void) {
  int a,b,x;
  scanf("%d %d %d",&a,&b,&x);
  
  //満杯に近い
  if(x>a*a*b/2)
  {
	printf("%.10f",atan((2.0*b-2.0*x/a/a)/a)/3.14159265358979*180);
  }else{
  	printf("%.10f",atan(a*b*b/2.0/x)/3.14159265358979*180);
  }
}