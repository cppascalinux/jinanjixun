#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int g,tag[10][10],n,m,k,a[10][10],A,vis[10][10],lasx,lasy,res,l,r,lx,ly;
char ch;
void check(int x,int y,int z)
{
	if(vis[x][y]!=z) return;
	if(!x || !y || x>n || y>m) return;
	vis[x][y]=-1;
	check(x+1,y,z); check(x-1,y,z);
	check(x,y+1,z); check(x,y-1,z);
}

bool jdg(int i,int j)
{
	if(i==1 || j==1) return 1;
	if(vis[i][j]==vis[i-1][j] && vis[i][j]==vis[i][j-1] && vis[i][j]==vis[i-1][j-1]) return 0;
	return 1;
}

void dfs(int t,int x,int y,int s)
{
	if(y==m+1) x+=1, y=1;
	if(s>g) return; 
	if(t-1-s>g) return;
	if(t==n*m+1)
	{
		for(int i=2;i<=n;i++)
			for(int j=2;j<=m;j++)
			{
				if(vis[i][j]==vis[i-1][j] && vis[i][j]==vis[i][j-1] && vis[i][j]==vis[i-1][j-1]) return;
				if(!vis[i][j]) lasx=i, lasy=j;
				else lx=i,ly=j;
			}
		check(lasx,lasy,0);
		int B=1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				if(vis[i][j]==0) B=0;
				if(vis[i][j]==-1) vis[i][j]=0;
			}
		check(lx,ly,1);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				if(vis[i][j]==1) B=0;
				if(vis[i][j]==-1) vis[i][j]=1;
			}
		if(B) res++;
		return ;
	}
	
	if(tag[x][y]!=1) if(jdg(x,y))dfs(t+1,x,y+1,s);
	
	if(tag[x][y]!=2)
	{
		vis[x][y]=1;
		if(jdg(x,y))dfs(t+1,x,y+1,s+1);
		vis[x][y]=0;
	}
}

int main()
{
	freopen("can.in","r",stdin);
	freopen("can.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&k);
	g=(n*m+k)/2;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%c",&ch);
			while(ch!='A' && ch!='B' && ch!='C') scanf("%c",&ch);
			if(ch=='A') tag[i][j]=1;
			if(ch=='B') tag[i][j]=2;
		}
	dfs(1,1,1,0);
	printf("%d",res);
}
