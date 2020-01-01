#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;
 
int main() {
 
	//数字
	int A,B;
	int N[3]={1,1,1};
  cin >> A >> B;
  N[A-1]=0;
  N[B-1]=0; 
  for(int i=0;i<3;i++){
    if(N[i]>0) cout << i+1 << endl;; 
  }
}