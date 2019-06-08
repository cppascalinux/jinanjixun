#include <bits/stdc++.h>
using namespace std;

int main(){
	freopen("loopy8.in","r",stdin);
	freopen("loopy8.ans","w",stdout);
	int n,gap=0;
	cin>>n;
	cout<<n<<"x"<<n<<"t0:";
	for (int i=1,x;i<=n*n;++i){
		cin>>x;
		if (x==-1) gap++;
		else{
			if (gap) cout<<(char)('a'+gap-1);
			cout<<x;gap=0;
		}
	}
	if (gap) cout<<(char)('a'+gap-1);
}
