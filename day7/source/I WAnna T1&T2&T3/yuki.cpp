#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
struct io
{
	char ibuf[40<<20] , * s , obuf[20<<20] , * t;
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
		fclose(stdin);fclose(stdout);
	}
	inline int read()
	{
		register int u = 0;
		while( * s < 48 ) s++;
		while( * s > 32 )
			u = (u<<1)+(u<<3) + ((* s++) ^ 48);
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
	inline void pc(register char u){
		* t++ = u;
	}
} ip;
#define read ip.read
#define print ip.print
#define pc ip.pc
struct Edge{
	int v,nxt;
}e[2000010];int tot;
int first[1000010];
void build(int u,int v)
{
	e[++tot]=(Edge){v,first[u]};
	first[u]=tot;
	return ;
}
int dfn[1000010],top[1000010],now;
int son[1000010],siz[1000010],dep[1000010],fa[1000010];
void dfs1(int u,int lst)
{
	fa[u]=lst;
	dep[u]=dep[lst]+1;
	siz[u]=1;
	for(int i=first[u];i;i=e[i].nxt)
		if(e[i].v!=lst){
			dfs1(e[i].v,u);
			siz[u]+=siz[e[i].v];
			if(siz[e[i].v]>siz[son[u]])
				son[u]=e[i].v;
		}
	return ;
}
void dfs2(int u,int f)
{
	top[u]=f;
	dfn[u]=++now;
	if(son[u])dfs2(son[u],f);
	for(int i=first[u];i;i=e[i].nxt)
		if(!dfn[e[i].v])dfs2(e[i].v,e[i].v);
	return ;
}
int n,m;
int c[1000010];
int lowbit(int x)
{
	return x&(-x);
}
void add(int x,int y)
{
	for(;x<=n;x+=lowbit(x))
		c[x]+=y;
	return ;
}
int query(int x)
{
	int ans=0;
	for(;x;x-=lowbit(x))
		ans+=c[x];
	return ans;
}
void Add(int x,int y,int z)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		add(dfn[top[x]],z);add(dfn[x]+1,-z);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y])swap(x,y);
	add(dfn[y],z);add(dfn[x]+1,-z);
	return ;
}
int val[1000010];
int a[1000010];
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)val[i]=read();
	for(int i=1;i<n;i++)
	{
		int u,v;
		u=read();v=read();
		build(u,v);
		build(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(int i=1;i<=n;i++)
		add(dfn[i],val[i]),add(dfn[i]+1,-val[i]);
	while(m--)
	{
		int op=read();
		if(op==1)
		{
			int x,y,z;
			x=read();y=read();z=read();
			Add(x,y,z);
		}
		else{
			int x,y;
			x=read();y=read();
			int cnt=1;
			a[1]=query(dfn[x]);
			for(int i=first[x];i;i=e[i].nxt)
				a[++cnt]=query(dfn[e[i].v]);
			sort(a+1,a+cnt+1);
			print(a[y]);
		}
	}
	return 0;
}
