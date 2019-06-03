#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
#define ll long long
char s[10][10];int bel[10][10],n,m,k,ans=0,que[100][2],f,e,ltk[10][10];
int dx[]={0,1,0,-1,0};
int dy[]={0,0,1,0,-1};
inline bool in(int x,int y) {return x>=1&&x<=n&&y>=1&&y<=m;}
inline bool check()
{
	que[f=e=1][1]=1;que[1][0]=1;
	while(f<=e)
	{
		int x=que[f][1],y=que[f][0];++f;
		ltk[x][y]=1;
		for (int l=1;l<=4;++l)
		{
			int tx=x+dx[l],ty=y+dy[l];
			if (!in(tx,ty)||ltk[tx][ty]||bel[tx][ty]!=bel[x][y]) continue;
			que[++e][1]=tx;que[e][0]=ty;
		}
	}
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			if (!ltk[i][j]) {que[f=e=1][1]=i,que[1][0]=j;break;}
	while(f<=e)
	{
		int x=que[f][1],y=que[f][0];++f;
		ltk[x][y]=2;
		for (int l=1;l<=4;++l)
		{
			int tx=x+dx[l],ty=y+dy[l];
			if (!in(tx,ty)||ltk[tx][ty]||bel[tx][ty]!=bel[x][y]) continue;
			que[++e][1]=tx;que[e][0]=ty;
		}
	}
	bool Z=true;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			if (!ltk[i][j]) Z=false;
			else ltk[i][j]=0;
	return Z;
}
void dfs(int i,int j,int kk)//A-B
{
	if (i==n+1) {if (abs(kk)<=k) ans+=check();return;}
	if (s[i][j]=='C')
	{
		bel[i][j]=1;
		if ((i!=1&&bel[i-1][j]==bel[i][j])&&(j!=1&&bel[i][j-1]==bel[i][j])&&bel[i-1][j-1]==bel[i][j]);
		else dfs(i+(j==m),j==m?1:j+1,kk+(bel[i][j]==1?1:-1));
		bel[i][j]=2;
		if ((i!=1&&bel[i-1][j]==bel[i][j])&&(j!=1&&bel[i][j-1]==bel[i][j])&&(bel[i-1][j-1]==bel[i][j]));
		else dfs(i+(j==m),j==m?1:j+1,kk+(bel[i][j]==1?1:-1));
	}else
	{
		if ((i!=1&&bel[i-1][j]==bel[i][j])&&(j!=1&&bel[i][j-1]==bel[i][j])&&(bel[i-1][j-1]==bel[i][j])) return;
		dfs(i+(j==m),j==m?1:j+1,kk+(bel[i][j]==1?1:-1));
	}
}
int main()
{
	freopen("can.in","r",stdin);
	freopen("can.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;++i) scanf("%s",s[i]+1);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j) 
			if (s[i][j]=='A') bel[i][j]=1;
			else if (s[i][j]=='B') bel[i][j]=2;
	dfs(1,1,0);
	printf("%d",ans);
	return 0;
}

//by qlwpc
