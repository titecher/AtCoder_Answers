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
/*
	// recieve |V| and |E|
	int V, E; std::cin >> V >> E;
	int G[V][V];
	
	for(int i = 0; i < E; i++) {
		// recieve edges
		int u, v, d; std::cin >> u >> v >> d;
		u--; v--;
		G[u][v]=d;
		G[v][u]=d;
	}
	
	int Tmax; std::cin >> Tmax;
	//int ReceiveOrd[Tmax];
	std::vector<std::pair<int, int>> ReceiveOrd;
	std::vector<int> OrdDetail;
	// recieve info
	for(int i = 0; i < Tmax; i++) {
		int Nnew; std::cin >> Nnew;
		for(int j = 0; j < Nnew; j++) {
			int new_id, dst; std::cin >> new_id >> dst;
			ReceiveOrd.push_back({new_id-1,dst});
			OrdDetail.push_back(dst);
		}
		ReceiveOrd.push_back({0,-1});
	}
	
	// for(int i = 0; i < Tmax; i++) {
	// 	if(ReceiveOrd[i].first>0){
	// 		std::cout << i << " " << ReceiveOrd[i].second << std::endl;
	// 	}
	// }

	//復習
	//G[i][j]：ノードiのj番目のリンクは、G[i][j].firstへ距離G[i][j].secondでつながる
	//ReceiveOrd[i]：時刻iに発生した注文の番号と位置。なかったら{0,-1}が入る。

	//車の定義
	//ノード上にいるかどうか。
	int OriginNode = 0;
	int TargetNode = -1;
	int Cargo[V]={};
	int Store[V]={};

	int Dest=-1;
	int OnRoad;

	//活動内容
	//対応中の注文
	int ActiveOrder;
	//処理済み
	int DeadOrder[Tmax]={};
	//
	std::vector<int> InCargoOrder;
	std::vector<int> InStoreOrder;

	for(int time=0;time<1000;time++){

		/////注文処理
		//注文があったら、倉庫にストック
		if(ReceiveOrd[time].first>0){
			Store[ReceiveOrd[time].second]+=1;
			InStoreOrder.push_back(ReceiveOrd[time].first);
		}

		//車の座標が原点なら積む
		if(OriginNode == 0 && TargetNode == -1){

			for(int j=0;j<V;j++)
			{
				Cargo[j]+=Store[j];
				Store[j]=0;
			}
			if(InStoreOrder.size()>0){
			InCargoOrder.insert(InCargoOrder.end(),InStoreOrder.begin(),InStoreOrder.end());
			InStoreOrder.clear();
			}
		}

		/////活動ターン
		//対応中の行動がnai
		if(Dest==-1){
		//Cargoがなければ倉庫へ
			if(InCargoOrder.size()==0){
				//原点に戻る。
				Dest=0;
				//現在点から原点までのルートを出す。
				//TargetNode=NextPath(OriginNode,Dest);///XXX
				//方向設定
				OnRoad=G[OriginNode][TargetNode];
			}else{
				//Activeな注文を設定
				//一番、古いCargo注文を取り出す。
				ActiveOrder = InCargoOrder.front();    
				InCargoOrder.erase(InCargoOrder.begin()); 
				//注文の行き先を設定

				//方向設定
			}
		}

		//方向に向けて１	 
		//到着地点の判定
			//道中なら終わり
			//顧客に着いたら、配達中配達品を消す
			//原点に着いたら、
		
		//1回の活動終了
	}

	// std::cout <<"tt "<< InStoreReceiveOrder.size() <<" " << InCargoReceiveOrder.size()<< std::endl;
	// for(int i = 0; i < InStoreReceiveOrder.size(); i++) {
	// 	std::cout <<"S "<< i << " " << InStoreReceiveOrder[i] << std::endl;
	// }
	// for(int i = 0; i < InCargoReceiveOrder.size(); i++) {
	// 	std::cout <<"C "<< i << " " << InCargoReceiveOrder[i]<< std::endl;
	// }

	//Position

	//Head
	//G[OriginNode][0].first
	//PriorReceiveOrd

	//ReceiveOrders


	//std::cout << G[V-1][E-1].first << " " << G[V-1][E-1].second << std::endl;
  // insert your code here to get more meaningful output
	// all stay
	//for(int i = 0; i < Tmax; i++) std::cout << -1 << std::endl;
	return 0;
}
