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
 
   long long int X;
   int flag=0;
   cin >> X;
   for(int i=X;i<2*X;i++){
      flag=0;
      for(int j=2;j<=pow(X,0.5);j++){
         if(i%j==0){
            flag=1;
            break;
         }
      }
      if(flag==0){
         cout << i << endl;
         break;
      }
   } 

}