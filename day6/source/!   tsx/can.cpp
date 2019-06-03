#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
namespace abc
{
	int n,m,k,c[105][105],vis[105][105],ans=0,q[1000005][2],head,tail,dx[4]={0,-1,0,1},dy[4]={1,0,-1,0};
	char a[105][105];
	int bfs(int fl,int tx,int ty)
	{
		head=0,tail=1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				vis[i][j]=0;
		q[1][0]=-1;
		int ffl=1;
		for(int i=1;i<=tx&&ffl;i++)
			for(int j=1;j<=(i==tx?ty:m);j++)
				if(c[i][j]==fl)
				{
					q[1][0]=i;
					q[1][1]=j;
					ffl=0;
					break;
				}
		if(q[1][0]==-1) return 0;
		vis[q[1][0]][q[1][1]]=1;
		int maxx=q[1][0];
		while(head<tail)
		{
			head++;
			int x=q[head][0],y=q[head][1];
			maxx=max(maxx,x);
			for(int i=0;i<4;i++)
			{
				int xx=x+dx[i],yy=y+dy[i];
				if(xx<=0||yy<=0||xx>tx||yy>m||vis[xx][yy]||c[xx][yy]!=fl) continue;
				if(xx==tx&&yy>ty) continue;
				vis[xx][yy]=1;
				q[++tail][0]=xx;
				q[tail][1]=yy;
			}
		}
		if(tx!=n||ty!=m)
		{
			if(maxx>=tx-1) return 0;
		}
		for(int i=1;i<=tx;i++)
			for(int j=1;j<=(i==tx?ty:m);j++)
			{
				//printf("vis[i][j]=%d,c[i][j]=%d,i=%d,j=%d,fl=%d\n",vis[i][j],c[i][j],i,j,fl);
				if(c[i][j]==fl&&!vis[i][j])
				{
					return -1;
				}
			}
		return tail;
	}
	void check()
	{
		int nw=bfs(0,n,m),nw2=bfs(1,n,m);
		if(nw==-1||nw2==-1) return;
		if(abs(nw-nw2)>k) return;
		ans++;
		/*printf("nw=%d,nw2=%d\n",nw,nw2);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
				printf("%d",c[i][j]);
			printf("\n");
		}
		printf("\n");*/
	}
	bool check2(int x,int y)
	{
		if(x==1||y==1) return 1;
		int nw=c[x][y];
		if(nw==c[x][y-1]&&nw==c[x-1][y]&&nw==c[x-1][y-1]) return 0;
		if(bfs(0,x,y)==-1||bfs(1,x,y)==-1) return 0;
		return 1;
	}
	void dfs(int x,int y)
	{
		if(x==n+1)
		{
			check();
			return;
		}
		int xx=x,yy=y+1;
		if(yy>m)
		{
			yy=1,xx++;
		}
		if(a[x][y]=='A')
		{
			c[x][y]=0;
			if(check2(x,y)) dfs(xx,yy);
			return;
		}
		if(a[x][y]=='B')
		{
			c[x][y]=1;
			if(check2(x,y)) dfs(xx,yy);
			return;
		}
		c[x][y]=0;
		if(check2(x,y)) dfs(xx,yy);
		c[x][y]=1;
		if(check2(x,y)) dfs(xx,yy);
	}
	void soe()
	{
		freopen("can.in","r",stdin);
		freopen("can.out","w",stdout);
		scanf("%d%d%d",&n,&m,&k);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf(" %c",&a[i][j]);
		dfs(1,1);
		printf("%d",ans);
	}
}
int main()
{
	abc::soe();
	return 0;
}
