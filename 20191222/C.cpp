#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;
 
long long int gcd(long long int a, long long int b) { 
   if (b == 0) 
      return a; 
   return gcd(b, a % b);  
} 
int main() {
 
	//数字
	long long int A,B;
  cin >> A >> B;
  long long int d=1;
  d=gcd(A,B);
  long long int q= A/d*B;
  cout << q << endl;

}