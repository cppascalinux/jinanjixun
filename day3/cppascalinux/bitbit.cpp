#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int n,m;
int mat[509][509];
namespace p1
{
	int cl[509];
	void solve()
	{
		int sm=0;
		for(int i=1;i<=m;i++)
		{
			if(mat[1][i]==1&&mat[1][i-1]==0)
				sm++;
			if(mat[1][i]==1)
				cl[i]=sm;
		}
		printf("%d\n",sm);
		for(int i=1;i<=sm;i++)
		{
			printf("+\n");
			for(int j=1;j<=m;j++)
				if(cl[j]==i)
					printf("1 ");
				else
					printf("0 ");
			printf("\n");
		}
	}
}
namespace p2
{
	struct node
	{
		int v[4][4];
		node(){memset(v,0,sizeof(v));}
	};
	int f[10],tp;
	node st[1009];
	node nw[1009];
	int fnd(int x)
	{
		return x==f[x]?x:f[x]=fnd(f[x]);
	}
	int dfs(int d,int mxd,node now)
	{
		if(d>mxd)
		{
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					if(now.v[i][j]!=mat[i][j])
						return 0;
			printf("%d\n",mxd);
			for(int i=1;i<=mxd;i++)
			{
				node t=nw[i];
				int inv=1;
				for(int j=1;j<=n;j++)
					for(int k=1;k<=n;k++)
						if(t.v[j][k]<0)
							inv=-1;
				if(inv==1)
					printf("+\n");
				else
					printf("-\n");
				for(int j=1;j<=n;j++)
				{
					for(int k=1;k<=n;k++)
						printf("%d ",abs(t.v[j][k]));
					printf("\n");
				}
			}
			return 1;
		}
		for(int i=1;i<=tp;i++)
		{
			node nxt=now;
			for(int j=1;j<=n;j++)
				for(int k=1;k<=n;k++)
					nxt.v[j][k]+=st[i].v[j][k];
			nw[d]=st[i];
			if(dfs(d+1,mxd,nxt))
				return 1;
		}
		return 0;
	}
	void solve()
	{
		for(int s=0;s<1<<n*n;s++)
		{
			node t;
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
				{
					int p=(i-1)*n+j;
					if((s>>(p-1))&1)
						t.v[i][j]=1,f[p]=p;
					else
						f[p]=0;
				}
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					if(t.v[i][j])
					{
						if(i+1<=n&&t.v[i+1][j])
							f[fnd((i-1)*n+j)]=fnd(f[i*n+j]);
						if(j+1<=n&&t.v[i][j+1])
							f[fnd((i-1)*n+j)]=fnd(f[(i-1)*n+j+1]);
					}
			int sk=0;
			for(int i=1;i<=n*n;i++)
				if(fnd(i)!=0)
					sk=f[i];
			int fg=0;
			for(int i=1;i<=n*n;i++)
				if(fnd(i)!=0&&fnd(i)!=sk)
					fg=1;
			if(fg)
				continue;
			st[++tp]=t;
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					t.v[i][j]*=-1;
			st[++tp]=t;
		}
		// printf("tp:%d\n",tp);
		// for(int i=1;i<=tp;i++)
		// {
		// 	for(int j=1;j<=n;j++)
		// 	{
		// 		for(int k=1;k<=n;k++)
		// 			printf("%d ",st[i].v[j][k]);
		// 		printf("\n");
		// 	}
		// 	printf("\n");
		// }
		for(int i=0;1;i++)
			if(dfs(1,i,node()))
				break;
	}
}
int main()
{
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",mat[i]+j);
	if(n==1)
		p1::solve();
	else
		p2::solve();
	return 0;
}