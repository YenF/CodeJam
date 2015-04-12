#include<iostream>

using namespace std;

int dinerA[1500],dinerB[1500],ansB,ansA;
int shiftCostA[1500],shiftCostB[1500];

bool roundB(int maxD){	//end or not
	int maxDiner=0, maxCount=0;
	for(int i=0; i<maxD; i++){
		//maxDiner = diner[maxDiner]<diner[i]?i:maxDiner;
		if(dinerB[maxDiner]<dinerB[i]){
			maxDiner=i;
			maxCount=shiftCostB[maxDiner];
		}else if(dinerB[maxDiner]==dinerB[i]){
			maxCount+=shiftCostB[i];	//shift大變動!!  希望不要亂掉
		}
	}
	//找到maxDiner之後，考慮要不要將其/2
	if(dinerB[maxDiner]%2!=0){	//奇數 or 8888 -> 4444 = 4min OK, 88888-> 44444 = 5min+4 -> notOK
		for(int i=0; i<maxD; i++){
			if(dinerB[i]!=0) dinerB[i]--;	//不想要出現負數
		}
		for(int i=0; i<maxD; i++){
			if(dinerB[i]!=0) return 0;
		}
		return 1;	//所有人都是0了-> end
	}
	if(dinerB[maxDiner]/2+shiftCostB[maxDiner]<dinerB[maxDiner] && dinerB[maxDiner]/2>maxCount){	//舉過些小例子，先分再-1 跟 -1再分 分鐘數是一樣的
		//要/2
		dinerB[maxDiner]/=2;
		ansB+=shiftCostB[maxDiner]-1;
		shiftCostB[maxDiner]*=2;	//只能shift一次 (隱藏在外面的一半數字讓原本的diner不能shift第二次) 每次shift+1 cost
		return 0;
	}else{
		for(int i=0; i<maxD; i++){
			if(dinerB[i]!=0) dinerB[i]--;	//不想要出現負數
		}
		for(int i=0; i<maxD; i++){
			if(dinerB[i]!=0) return 0;
		}
		return 1;	//所有人都是0了-> end
	}
}

bool roundA(int maxD){	//end or not
	int maxDiner=0, maxCount=0, secondDiner=0;
	for(int i=0; i<maxD; i++){
		//maxDiner = diner[maxDiner]<diner[i]?i:maxDiner;
		if(dinerA[maxDiner]<dinerA[i]){
			maxDiner=i;
			maxCount=shiftCostA[maxDiner];
		}else if(dinerA[maxDiner]==dinerA[i]){
			maxCount+=shiftCostA[i];	//shift大變動!!  希望不要亂掉
		}
	}
	//找到maxDiner之後，考慮要不要將其/2
	int div=1, addMin=1000000;
	for(int i=1; i<=dinerA[maxDiner]/2; i++){
		if(dinerA[maxDiner]%i!=0) continue;	//除不進就不做
		//addMin=min(addMin,i+diner[maxDiner]/i);
		if(addMin>=i+(dinerA[maxDiner]/i-1)*maxCount){
			addMin = i+(dinerA[maxDiner]/i-1)*maxCount;
			div = i;
		}//div是最後數字
	}		

		//splitCost           * 個數   + 剩下cake數量(min) < 原本min
	if((dinerA[maxDiner]/div-1)*maxCount+			div		<dinerA[maxDiner]-1){	//舉過些小例子，先分再-1 跟 -1再分 分鐘數是一樣的
		ansA+=(dinerA[maxDiner]/div-1);
		shiftCostA[maxDiner]+=(dinerA[maxDiner]/div-1);	//只能shift一次 (隱藏在外面的一半數字讓原本的diner不能shift第二次) 每次shift+1 cost
		dinerA[maxDiner]=div;	// 9/3 = 3, splitCost 2
		return 0;
	}else{
		ansA++;
		for(int i=0; i<maxD; i++){
			if(dinerA[i]!=0) dinerA[i]--;	//不想要出現負數
		}
		for(int i=0; i<maxD; i++){
			if(dinerA[i]!=0) return 0;
		}
		return 1;	//所有人都是0了-> end
	}
}

int main(){
	int cases, diners, maxCake;
	cin>>cases;
	for(int c=1; c<=cases; c++){
		ansA=0; maxCake=0; ansB=0;
		cin>>diners;
		for(int i=0; i<diners; i++){ shiftCostA[i]=1; shiftCostB[i]=1; }
		for(int i=0; i<diners; i++){
			cin>>dinerA[i];
			if(dinerA[i]>maxCake) maxCake=dinerA[i];
		}
		memcpy(dinerB,dinerA,sizeof(dinerA));
		while(!roundA(diners)) ;
		ansB++;
		while(!roundB(diners)) ansB++;
		if(ansA>maxCake) ansA=maxCake;
		if(ansB>maxCake) ansB=maxCake;
		if(ansA>ansB) cout<<"Case #"<<c<<": "<<ansB<<endl;
		else cout<<"Case #"<<c<<": "<<ansA<<endl;
		
	}
	return 0;
}