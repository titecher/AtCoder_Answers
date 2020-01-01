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
   cin >> N;

   if(N%2==1){
      cout << 0 << endl;
   }else{
   long long int M;
   long long int S=0;
   
   for(int i=1;i<100;i++){
      M=2*(long long int)pow(5,i);
      if(M>N){break;}
      S+=N/M;
     // cout << i<<" "<<S << endl;
   }
   cout << S << endl;
   }
 //  cout <<N <<" = " << (int)N/((int)pow(5,M)) << "*5**"<< M << "+"<< N-((int)N/((int)pow(5,M))*(int)pow(5,M)) << endl;
 
}