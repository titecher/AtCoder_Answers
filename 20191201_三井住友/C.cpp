#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;
 
int main() {
 
	//数字
  //与えられた数字を100で割ると使うカードの枚数。
  //すべて100、すべて105とする選び方で最小、最大が定まる。
  //その間の数はすべてできる
  //2000以降は何でもできる
	int X;
	cin >> X;
  	int ss=X/100;
  	if(X>=ss*100 && X<=ss*105)
    {
    cout << 1 << endl;
    }else{
    cout << 0 << endl;
    }
}