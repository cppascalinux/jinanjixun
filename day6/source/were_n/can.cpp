#include<bits/stdc++.h>
#define CL(a) memset(a,0,sizeof(a))
#define Rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;
int ans,A[20][20],n,m,K,dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};
bool vis[11][11];
char M[20][20];
void Dfs1(int x,int y,int c){
	vis[x][y]=1;
	for (int i=0;i<4;i++){
		int x1=x+dx[i],y1=y+dy[i];
		if (x1>=1&&x1<=n&&y1>=1&&y1<=m){
			if (vis[x1][y1]||A[x1][y1]!=c) continue;
			Dfs1(x1,y1,c);
		}
	}
}
bool Check(){ 
	int x1=0,x2=0;
	Rep(i,1,n) Rep(j,1,m) 
		if (A[i][j]) x1++;
		else x2++;
	if (abs(x1-x2)>K) return 0;
	int aaa;
	aaa=0;
	Rep(i,1,n-1) Rep(j,1,m-1)
		if (A[i][j]==A[i+1][j]&&A[i][j]==A[i][j+1]&&A[i][j]==A[i+1][j+1])
			return 0;
	CL(vis);
	Rep(i,1,n){
		bool f1=0;
		Rep(j,1,m) if (!A[i][j]){
			Dfs1(i,j,0); f1=1;
			Rep(i,1,n) Rep(j,1,m) if (!A[i][j]&&!vis[i][j]) 
				return 0;
		}
		if (f1) break;
	}
	CL(vis);
	Rep(i,1,n){
		bool f1=0;
		Rep(j,1,m) if (A[i][j]){
			Dfs1(i,j,1); f1=1;
			Rep(i,1,n) Rep(j,1,m) if (A[i][j]&&!vis[i][j]) 
				return 0;
		}
		if (f1) break;
	}	
	return 1;
}
void Dfs(int x,int y){
	if (x==n+1){
		if (Check()) ans++;
		return;
	}
	if (y==m+1){
		Dfs(x+1,1); return;
	}
	if (M[x][y]!='B') A[x][y]=0; Dfs(x,y+1);
	if (M[x][y]!='A') A[x][y]=1; Dfs(x,y+1);
}
int main(){
	freopen("can.in","r",stdin);
	freopen("can.out","w",stdout);
	scanf("%d %d %d",&n,&m,&K);
	Rep(i,1,n) scanf("%s",M[i]+1);
	Dfs(1,1);
	cout<<ans;
}
