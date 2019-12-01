#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <math.h>
using namespace std;
 
int main() {
 
	//数字
	int N;
  int flag=0;
	cin >> N;

  //1円からN円まで8%の税たすといくらになるか総当たり
  int i;
	for(i=1;i<=N;i++){
      if((i*1.08)-N<1.0 && (i*1.08)>=N){
  	    cout << i << endl;
         flag=1;
         break;
        }
    }
  if(flag==0){
  	    cout << ":(" << endl;
  }
}
