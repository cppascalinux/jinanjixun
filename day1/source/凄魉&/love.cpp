#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
#define M 401200
#define N 201300
#define INF 0x3f3f3f3f3f3f3f3f
#define ll long long
priority_queue<int> Q;
struct node{
	int to,next,v;
}q[M];
int head[N],ss,a[N],X,Y,fa[N],p[N][2];ll S[N],mx,f[N][2],aa[N],b[2][N];
void addedge(int x,int y,int v)
{
	q[++ss]=(node){y,head[x],v};head[x]=ss;
	q[++ss]=(node){x,head[y],v};head[y]=ss;
}
void dfs(int i)
{
	f[i][0]=f[i][1]=0;p[i][0]=p[i][1]=i;
	for (int j=head[i];j;j=q[j].next)
		if (q[j].to^fa[i])
		{
			int t=q[j].to;
			fa[t]=i;
			dfs(t);
			if (f[t][1]+q[j].v>f[i][1])
			{
				f[i][0]=f[i][1];p[i][0]=p[i][1];
				f[i][1]=f[t][1]+q[j].v;p[i][1]=p[t][1];
			}else if (f[t][1]+q[j].v>f[i][0])
			{
				f[i][0]=f[t][1]+q[j].v;p[i][0]=p[t][1];
			}
		}
	if (f[i][1]+f[i][0]>mx) X=p[i][0],Y=p[i][1],mx=f[i][1]+f[i][0];
}
void dd(int i)
{
	for (int j=head[i];j;j=q[j].next)
		if (q[j].to^fa[i])
		{
			int t=q[j].to;
			fa[t]=i;
			dd(t);
		}
}
ll fzj()
{
	int Rt=1;mx=-INF;
	fa[Rt]=0;dfs(Rt);
	return mx;
}
inline int read(){
	int n=0;char a;bool z=false;
	while(a=getchar())
	{
		if (a>'9'||a<'0')
			if (z) break;
			else continue;
		if (!z) z=true;
		n=(n<<1)+(n<<3)+(a^48);
	}
	return n;
}
int main()
{
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
	int n,m,x,y,v;ll ans=0,V2=0;
	n=read();m=read();
	for (int i=1;i<n;++i)
	{
		x=read();y=read();v=read();
		addedge(x,y,v);ans+=v<<1;
	}
	for (int i=1;i<=m;++i) a[i]=read();
	printf("%lld ",ans);
	aa[0]=ans;
	for (int i=1;i<=m;++i)
	{
		fzj();
		x=Y;fa[X]=0;dd(X);
		while(x)
		{
			y=fa[x];if (!y) break;
			for (int j=head[x];j;j=q[j].next) if (q[j].to==y) {q[j].v=-q[j].v;break;}
			for (int j=head[y];j;j=q[j].next) if (q[j].to==x) {q[j].v=-q[j].v;break;}
			x=y;
		}
		aa[i]=aa[i-1]-mx;
	}
	memset(b,0x7f,sizeof(b));
	b[0][0]=b[1][0]=0;
	for (int i=1,z;i<=m;++i)
	{
		z=i&1;
		for (int j=1;j<=i;++j)
			b[z][j]=min(b[z^1][j],b[z^1][j-1]+a[i]);
		for (int j=1;j<=i+1;++j) b[z^1][j]=INF;
		for (int j=1;j<=i;++j) ans=min(ans,aa[j]+b[z][j]);
		printf("%lld ",ans);
	}
	return 0;
}

//by qlwpc
