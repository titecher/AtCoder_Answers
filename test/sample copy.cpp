#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;

int main() {

	int X,Y
	cin >> X >> Y;
	int award=0;

	if(X==3){
		award+=100000;
	}else if(X==2){
		award+=200000;
	}else if(X==1){
		award+=300000;
	}
	
		if(Y==3){
		award+=100000;
	}else if(Y==2){
		award+=200000;
	}else if(Y==1){
		award+=300000;
	}

	if(X==1 && Y==1){
		award+=400000;
	}

	cout << award << endl;


/*

*/

}