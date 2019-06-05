#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct io
{
	char ibuf[ 20<<20 ] , * s , obuf[ 10<<20 ] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "su.in" , "r" , stdin );
		freopen( "su.out" , "w" , stdout );
		fread( s = ibuf , 1 ,  20<<20  , stdin );
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
		* t++ = ' ';
	}
	inline void pc(register char u)
	{
		* t++ = u;
	}
} ip;
#define read ip.read
#define print ip.print
#define pc ip.pc
struct Edge
{
	int nxt,to;
}edge[200003];
struct Node
{
	int x,c;
};
queue<Node> q;
int n,m,cnt;
int head[100003],col[100003],dep[100003],f[100003],b[100003],num[100003];
int Max[100003],Min[100003],d[100003];
bool v[100003];
void addedge(int u,int v)
{
	edge[++cnt].nxt=head[u];
	edge[cnt].to=v;
	head[u]=cnt;
}
void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	f[x]=fa;
	for(int i=head[x];i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		if(to==fa) continue;
		dfs(to,x);
	}
}
void bfs()
{
	int now=0;
	memset(v,0,sizeof(v));
	for(int i=1;i<=n;i++)
		if(col[f[i]]!=col[i])
		{
			q.push((Node){i,++now});
			v[i]=true;
		}
	while(!q.empty())
	{
		int x=q.front().x,c=q.front().c;
		q.pop();
		b[x]=c;
		for(int i=head[x];i;i=edge[i].nxt)
		{
			int to=edge[i].to;
			if(col[to]==col[x]&&!v[to])
			{
				q.push((Node){to,c});
				v[to]=true;
			}
		}
	}
	for(int i=1;i<=now;i++)
	{
		num[i]=Max[i]=0;
		Min[i]=100000;
	}
	for(int i=1;i<=n;i++)
		num[b[i]]++;
	for(int i=1;i<=n;i++)
	{
		Max[b[i]]=max(Max[b[i]],dep[i]);
		Min[b[i]]=min(Min[b[i]],dep[i]);
	}
	for(int i=1;i<=now;i++)
		d[i]=Max[i]-Min[i]+1;
}
void modify1(int x,int y)
{
	col[x]=y;
	bfs();
}
void modify2(int x,int y)
{
	for(int i=1;i<=n;i++)
		if(b[i]==b[x]) col[i]=y;
	bfs();
}
void query(int x)
{
	print(col[x]);
	print(num[b[x]]);
	print(d[b[x]]);
	pc('\n');
}
int main()
{
	n=read();
	read();
	for(int i=2;i<=n;i++)
	{
		int x=read();
		addedge(i,x);
		addedge(x,i);
	}
	for(int i=1;i<=n;i++)
		col[i]=read();
	dfs(1,0);
	bfs();
	m=read();
	while(m--)
	{
		int opt=read(),x=read();
		if(opt==1)
		{
			int y=read();
			modify1(x,y);
		}
		else if(opt==2)
		{
			int y=read();
			modify2(x,y);
		}
		else if(opt==3) query(x);
	}
	return 0;
}
