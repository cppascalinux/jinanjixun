#include<bits/stdc++.h>
#define LL long long
#define CL(a) memset(a,0,sizeof(a))
#define Mod (100000007)
#define Rep(i,a,b) for (int i=a;i<=b;i++)
LL dp[2][(1<<20)+5];
using namespace std;
int n,m,R[200][200],D[200][200];
int Get(int x,int i){
	if (x&(1<<(i-1))) return 1;
	else return 0;
}
int Num(int i){
	return 1<<(i-1);
}
void Upd(LL &x,LL a){
	x=(x+a)%Mod;
}
int main(){
	freopen("scumwish.in","r",stdin);
	freopen("scumwish.out","w",stdout);
	scanf("%d %d",&n,&m);
	Rep(i,1,n) Rep(j,1,m-1) scanf("%d",&R[i][j]),R[i][j]^=1;
	Rep(i,1,n-1) Rep(j,1,m) scanf("%d",&D[i][j]),D[i][j]^=1;
	int Cur=0;
	dp[Cur][(1<<m)-1]=1;
	Rep(i,1,n) Rep(j,1,m){
		Cur^=1; CL(dp[Cur]);
		Rep(x,0,(1<<m)-1) if (dp[Cur^1][x]){
			if (x&1)  //1
				Upd(dp[Cur][(x>>1)+Num(m)],dp[Cur^1][x]);
			else{
				if (i>1&&!D[i-1][j]) //2
					Upd(dp[Cur][(x>>1)+Num(m)],dp[Cur^1][x]);
			}
			if (j>1&&!Get(x,m)&&!R[i][j-1]){ //3 5
				if (x&1)
					Upd(dp[Cur][(x>>1)+Num(m)+Num(m-1)],dp[Cur^1][x]);
				else{
					if (i>1&&!D[i-1][j])
						Upd(dp[Cur][(x>>1)+Num(m)+Num(m-1)],dp[Cur^1][x]);
				}
			}
			if (i>1&&j<m&&!Get(x,1)&&!Get(x,2)&&!D[i-1][j]&&!R[i-1][j]) //4
				Upd(dp[Cur][(x>>1)+Num(m)+1],dp[Cur^1][x]);
			if (x&1) 
				Upd(dp[Cur][x>>1],dp[Cur^1][x]);//²»·Å 
		}
	}
	cout<<dp[Cur][(1<<m)-1];
}
