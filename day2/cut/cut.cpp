#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
#include<queue>
#define li long long
#define db double
#define eps 1e-10
#define pii pair<int,int>
#define pip pair<int,pii>
#define pli pair<li,int>
#define fi first
#define se second
#define inf 0x7F7F7F7F7F7F7F7FLL
using namespace std;
int n,m,k,w;
int mat[1009][1009];
pii st[1009];
int vis[1009][1009],ans[1009][1009];
li sm[1009];
int dp[5][2]={{},{1,0},{-1,0},{0,1},{0,-1}};
mt19937 rnd(time(0));
li judge()
{
	priority_queue<pli,vector<pli>,greater<pli> > pq;
	priority_queue<pip,vector<pip>,less<pip> > nxt[1009];
	for(int i=1;i<=k;i++)
	{
		int px=st[i].fi,py=st[i].se;
		pq.push(pli(mat[px][py],i));
		sm[i]=mat[px][py];
		for(int j=1;j<=4;j++)
		{
			int nx=px+dp[j][0],ny=py+dp[j][1];
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&!vis[nx][ny])
				nxt[i].push(pip(mat[nx][ny],pii(nx,ny)));
		}
	}
	while(!pq.empty())
	{
		int x=pq.top().se;
		pq.pop();
		while(!nxt[x].empty())
		{
			int v=nxt[x].top().fi;
			pii t=nxt[x].top().se;
			nxt[x].pop();
			if(!vis[t.fi][t.se])
			{
				vis[t.fi][t.se]=x;
				sm[x]+=v;
				for(int i=1;i<=4;i++)
				{
					int nx=t.fi+dp[i][0],ny=t.se+dp[i][1];
					if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&!vis[nx][ny])
						nxt[x].push(pip(mat[nx][ny],pii(nx,ny)));
				}
				break;
			}
		}
		if(!nxt[x].empty())
			pq.push(pli(sm[x]+rnd()%w,x));
		// for(int i=1;i<=n;i++)
		// {
		// 	for(int j=1;j<=m;j++)
		// 		printf("%2d ",vis[i][j]);
		// 	printf("\n");
		// }
		// printf("\n\n");
	}
	li mn=inf,mx=0;
	for(int i=1;i<=k;i++)
		mn=min(mn,sm[i]),mx=max(mx,sm[i]);
	return mx-mn;
}
void sa()
{
	li out=inf;
	while(out>100)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				vis[i][j]=0;
		for(int i=1;i<=k;i++)
		{
			while(1)
			{
				st[i].fi=rnd()%n+1,st[i].se=rnd()%m+1;
				if(!vis[st[i].fi][st[i].se])
				{
					vis[st[i].fi][st[i].se]=i;
					break;
				}
			}
		}
		li tmp=judge();
		if(tmp<out)
		{
			out=tmp;
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++)
					ans[i][j]=vis[i][j];
			cerr<<out<<endl;
		}
	}
	// for(int i=1;i<=k;i++)
	// 	printf("i:%d sm:%lld\n",i,sm[i]);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			printf("%d ",ans[i][j]);
		printf("\n");
	}		
}
void solve2()
{
	li sm=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			sm+=mat[i][j];
	li goal=sm/k,res=sm%k,tmp=0,cur=1;
	for(int i=1;i<=n;i++)
	{
		if(i&1)
		{
			for(int j=1;j<=m;j++)
			{
				tmp+=mat[i][j];
				ans[i][j]=cur;
				if(tmp>=goal-300000000)
				{
					tmp=0;
					cur++;
				}
			}
		}
		else
		{
			for(int j=m;j>=1;j--)
			{
				tmp+=mat[i][j];
				ans[i][j]=cur;
				if(tmp>=goal-300000000)
				{
					tmp=0;
					cur++;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			printf("%d ",ans[i][j]);
		printf("\n");
	}
}
int main()
{
	freopen("cut.in","r",stdin);
	freopen("cut9.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&k,&w);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&mat[i][j]);
	// sa();
	solve2();
	return 0;
}