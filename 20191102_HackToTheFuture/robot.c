#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int K;
int maxstep=30;
//方向指示器
int *Drx,*Dry,*Drd;
int *Rx,*Ry,*Rd;
int *Bx,*By;

int N,M,B;
int Gx,Gy;

//ゴール
int Goal(int R){
	if(Rx[R]==Gx && Ry[R]==Gy){
    	return 1;
    }else{
    	return 0;
    }
}

//ロボiがぶつかってるかどうか
int Bar(int R)
{	
  	int i;
  	for(i=0;i<B;i++)
    {
		if((Rx[R]+1+N)%N==Bx[i] && Ry[R]==By[i] && Rd[R]==0){
        	return 1;
        }else if(Rx[R]==Bx[i] && (Ry[R]-1+N)%N==By[i] && Rd[R]==1){
        	return 1;
        }else if((Rx[R]-1+N)%N==Bx[i] && Ry[R]==By[i] && Rd[R]==2){
        	return 1;
        }else if(Rx[R]==Bx[i] && (Ry[R]+1+N)%N==By[i] && Rd[R]==3){
        	return 1;
        }else{
        	return 0;
        }
    }
}

void Dir(int R){
	int i;
  	//方向指示器による更新
	for(i=0;i<K;i++)
    {
    	if(Rx[R]==Drx[i] && Ry[R]==Dry[i]){
	          Rd[R]=Drd[i];
    	}
    }
}
  
void Mov(int R){
	//向きによる位置の更新
	switch(Rd[R]){
          case 0:
            Rx[R]=(Rx[R]+1+N)%N;
            break;
          case 1:
            Ry[R]=(Ry[R]-1+N)%N;
            break;
          case 2:
            Rx[R]=(Rx[R]-1+N)%N;
            break;
          case 3:
            Ry[R]=(Ry[R]+1+N)%N;
            break;  
        }
}

int main(void) {
	int i;
  	int step;
    scanf("%d %d %d\n",&N,&M,&B);
	scanf("%d %d\n",&Gx,&Gy);
  	
  	Rx= (int *)calloc(M,sizeof(int));
	Ry= (int *)calloc(M,sizeof(int));
	Rd= (int *)calloc(M,sizeof(int));
  	Bx= (int *)calloc(B,sizeof(int));
	By= (int *)calloc(B,sizeof(int));
	//ろぼ

  	char Rtest[M];
    for(i=0;i<M;i++)
    {
      scanf("%d %d %s\n", &Rx[i],&Ry[i],&Rtest[i]);
    }
  	for(i=0;i<M;i++)
    {
  		switch(Rtest[i]){
          case 'U':
            Rd[i]=1;
            break;
          case 'D':
            Rd[i]=3;
            break;
          case 'L':
            Rd[i]=0;
            break;
          case 'R':
            Rd[i]=2;
            break;  
        }
    }
  
  	//ばりあ

    for(i=0;i<B;i++)
    {
      scanf("%d %d\n", &Bx[i],&By[i]);
    }
  	//読み込み
  	
  	Drx= (int *)calloc(K,sizeof(int));
	Dry= (int *)calloc(K,sizeof(int));
	Drd= (int *)calloc(K,sizeof(int));
  	
  	//方向指示器暫定
  	K=2;
  	for(i=0;i<K;i++){
    	Drx[0]=5;Dry[0]=8;Drd[0]=1;
        Drx[1]=2;Dry[1]=5;Drd[1]=2;
    }
  
  	//
  
  
  	//
  	printf("%d %d %d %d %d %d\n",0,Rx[1],Ry[1],Rd[1],Bar(1),Goal(1));
  	for(step=1;step<maxstep;step++)
    {
    	//ロボ更新
      	for(i=0;i<M;i++)
        {
          	//動けない判定があれば次のロボット
          	if(Bar(i)==1 || Goal(i)==1){
            	break;
            }else{
              //方向の更新
            	Dir(i);
              //向きの方向に進む
            	Mov(i);
            }
        }
      	//test
    }
}