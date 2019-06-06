#include <bits/stdc++.h>
using namespace std;

int main(){
	freopen("flipflap.in","w",stdout);
	srand((int)time(0));
	int n=999,m=4999;
	cout<<n<<" "<<m<<endl;
	for (int i=1;i<=m;++i){
		int op=rand()%2+1;
		int l=rand()%n+1,r=rand()%n+1;
		if (l>r) swap(l,r);
		if (op==1) cout<<op<<" "<<l<<" "<<r<<" "<<rand()%100<<endl;
		if (op==2) cout<<op<<" "<<l<<" "<<r<<" "<<rand()<<endl;
	}
}
