#include<bits/stdc++.h>
#define ll long long
const int N=1e6+5;
int a[N],dep[N],ch[N][2],mod,n,m;
void ins(int s,int x){
	if(a[x]<a[s]) if(ch[s][0]) ins(ch[s][0],x);
	else ch[s][0]=x,dep[x]=dep[s]+1;
	else if(ch[s][1]) ins(ch[s][1],x);
	else ch[s][1]=x,dep[x]=dep[s]+1;
}
int main(){
	int T,x;
	freopen("fuwafuwa.in","r",stdin),freopen("fuwafuwa.out","w",stdout),scanf("%d",&T),dep[0]=-1;
	while(T--){
		scanf("%d%d%d%d",&n,&m,&mod,&x),memset(a,-1,sizeof a),memset(ch,0,sizeof ch);
		for(int i=1;i<=x;i++) a[i]=n=(n+m)%mod,ins(0,i);
		printf("%d\n",dep[x]);
	}
	return 0;
}
