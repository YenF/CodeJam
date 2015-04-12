#include<iostream>

using namespace std;

bool computeAns(int X, int R, int C){
	if(X==1) return 1;	//隨便都填得進去
	else if(X==2){
		if( (R*C)%2==0 ) return 1;
		else return 0;
	}else if(X==3){
		if( (R*C)%3==0 ){	//只有總塊數可除 還不行
			if(R*C==3) return 0;	
			if(R*C==6) return 1;
			if(R*C==9) return 1;
			if(R*C==12) return 1;
		}else return 0;
	}else if(X==4){
		if( (R*C)%4==0 ){	//只有總塊數可除 還不行
			if(R*C==4) return 0;
			if(R*C==8) return 0;
			if(R*C==12) return 1;
			if(R*C==16) return 1;
		}else return 0;
	}
}

int main(){
	int cases,X,R,C;
	cin>>cases;
	for(int c=1; c<=cases; c++){
		cin>>X>>R>>C;
		cout<<"Case #"<<c<<": ";
		if(computeAns(X,R,C)) cout<<"GABRIEL\n";
		else cout<<"RICHARD\n";
	}
	return 0;
}