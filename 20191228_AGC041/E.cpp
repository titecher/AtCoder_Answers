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
   long long int A;
   long long int B;
   long long int max;
   long long int min;

   cin >> N >> A >> B;
   
   if((B-A)%2==0){
      printf("%lld\n",(B-A)/2);
   }else{
      //差が奇数
      max = N-B;
      min = A-1;
      printf("%lld\n",(B-A-1)/2+(max<min?max:min)+1);
   } 
}