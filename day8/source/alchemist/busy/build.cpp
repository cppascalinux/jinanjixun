#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+1;

int n,m;
int a[maxn];

int main(){
	srand((int)time(0));
	freopen("busy.in","w",stdout);
	n=3000,m=3000;
	cout<<n<<" "<<m<<endl;
	for (int i=1;i<=n;++i)
		cout<<rand()%30+1<<" ";cout<<endl;
	for (int i=1;i<=m;++i){
		int op=rand()%2+1;
		int l=rand()%30+1,r=rand()%30+1;
		cout<<op<<" "<<l<<" "<<r<<endl;
	}
}
