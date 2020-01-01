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
 
   long long int A;
   long long int B;
   long long int K;

   cin >> A >> B >> K;
   
   cout << (K-A>0?0:A-K) << " " << (K-A>0?(B-(K-A)>=0?B-(K-A):0):B) << endl;
}