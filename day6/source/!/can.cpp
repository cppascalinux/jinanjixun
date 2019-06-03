#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define ll long long
using namespace std;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
int n,m,k,ans;
char a[15][15];
bool flag[15][15];
queue<int>qx,qy;
bool vis[15][15];
void dfs(int x,int y)
{
	if(x==n+1)
	{
		bool flag1=0,flag2=0;
		for(int i=1;i<=n;i++)
		  for(int j=1;j<=m;j++)
		    vis[i][j]=0;
		int s1=0,s2=0;
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(flag[i][j]==0)s1++;
			else s2++;
			if(vis[i][j])continue;
			if(flag[i][j]==0&&flag1)return;
			if(flag[i][j]==1&&flag2)return;
			vis[i][j]=1;
			qx.push(i);
			qy.push(j);
			while(!qx.empty())
			{
				int x=qx.front();
				int y=qy.front();
				qx.pop();
				qy.pop();
				for(int k=0;k<4;k++)
				{
					int xx=x+dx[k];
					int yy=y+dy[k];
					if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&flag[xx][yy]==flag[x][y]&&!vis[xx][yy])
					{
						vis[xx][yy]=1;
						qx.push(xx);
						qy.push(yy);
					}
				}
			}
			if(flag[i][j]==0)flag1=1;
			if(flag[i][j]==1)flag2=1;
		}
		if(abs(s1-s2)<=k)ans++;
		return;
	}
	if(a[x][y]=='A')
	{
		if(x!=1&&y!=1&&flag[x-1][y-1]==0&&flag[x-1][y]==0&&flag[x][y-1]==0)return;
		if(x!=1&&y!=1&&flag[x-1][y-1]==0&&flag[x-1][y]==1&&flag[x][y-1]==1)return;
		flag[x][y]=0;
		if(y==m)dfs(x+1,1);
		else dfs(x,y+1);
	}
	else if(a[x][y]=='B')
	{
		if(x!=1&&y!=1&&flag[x-1][y-1]==1&&flag[x-1][y]==1&&flag[x][y-1]==1)return;
		if(x!=1&&y!=1&&flag[x-1][y-1]==1&&flag[x-1][y]==0&&flag[x][y-1]==0)return;
		flag[x][y]=1;
		if(y==m)dfs(x+1,1);
		else dfs(x,y+1);
	}
	else
	{
		if(x!=1&&y!=1&&flag[x-1][y-1]==0&&flag[x-1][y]==0&&flag[x][y-1]==0);
		else if(x!=1&&y!=1&&flag[x-1][y-1]==0&&flag[x-1][y]==1&&flag[x][y-1]==1);
		else
		{
			flag[x][y]=0;
			if(y==m)dfs(x+1,1);
			else dfs(x,y+1);
		}
		if(x!=1&&y!=1&&flag[x-1][y-1]==1&&flag[x-1][y]==1&&flag[x][y-1]==1);
		else if(x!=1&&y!=1&&flag[x-1][y-1]==1&&flag[x-1][y]==0&&flag[x][y-1]==0);
		else
		{
			flag[x][y]=1;
			if(y==m)dfs(x+1,1);
			else dfs(x,y+1);
		}
	}
}
int main()
{
	freopen("can.in","r",stdin);
	freopen("can.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	dfs(1,1);
	printf("%d\n",ans);
	return 0;
}
