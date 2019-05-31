#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
namespace yjh
{
	int n,m,dx[4]={0,1,0,-1},dy[4]={-1,0,1,0},q[1000005][2],head,tail,f[1000005],t;
	int mp[15][15],mp1[15][15],tfl=0,g[15],gfl[15],c[1000005];
	int getval(int x,int xx,int yy)
	{
		return !!(x&(1<<((xx-1)*m+yy-1)));
	}
	bool check(int x)
	{
		if(x==0) return 1;
		int cnt=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				mp[i][j]=getval(x,i,j);
				cnt+=mp[i][j];
				if(mp[i][j]) q[1][0]=i,q[1][1]=j;
			}
		//printf("x=%d\n",x);
		/*for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
				printf("%d ",mp[i][j]);
			printf("\n");
		}*/
		head=0,tail=1;
		mp[q[1][0]][q[1][1]]=0;
		while(head<tail)
		{
			head++;
			int x=q[head][0],y=q[head][1];
			for(int i=0;i<4;i++)
			{
				int xx=x+dx[i],yy=y+dy[i];
				if(xx<=0||xx>n||yy<=0||yy>m||!mp[xx][yy]) continue;
				mp[xx][yy]=0;
				q[++tail][0]=xx;
				q[tail][1]=yy;
			}
		}
		if(tail==cnt) return 1;
		return 0;
	}
	int checkans()
	{
		int fl=1;
		for(int i=1;i<=n&&fl;i++)
			for(int j=1;j<=m;j++)
				if(mp[i][j]!=mp1[i][j])
				{
					fl=0;
					break;
				}
		return fl;
	}
	void dfs(int dep,int maxn)
	{
		if(checkans())
		{
			printf("%d\n",dep-1);
			for(int i=1;i<dep;i++)
			{
				printf("%c\n",gfl[i]?'-':'+');
				for(int j=1;j<=n;j++)
				{
					for(int k=1;k<=m;k++)
						printf("%d",getval(g[i],j,k));
					printf("\n");
				}
			}
			tfl=1;
			return;
		}
		if(dep>maxn) return;
		for(int i=1;i<=t;i++)
		{
			int nw=f[i];
			for(int j=1;j<=n;j++)
				for(int k=1;k<=m;k++)
					mp[j][k]+=getval(nw,j,k);
			g[dep]=nw;
			gfl[dep]=0;
			dfs(dep+1,maxn);
			if(tfl) return;
			for(int j=1;j<=n;j++)
				for(int k=1;k<=m;k++)
					mp[j][k]=mp[j][k]-2*getval(nw,j,k);
			g[dep]=nw;
			gfl[dep]=1;
			dfs(dep+1,maxn);
			if(tfl) return;
			for(int j=1;j<=n;j++)
				for(int k=1;k<=m;k++)
					mp[j][k]+=getval(nw,j,k);
		}
	}
	void soe()
	{
		freopen("bitbit.in","r",stdin);
		freopen("bitbit.out","w",stdout);
		scanf("%d%d",&n,&m);
		if(n==1)
		{
			int cnt=0;
			c[0]=c[m+1]=0;
			for(int i=1;i<=m;i++)
			{
				char ch;
				scanf(" %c",&ch);
				c[i]=ch-'0';
			}
			for(int i=1;i<=m;i++)
				if(c[i]==1&&c[i-1]==0)
					cnt++;
			printf("%d\n",cnt);
			if(cnt==0) return;
			int nw=1;
			for(int i=1;i<=cnt;i++)
			{
				printf("+\n");
				while(nw<=m&&(c[nw]!=1||c[nw-1]!=0)) nw++;
				int d=nw;
				while(d<=m&&(c[d]!=1||c[d+1]!=0)) d++;
				for(int j=1;j<=m;j++)
				{
					if(j<nw||j>d) printf("0");
					else printf("1");
				}
				nw=d+1;
				printf("\n");
			}
			return;
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				char ch;
				scanf(" %c",&ch);
				mp1[i][j]=ch-'0';
			}
		for(int i=0;i<(1<<(n*m));i++)
			if(check(i))
				f[++t]=i;
		memset(mp,0,sizeof(mp));
		for(int i=1;i<=4;i++)
		{
			dfs(1,i);
			if(tfl) return;
		}
		//printf("t=%d\n",t);
		//for(int i=1;i<=t;i++)
		//	printf("%d ",f[i]);
	}
}
int main()
{
	yjh::soe();
	return 0;
}
