#include<bits/stdc++.h>
#define CL(a) memset(a,0,sizeof(a))
#define Rep(i,a,b) for (int i=a;i<=b;i++)
#define Mod (1000000007)
#define LL long long
using namespace std;
int n,m,K,siz[1<<10];
char S1[1001010],S[1001010];
int Get(int x,int i){
	if (x&(1<<(i-1))) return 1;
	else return 0;
}
void Upd(LL &x,LL a){ x=(x+a)%Mod; }
void InIt(){
	scanf("%d %d %s",&n,&K,S1+1);
	int len=strlen(S1+1);
	Rep(i,1,K) Rep(j,1,len) S[++m]=S1[j];
}
LL dp[2][(1<<7)+5][(1<<6)+5][8][2][2];
int main(){
	freopen("end.in","r",stdin);
	freopen("end.out","w",stdout);
	InIt();
	int Cur=0;
	dp[Cur][(1<<n)-1][(1<<(n-1))-1][n][0][0]=1;
	Rep(i,0,m-1){
		CL(dp[Cur^1]);
		Rep(x1,0,(1<<n)-1) Rep(x2,0,(1<<(n-1))-1) Rep(num,0,1) if (dp[Cur][x1][x2][n][0][num])
			Upd(dp[Cur^1][x1][x2][0][0][0],dp[Cur][x1][x2][n][0][num]);
		Rep(k,0,n-1) Rep(x1,0,(1<<n)-1) Rep(x2,0,(1<<(n-1))-1)
			Rep(n1,0,1) Rep(n2,0,1) if (dp[Cur^1][x1][x2][k][n1][n2]) Rep(num,0,1) {
				if (S[i+1]=='0'&&Get(x1,k+1)&&num) continue;
				if (k&&n2&&Get(x2,k)&&!num) continue;
				int X1=x1,X2=x2;
				if (Get(x1,k+1)&&num<S[i+1]-'0') X1^=1<<k;
				if (k&&Get(x2,k)&&n2<num) X2^=1<<(k-1);
				
				Upd(dp[Cur^1][X1][X2][k+1][(n1+num)%2][num],dp[Cur^1][x1][x2][k][n1][n2]);
			}
		Cur^=1; 
	}
	LL ans=0; 
	Rep(i,0,1) Upd(ans,dp[Cur][0][0][n][0][i]);
	cout<<ans;
}
