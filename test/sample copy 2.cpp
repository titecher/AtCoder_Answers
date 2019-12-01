#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <math.h>

using namespace std;

int main() {

	int H,W,K;
  	cin >> H >> W >> K;
  	char A[H][W];
   	int Area[H][W];
  	int Y[K],X[K];
  	int k=0;	
  for(int i=0;i<H;i++){
        for(int j=0;j<H;j++){
  		cin >> A[i][j];
        Area[i][j]=0;
        if(A[i][j]=="#")
        {
        	X[k]=j;
          	Y[k]=i;
          	k++;
        }
        }
    }
  
  	int AreaRight[K];
	int AreaLeft[K];
  int AreaTop[K];
  int AreaBottom[K];
  
  	for(int i=0;i<1;i++)
    {
    	cout << X[i] <<" "<< Y[i] << endl;
      	
      	for(int i=0;i<H;i++){
        	for(int j=0;j<H;j++){
  				Area[i][j];
        	}
 		}
      	
      	if(X[i]!=0 && A[X[i]-1][Y[i]]==".")
        {
        	check()
        }
    }
  
  	cout << A[0][1] << endl;
}