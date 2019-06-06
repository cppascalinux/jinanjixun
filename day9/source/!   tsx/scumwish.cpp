#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,vis1[105][105],vis2[105][105],f[15][15][2505];
const int mod=1e8+7;
int dfs(int x,int y,int nw)
{
	//printf("x=%d,y=%d,nw=%d\n",x,y,nw);
	if(x==n+1&&nw==0) return 1;
	if(x==n+1) return 0;
	int xx=x,yy=y+1;
	if(yy>m) xx++,yy=1;
	if(nw&(1<<(y-1))) return dfs(xx,yy,nw-(1<<(y-1)));
	if(f[x][y][nw]!=-1) return f[x][y][nw];
	int ans=0;
	ans=dfs(xx,yy,nw);
	if(vis2[x][y]) ans=(ans+dfs(xx,yy,nw+(1<<(y-1))))%mod;
	if(vis1[x][y]&&!(nw&(1<<y))) ans=(ans+dfs(xx,yy,nw+(1<<y)))%mod;
	if(vis2[x][y]&&vis1[x][y]&&!(nw&(1<<y))) ans=(ans+dfs(xx,yy,nw+(1<<y)+(1<<(y-1))))%mod;
	if(vis2[x][y]&&x<n&&y>1&&vis1[x+1][y-1]&&!(nw&(1<<y-2))) ans=(ans+dfs(xx,yy,nw+(1<<(y-1))+(1<<(y-2))))%mod;
	f[x][y][nw]=ans;
	return ans;
}
int main()
{
	freopen("scumwish.in","r",stdin);
	freopen("scumwish.out","w",stdout);
	memset(f,-1,sizeof(f));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
			scanf("%d",&vis1[i][j]);
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&vis2[i][j]);
	printf("%d",dfs(1,1,0));
	return 0;
}
