#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <math.h>

using namespace std;
long long int H,W,K,V;
int **vis;
long long int **A;
long long int **B;
long long int LL,RR,TT,BB;
void search(int a,int b);
long long int rech(int a,int b);

void search(int a,int b){
    long long int money=V;
  	int flag=0;
	if(a!=0 && b!=0 && a<=H && b<=W)
	{
  	if(vis[a-1][b]==0 && rech(a-1,b)<V){
    	vis[a-1][b]=1;
		//cout << "f1" << rech(a-1,b) << endl;
        if(money>rech(a-1,b)){
        	money=rech(a-1,b);
          	flag=1;
        }
    }
	
  	if(vis[a][b-1]==0 && rech(a,b-1)<V ){
    	vis[a][b-1]=1;
		//cout << "f2"<< rech(a,b-1) << endl;
        if(money>rech(a,b-1)){
        	money=rech(a,b-1);
          	flag=2;
        }
    }
  	if(vis[a+1][b]==0 && rech(a+1,b)<V){
    	vis[a+1][b]=1;
		//cout << "f3"<< rech(a+1,b) << endl;
        if(money>rech(a+1,b)){
        	money=rech(a+1,b);
          	flag=3;
        }
    }
  	if(vis[a][b+1]==0 && rech(a,b+1)<V){
    	vis[a][b+1]=1;
		//cout << "f4"<< rech(a,b+1) << endl;
        if(money>rech(a,b+1)){
        	money=rech(a,b+1);
          	flag=4;
        }
    }
	}
	switch (flag) {
		case 1:
			for(int i=(TT>a-1?a-1:TT);i<(BB>a-1?BB:a-1)+1;i++){
	 	 	for(int j=(LL>b?b:LL);j<(RR>b?RR:b)+1;j++){	
				B[i][j]=1;
   				}
    		}
        	TT--;
			search(a-1,b);
			break;
		case 2:
			for(int i=(TT>a?a:TT);i<(BB>a?BB:a)+1;i++){
	 	 		for(int j=(LL>b-1?b-1:LL);j<(RR>b-1?RR:b-1)+1;j++){	
					B[i][j]=1;
   				}
    		}
        	LL--;
			search(a,b-1);
        	break;
       	case 3:
			for(int i=(TT>a+1?a+1:TT);i<(BB>a+1?BB:a+1)+1;i++){
	 	 		for(int j=(LL>b?b:LL);j<(RR>b?RR:b)+1;j++){	
					B[i][j]=1;
   				}
    		}
        	BB++;
			search(a+1,b);
        	break;
        case 4:
			for(int i=(TT>a?a:TT);i<(BB>a?BB:a)+1;i++){
	 	 		for(int j=(LL>b+1?b+1:LL);j<(RR>b+1?RR:b+1)+1;j++){	
					B[i][j]=1;
   				}
    		}
        	RR++;
			search(a,b+1);
        	break;
		default:
//			cout << "error";
			break;
	}
  	
}

long long int rech(int a,int b){
  	long long int sum=0;
  	long long int area=0;
	 for(int i=(TT>a?a:TT);i<(BB>a?BB:a)+1;i++){
	  	for(int j=(LL>b?b:LL);j<(RR>b?RR:b)+1;j++){	
    		sum += A[i][j];
          	area++;
   		}
    }
	return(sum+area*K);
}


int main() {

  	cin >> H >> W >> K >> V;

  	vis=new int*[W];
  	for (int i = 0; i < H; i++) {
    vis[i] = new int[W];
    }
  	A=new long long int*[W];
  	for (int i = 0; i < H; i++) {
    A[i] = new long long int[W];
    }
  	B=new long long int*[W];
  	for (int i = 0; i < H; i++) {
    B[i] = new long long int[W];
    }

  	long long int min=1000000000;
	int minH,minW;
  	for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
  		cin >> A[i][j];
        vis[i][j]=0;
        if(min>A[i][j]){
			min=A[i][j];
        	minH=i;
            minW=j;
        }
        }
    }

  	LL=minW;
  	RR=minW;
  	TT=minH;
	BB=minH;
  	//cout << "test" << endl;
	//cout << minW <<" "<< minH << endl;
	for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
  			//cout << A[i][j] << " ";
        }
      		//cout << endl;
    }
	if(A[minH][minW]+K<V){
	B[minH][minW]=1;
  	vis[minH][minW]=1;
	//cout << LL <<" "<< RR <<" " << TT <<" "<< BB << endl;
	search(minH,minW);
	}
    //cout << "test" << endl;  
  	//cout << LL <<" "<< RR <<" " << TT <<" "<< BB << endl;
	for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
  			//cout << vis[i][j];
        }
      		//cout << endl;
    }
  //cout << LL <<" "<< RR <<" " << TT <<" "<< BB << endl;
	long long int sum=0;
	int aaa=0;
	for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
  			//cout << B[i][j];
			sum+=B[i][j]*A[i][j];
			aaa+=B[i][j];
        }
      		//cout << endl;
    }
	//cout << sum <<" "<< sum+aaa*K << endl;
	cout << aaa << endl;
}