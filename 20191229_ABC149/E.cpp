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
 
   long long int N;
   long long int M;

   cin >> N >> M;
   vector<int> A;
   long long int O;
   for(int i=0;i<N;i++){
      cin >> O;
      A.push_back(O);
   }
   sort(A.begin(),A.end());
   //cout << A[0] << endl;
   vector<int> sum;
   for(int i=0;i<N;i++){
      for(int j=0;j<N;j++){
         sum.push_back(A[i]+A[j]);
      }
   }
   sort(sum.begin(),sum.end());
   int poi=0;
   for(int i=0;i<M;i++){
      poi+=sum[N*N-M+i];
   }
   cout << poi << endl;
}