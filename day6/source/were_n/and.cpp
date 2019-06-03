#include<bits/stdc++.h>
#define Rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
#define Mod (1000000007)
using namespace std;
int n,m,b[200],Cur,x1,x2,a[200],B[200];
LL dp[32][(1<<9)+5][(1<<9)+5];
int Get(int x,int num){
	num--;
	if (x&(1<<num)) return 1;
	else return 0;
}
void Upd(LL &x,LL a){
	x=(x+a)%Mod;
}
void Dfs(int x,int X1,int X2){
	if (x==n+1){
		Upd(dp[Cur-1][X1][X2],dp[Cur][x1][x2]); 
		return;
	}
	for (a[x]=0;a[x]<=1;a[x]++){
		int base1=X1,base2=X2;
		bool f1=Get(x1,x-1),f2=Get(x2,x-1);
		if (x>1&&f1&&(a[x-1]&B[x-1])>(a[x]&B[x])) continue;
		if (x>1&&f2&&(a[x-1]|B[x-1])<(a[x]|B[x])) continue;
		
		if (x>1&&f1&&(a[x-1]&B[x-1])==(a[x]&B[x])) base1|=(1<<(x-2));
		if (x>1&&f2&&(a[x-1]|B[x-1])==(a[x]|B[x])) base2|=(1<<(x-2));
		Dfs(x+1,base1,base2);
	}
}
int main(){
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	scanf("%d %d",&n,&m);
	Rep(i,1,n) scanf("%d",&b[i]);
	dp[m+1][(1<<(n-1))-1][(1<<(n-1))-1]=1;
	for (Cur=m+1;Cur>1;Cur--){
		Rep(i,1,n) B[i]=Get(b[i],Cur-1);
		for (x1=0;x1<(1<<(n-1));x1++) for (x2=0;x2<(1<<(n-1));x2++) 
			if (dp[Cur][x1][x2])
				Dfs(1,0,0);
	}
	LL ans=0;
	Rep(i,0,(1<<(n-1))-1) Rep(j,0,(1<<(n-1))-1) 
		Upd(ans,dp[1][i][j]);
	ans=(ans+Mod)%Mod;
	cout<<ans;	
}
