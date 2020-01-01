#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <utility>
#include <string>
#include <math.h>
#include <algorithm>
#include <cstring>
#include <cctype>

using namespace std;

int main() {
 
	//数字
   long long int N;
   long long int M;
   long long int V;
   long long int P;
   vector<long long int> A;
      vector<long long int> D;
   int* B= new int[1000000000];
   int* C= new int[1000000000];

   cin >> N >> M >> V >> P;
   long long int test;
   for(int i =0;i<N;i++){
      cin >> test;
      A.push_back(test);
      D.push_back(test);
      B[A[i]]+=1;
      C[D[i]]+=1;
   }
   
   sort(A.begin(),A.end());
   sort(D.begin(),D.end());
   int sum=0;
   int k;
   int mm=0;
   for(int i=0;i<M;i++){
         sum=0;
         mm=0;
         for(k=0;k<N;k++){
            sum+=B[A[k]];
            if(sum>V){
               mm=A[k];
               break;
            }
         }
         for(int l=0;l<N;l++){
            if(D[l]<=mm){
               D[l]+=1;
            }else{
               break;
            }
         }
         //sort(A.begin(),A.end());
         C= new int[1000000000];
         for(int i =0;i<N;i++){
            C[D[i]]+=1;
         }
   }
   sort(D.begin(),D.end());
   int max= D[D.size()-1];
   int dum=0;
   int ddd;
   for(int k=max;k>0;k--){
      dum+=C[k];
      if(dum>P){
         ddd=k;
         break;
      }
   }
   max=0;
   for(int k=ddd;k<N;k++){
      if(C[k]>0){max++;};
   }
   cout << dum << endl;
}