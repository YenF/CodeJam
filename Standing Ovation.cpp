#include<iostream>
#include<string>

using namespace std;

char arr[1010];

int countInvite(int level){
	int ans=0, claps=0;	//鼓掌人數
	for(int i=0; i<=level; i++){
		if(claps>=i) claps+=(arr[i]-48);
		else{
			if(arr[i]=='0') continue;	//可能後面的shylevel沒觀眾，就不需要邀請
			ans+=(i-claps);
			claps+=(arr[i]-48+ans);
		}
	}
	return ans;
}

int main(){
	int cases,level;
	cin>>cases;
	for(int c=1; c<=cases; c++){
		cin>>level;
		cin.ignore(1,' ');
		cin.getline(arr,1010);
		cout<<"Case #"<<c<<": "<<countInvite(level)<<endl;
	}
	return 0;
}