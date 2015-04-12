#include<iostream>
#include<string>

using namespace std;

string s;
char ch[10010];
char searchCH[3] = {'i','j','k'};

class Quaternion{
public:
	char CH;
	int minus;
	Quaternion():minus(1){}
	Quaternion(char c):CH(c),minus(1){}
};

Quaternion Q[10000][10000];

Quaternion mulChar(Quaternion a, char b){
	if(a.CH=='i'){
		if(b=='i'){ a.CH='1'; a.minus=-a.minus; }
		else if(b=='j'){ a.CH='k'; }
		else if(b=='k'){ a.CH='j'; a.minus=-a.minus;}
	}else if(a.CH=='j'){
		if(b=='i'){ a.CH='k'; a.minus=-a.minus; }
		else if(b=='j'){ a.CH='1'; a.minus=-a.minus; }
		else if(b=='k'){ a.CH='i'; }
	}else if(a.CH=='k'){
		if(b=='i'){ a.CH='j'; }
		else if(b=='j'){ a.CH='i'; a.minus=-a.minus; }
		else if(b=='k'){ a.CH='1'; a.minus=-a.minus;}
	}else if(a.CH=='1'){
		a.CH=b;	//minus不用管
	}
	return a;
}

bool computeAns(Quaternion nowCH, int search, int ind){
	int indexI,indexJ,indexK;
	bool flag=0;
	if(search>2) return 0;
	if(ind==s.length()){	//已經超過最後一個了 不能用
		if(nowCH.CH==searchCH[2] && search==2 && nowCH.minus==1) return 1;
		else return 0;
	}

	while(ind<s.length()){
		if(nowCH.CH==searchCH[search] && nowCH.minus==1){	//找到要找的文字了 且 沒有負號
			//if(computeAns(Quaternion(s[ind]),search+1,ind+1)) return 1;
			if(search==0) indexI=ind;	//i若要繼續搜尋，從此ind開始
			else if(search==1) indexJ=ind;
			else if(search==2) indexK=ind;
			search++;
			flag=1;
		}
		if(flag){ nowCH=Quaternion(s[ind+1]); flag=0; }
		else nowCH=mulChar(nowCH,s[ind]);
		//找下一個字母，或是繼續看這字母更長
		ind++;
	}
	if(nowCH.CH==searchCH[2] && search==2 && nowCH.minus==1) return 1;
	else return 0;

}

int main(){
	int cases,L,X;
	string tmp;
	//char tmp[10010];
	cin>>cases;
	for(int c=1; c<=cases; c++){
		cin>>L>>X;
		//cin.ignore(5,'\n');
		cin>>tmp;
		//cin.getline(tmp,10005);
		s.clear();
		cout<<"Case #"<<c<<": ";
		if(L==1){ cout<<"NO\n"; continue; }
		for(int i=0; i<X; i++) s.append(tmp);
		if(computeAns(Quaternion(s[0]),0,1)) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}