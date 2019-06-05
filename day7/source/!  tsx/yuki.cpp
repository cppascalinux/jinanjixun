#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<cctype>
using namespace std;
typedef long long ll;
int p1=2000000,p2=2000000,p3=-1;
char buf[5000005],buf2[5000005];
inline int readc()
{
	if(p1>=p2)
	{
		fread(buf,1,p2,stdin);
		p1=0;
	}
	return buf[p1++];
}
inline int read()
{
	int x=0,ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch))
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x;
}
inline void getwr()
{
	fwrite(buf2,1,p3+1,stdout);
	p3=-1;
}
inline void print(int x)
{
	if(x>=10) print(x/10);
	buf2[++p3]=x%10+'0';
	if(p3>=2000000) getwr();
}
struct edge
{
	int v,nxt;
}e[5000005];
int n,m,h[2000005],t=0,bt,c[100005][20],d[100005],tin[2000005],dfn[2000005],cnt=0;
ll a[2000005],b[2000005],sum[5000005];
void add(int u,int v)
{
	tin[u]++,tin[v]++;
	e[++t].v=v;
	e[t].nxt=h[u];
	h[u]=t;
}
void dfs(int u,int fa,int dep)
{
	c[u][0]=fa;
	d[u]=dep;
	for(int i=1;i<=18;i++)
		c[u][i]=c[c[u][i-1]][i-1];
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,u,dep+1);
	}
}
int lca(int u,int v)
{
	if(d[u]<d[v]) swap(u,v);
	for(int i=18;i>=0;i--)
		if(d[c[u][i]]>=d[v])
			u=c[u][i];
	if(u==v) return u;
	for(int i=18;i>=0;i--)
		if(c[u][i]!=c[v][i])
			u=c[u][i],v=c[v][i];
	return c[u][0];
}
void getadd(int u,int v,int w)
{
	while(u!=v)
	{
		a[u]+=w;
		u=c[u][0];
	}
	a[v]+=w;
}
int lowbit(int x)
{
	return x&(-x);
}
void modify(int x,int v)
{
	//fprintf(stderr,"x=%d\n",x);
	for(int i=x;i<=n;i+=lowbit(i))
		sum[i]+=v;
}
ll query(int x)
{
	ll ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans+=sum[i];
	return ans;
}
void afs(int u,int fa)
{
	dfn[u]=++cnt;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa) continue;
		afs(v,u);
	}
}
int main()
{
	freopen("yuki.in","r",stdin);
	freopen("yuki.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<n;i++)
	{
		int u,v;
		u=read(),v=read();
		add(u,v);
		add(v,u);
	}
	if(n<=1000&&m<=1000)
	{
		dfs(1,1,1);
		for(int i=1;i<=m;i++)
		{
			int op,u,v,w;
			op=read();
			if(op==1)
			{
				u=read(),v=read(),w=read();
				int l=lca(u,v);
				getadd(u,l,w);
				getadd(v,l,w);
				a[l]-=w;
			}
			else
			{
				u=read(),v=read();
				b[1]=a[u];
				bt=1;
				for(int i=h[u];i;i=e[i].nxt)
				{
					int vv=e[i].v;
					b[++bt]=a[vv];
				}
				sort(b+1,b+bt+1);
				print(b[v]);
				buf2[++p3]='\n';
			}
		}
		getwr();
		return 0;
	}
	for(int i=1;i<=n;i++)
		if(tin[i]==2)
		{
			afs(i,0);
			break;
		}
	//fprintf(stderr,"cnt=%d\n",cnt);
	for(int i=1;i<=n;i++)
		modify(dfn[i],a[i]),modify(dfn[i]+1,-a[i]);
	for(int i=1;i<=m;i++)
	{
		int op,x,y,z;
		op=read();
		if(op==1)
		{
			x=read(),y=read(),z=read();
			x=dfn[x],y=dfn[y];
			if(x>y) swap(x,y);
			modify(x,z);
			modify(y+1,-z);
		}
		else
		{
			x=read(),y=read();
			x=dfn[x];
			bt=0;
			b[++bt]=query(x);
			if(x!=1) b[++bt]=query(x-1);
			if(x!=n) b[++bt]=query(x+1);
			sort(b+1,b+bt+1);
			print(b[y]);
			buf2[++p3]='\n';
			//printf("%lld\n",b[y]);
		}
	}
	getwr();
	return 0;
}
