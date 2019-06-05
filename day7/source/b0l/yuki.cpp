#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
struct io
{
	char ibuf[ 40<<20 ] , * s , obuf[ 5<<20 ] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "yuki.in" , "r" , stdin );
		freopen( "yuki.out" , "w" , stdout );
		fread( s = ibuf , 1 ,  40<<20  , stdin );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
	}
	inline int read()
	{
		register int u = 0;
		while( * s < 48 ) s++;
		while( * s > 32 )
			u =( u << 3 ) + ( u << 1) + ( (* s++) ^ 48 );
		return u;
	}
	template < class T >
	inline void print( register T u )
	{
		static int * q = a;
		if( !u ) * t++ = 48;
		else
		{
			while( u ) * q++ = u % 10 + 48 , u /= 10;
			while( q != a )
				* t++ = * --q;
		}
		* t++ = '\n';
	}
} ip;
#define read ip.read
#define print ip.print
struct Edge
{
	int nxt,to;
}edge[2000003];
int n,m,cnt,idx;
int a[1000003];
int head[1000003];
int dep[1000003],f[1000003],top[1000003],son[1000003],siz[1000003];
int s[1000003],id[1000003],t[1000003];
int lowbit(int x){return x&(-x);};
void modify(int i,int x)
{
	for(;i<=n;i+=lowbit(i))
		a[i]+=x;
}
int query(int i)
{
	int res=0;
	for(;i;i-=lowbit(i))
		res+=a[i];
	return res;
}
void addedge(int u,int v)
{
	edge[++cnt].nxt=head[u];
	edge[cnt].to=v;
	head[u]=cnt;
}
void dfs1(int x,int fa)
{
	dep[x]=dep[fa]+1;
	f[x]=fa;
	siz[x]=1;
	int maxx=0;
	for(int i=head[x];i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		if(to==fa) continue;
		dfs1(to,x);
		siz[x]+=siz[to];
		if(siz[to]>maxx)
		{
			maxx=siz[to];
			son[x]=to;
		}
	}
}
void dfs2(int x,int topf)
{
	id[x]=++idx;
	top[x]=topf;
	if(!son[x]) return;
	dfs2(son[x],topf);
	for(int i=head[x];i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		if(to==f[x]||to==son[x]) continue;
		dfs2(to,to);
	}
}
void mrange(int x,int y,int z)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		modify(id[top[x]],z);
		modify(id[x]+1,-z);
		x=f[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	modify(id[x],z);
	modify(id[y]+1,-z);
}
int qrange(int x,int y)
{
	int now=0;
	t[++now]=query(id[x]);
	for(int i=head[x];i;i=edge[i].nxt)
		t[++now]=query(id[edge[i].to]);
	sort(t+1,t+now+1);
	return t[y];
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)
		s[i]=read();
	for(int i=1;i<n;i++)
	{
		int u,v;
		u=read();v=read();
		addedge(u,v);
		addedge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(int i=1;i<=n;i++)
		modify(id[i],s[i]),modify(id[i]+1,-s[i]);
	while(m--)
	{
		int opt,x,y;
		opt=read(),x=read(),y=read();
		if(opt==1)
		{
			int z;
			z=read();
			mrange(x,y,z);
		}
		else print(qrange(x,y));
	}
	return 0;
}
