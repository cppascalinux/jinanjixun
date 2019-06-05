#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+1;

int n,m;
int a[maxn];

int main(){
	srand((int)time(0));
	freopen("save.in","w",stdout);
	n=100000,m=100000;
	cout<<n<<" "<<m<<endl;
	for (int i=1;i<=n;++i)
		cout<<rand()<<" ";cout<<endl;
	for (int i=1;i<=m;++i){
		int op=rand()%2?1:3;
		int l=rand()%n+1,r=rand()%n+1;
		if (l>r) swap(l,r);
		cout<<op<<" "<<l<<" "<<r<<" ";
		if (op==1) cout<<rand();
		cout<<endl;
	}
}
