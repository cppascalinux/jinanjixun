#include<cstdio>
#include<cstdlib>
#define N 510
char s[N][N],ans[N][N];int que[N*N][3],n,m,vis[N][N],C,stk[N*N],top;bool cet[N*N];
int dx[]={0,1,0,-1,0};
int dy[]={0,0,1,0,-1};
inline bool in(int x,int y) {return x>=1&&x<=n&&y>=1&&y<=m;}
void bfs(int x,int y,int c,char nm)
{
	int f,e,cnt=0;
	que[e=f=1][1]=x;que[1][0]=y;vis[x][y]=c;
	while(f<=e)
	{
		x=que[f][1];y=que[f][0];++f;
		for (int l=1;l<=4;++l)
		{
			int tx=x+dx[l],ty=y+dy[l];
			if (in(tx,ty)&&s[tx][ty]==nm&&!vis[tx][ty])
			{
				vis[tx][ty]=c;
				que[++e][1]=tx;que[e][0]=ty;
			}
			if (in(tx,ty)&&s[tx][ty]=='1'&&nm=='0'&&!cet[vis[tx][ty]])
			{
				cet[vis[tx][ty]]=true;++cnt;
				stk[++top]=vis[tx][ty];
			}
		}
	}
	if (cnt==C)
	{
		printf("2\n+\n");
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j) ans[i][j]=vis[i][j]==c||s[i][j]=='1'?'1':'0';
		for (int i=1;i<=n;++i) printf("%s\n",ans[i]+1);
		printf("-\n");
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j) ans[i][j]=vis[i][j]==c?'1':'0';
		for (int i=1;i<=n;++i) printf("%s\n",ans[i]+1);
		exit(0);
	}else while(top) cet[stk[top--]]=false;
}
int main()
{
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	int x,y,K;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%s",s[i]+1);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j) 
			if (s[i][j]=='1'&&!vis[i][j])
				bfs(i,j,++C,'1');
	if (!C) return !printf("0");
	if (C<=1)
	{
		printf("1\n+\n");
		for (int i=1;i<=n;++i) printf("%s\n",s[i]+1);
		return 0;
	}
	K=C;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			if (s[i][j]=='0'&&!vis[i][j])
				bfs(i,j,++K,'0');

	if (n==1)
	{
		printf("%d\n",C);
		for (int c=1;c<=C;++c)
		{
			printf("+\n");
			for (int j=1;j<=m;++j) printf("%d",vis[1][j]==c);
			putchar('\n');
		}
		return 0;
	}
	if (m==1)
	{
		printf("%d\n",C);
		for (int c=1;c<=C;++c)
		{
			printf("+\n");
			for (int i=1;i<=n;++i) printf("%d\n",vis[i][1]==c);
		}
		return 0;
	}
	if (m==2)
	{
		printf("3\n+\n");
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j) ans[i][j]=i!=n&&(i==1||j==1||s[i][j]=='1')?'1':'0';
		for (int i=1;i<=n;++i) printf("%s\n",ans[i]+1);
		printf("+\n");
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j) ans[i][j]=i!=1&&(i==n||j==2||s[i][j]=='1')?'1':'0';
		for (int i=1;i<=n;++i) printf("%s\n",ans[i]+1);
		printf("-\n");
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j) ans[i][j]=i!=1&&i!=n||s[i][j]=='0'?'1':'0';
		for (int i=1;i<=n;++i) printf("%s\n",ans[i]+1);
		return 0;
	}
	if (n>=2&&m>=3)
	{
		printf("3\n+\n");
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j) ans[i][j]=j!=m&&(j==1||i&1||s[i][j]=='1')?'1':'0';
		for (int i=1;i<=n;++i) printf("%s\n",ans[i]+1);
		printf("+\n");
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j) ans[i][j]=j!=1&&(j==m||!(i&1)||s[i][j]=='1')?'1':'0';
		for (int i=1;i<=n;++i) printf("%s\n",ans[i]+1);
		printf("-\n");
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j) ans[i][j]=j!=1&&j!=m||s[i][j]=='0'?'1':'0';
		for (int i=1;i<=n;++i) printf("%s\n",ans[i]+1);
		return 0;
	}
	return 0;
}
