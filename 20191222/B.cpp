#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;
 
int main() {
 
	//数字
	int N;
  string S,T;
  string O;
  cin >> N;
  cin >> S >> T;
  O="";
  for(int i=0;i<N;i++){
    O+=S[i];
    O+=T[i]; 
  }
  cout << O << endl;
}