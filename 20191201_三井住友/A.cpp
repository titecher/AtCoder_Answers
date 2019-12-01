#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;
 
int main() {
 
	//数字
	int X,Y,A,B;
	cin >> X >> Y;
  cin >> A >> B;

  //月が変わっていたら月末
	if(X!=A){
    cout << 1 << endl;
    }else{
    cout << 0 << endl;
    }
}