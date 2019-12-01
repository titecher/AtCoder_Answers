#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int asc(const void *a, const void *b);
int desc(const void *a, const void *b);

int main(void) {

//int N;
//int *A;
//scanf("%d", &N);
/*
  A = (int *)calloc(N,sizeof(int));
  for(i=0;i<N;i++)
  {
  	scanf("%d", &A[i]);
  }
  qsort(A, N, sizeof(int), asc);
*/


}

int asc(const void *a, const void *b) {
  return *(int *)a - *(int *)b;
}
int desc(const void *a, const void *b) {
  return *(int *)b - *(int *)a;
}
