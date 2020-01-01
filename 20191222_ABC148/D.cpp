#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;

int main() {
 
	//数字
   int N;
   cin >> N;
   int A[N];
   int B[N];

   for(int i=0;i<N;i++){
      cin >> A[i];
      B[i]=0;
   }

   int count=1;
   for(int i=0;i<N;i++){
      if(A[i]==count){
         B[count]=i;
         count++;
      }
   }

   int gomi=0;
   //cout << count << endl;
   for(int i=1;i<count;i++){
      if(i==1){gomi=B[i];
      }else{
         gomi+=B[i]-B[i-1]-1;
      }
      //cout << i << endl;
   }
   gomi+=N-B[count-1]-1;
   if(count == 1){
      cout << -1 << endl;
   }
   else{
      cout << gomi << endl;
   }
}