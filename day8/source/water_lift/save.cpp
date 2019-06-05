#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[100001];
int main(){
	freopen("save.in","r",stdin);
	freopen("save.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	while(m--){
		int op,l,r;
		cin>>op>>l>>r;
		if(op==1){
			int x;
			cin>>x;
			for(int i=l;i<=r;i++){
				a[i]^=x;
			}
		}
		if(op==2){
			sort(a+l,a+r+1);
		}
		if(op==3){
			int ans=0;
			for(int i=l;i<=r;i++)ans^=a[i];
			cout<<ans<<endl;
		}
	}
}
