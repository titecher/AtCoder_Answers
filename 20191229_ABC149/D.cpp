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
   long long int K;
   long long int R;
   long long int S;
   long long int P;
   string T;
   string U;


   cin >> N >> K;
   cin >> R >> S >> P;
   cin >> T;
   int* J = new int[N];
   U="";
   for(int i=0;i<N;i++){
      switch (T[i]){
         case 's':
            U+="r";
            J[i]=R;
            break;
         case 'p':
            U+="s";
            J[i]=S;
            break;
         case 'r':
            U+="p";
            J[i]=P;
            break;
      }
   }
   for(int i=0;i<N;i++){
       if(i>=K){
          if(U[i]==U[i-K]){
             U[i]='o';
          }
       }
   }
   // cout << U << endl;
   int poi =0;
   for(int i=0;i<N;i++){
      switch (U[i]){
            case 'p':
               poi+=P;
               break;
            case 'r':
               poi+=R;
               break;
            case 's':
               poi+=S;
               break;
            case 'o':
               poi+=0;
               break;
      }
   }
   cout << poi << endl;
}