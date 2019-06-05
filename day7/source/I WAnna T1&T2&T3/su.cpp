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
		freopen( "su.in" , "r" , stdin );
		freopen( "su.out" , "w" , stdout );
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
		* t++ = ' ';
	}
	inline void pc(register char u){
		* t++ = u;
	}
} ip;
#define read ip.read
#define print ip.print
#define pc ip.pc
int col[100010];
int q[100010],head,tail;
bool vis[100010];
struct Edge{
	int v,nxt;
}e[200010];int tot;
int first[100010];
void build(int u,int v)
{
	e[++tot]=(Edge){v,first[u]};
	first[u]=tot;
	return ;
}
void bfs(int x)
{
	for(int i=1;i<=tail;i++)
		vis[q[i]]=false;
	head=0,tail=1;
	q[tail]=x;
	while(head<tail)
	{
		head++;
		int u=q[head];
		vis[u]=true;
		for(int i=first[u];i;i=e[i].nxt)
			if(col[e[i].v]==col[x]&&!vis[e[i].v])
				q[++tail]=e[i].v;
	}
	return ;
}
int dep[100010];
int main()
{
	int n=read();
	for(int i=1;i<=n;i++)
	{
		int v=read();
		if(v)build(i,v);
		if(v)build(v,i);
		dep[i]=dep[v]+1;
	}
	for(int i=1;i<=n;i++)
		col[i]=read();
	int m=read();
	while(m--)
	{
		int op=read();
		if(op==1)
		{
			int x=read();
			int y=read();
			col[x]=y;
		}
		else if(op==2)
		{
			int x=read();
			int y=read();
			bfs(x);
			for(int i=1;i<=tail;i++)
				col[q[i]]=y;
		}
		else{
			int x=read();
			bfs(x);
			int mx=0,mn=1e9;
			for(int i=1;i<=tail;i++)
				mx=max(mx,dep[q[i]]),
				mn=min(mn,dep[q[i]]);
			print(col[x]);
			print(tail);
			print(mx-mn+1);
			pc('\n');
		}
	}
	return 0;
}
