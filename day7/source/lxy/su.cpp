#include <iostream>
#include <cstdio>
#include <cctype>
#define il inline
#define re register
#define gc getchar
#define LL long long
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
int read()
{
	re bool p = 0;
	re char ch;
	re int s = 0;
	while (ch = getchar(), p |= ch == '-', ch < '0' || ch > '9')
		;
	while (s = s * 10 + ch - '0', ch = getchar(), ch >= '0' && ch <= '9')
		;
	return s * (p ? -1 : 1);
}
struct io
{
	char obuf[ 22 << 20 ] , * t;
	int a[40];
	io() : t( obuf )
	{
		freopen( "su.in" , "r" , stdin );
		freopen( "su.out" , "w" , stdout );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
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
	}
} ip;
#define print ip.print
const int MAXN = 5000000;
int cnt = 0;
int n;
int head[MAXN], nxt[MAXN], to[MAXN];
int dep[MAXN], fa[MAXN], vis[MAXN];
int col[MAXN];
il void ins(re int u, re int v)
{
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
}
il void insert(re int u, re int v)
{
	ins(u, v);
	ins(v, u);
}
il void dfs(re int u)
{
	dep[u] = dep[fa[u]] + 1;
	for (re int i = head[u]; i; i = nxt[i])
		if (to[i] != fa[u])
			dfs(to[i]);
}
il void change_one(re int x, re int y)
{
	col[x] = y;
}
int qu[MAXN + 10], l, r;
il void change_all(re int x, re int y)
{
	if (y == col[x])
		return;
	l = r = 0;
	qu[r++] = x;
	while (l != r)
	{
		int u = qu[l++];
		if (l > MAXN)
			l = 0;
		for (int i = head[u]; i; i = nxt[i])
			if (col[to[i]] == col[u])
			{
				qu[r++] = to[i];
				if (r > MAXN)
					r = 0;
			}
		col[u] = y;
	}
}
void query(re int x)
{
	print(col[x]);
	*ip.t++ = ' ';
	int MIN = 0x3fffffff, MAX = -0x3fffffff;
	re int sze = 0;
	l = r = 0;
	qu[r++] = x;
	fill(vis + 1, vis + 1 + n, 0);
	vis[x] = 1;
	while (l != r)
	{
		re int u = qu[l++];
		++sze;
		MIN = min(MIN, dep[u]);
		MAX = max(MAX, dep[u]);
		if (l > MAXN)
			l = 0;
		for (re int i = head[u]; i; i = nxt[i])
			if (col[to[i]] == col[u] && !vis[to[i]])
			{
				qu[r++] = to[i];
				vis[to[i]] = 1;
				if (r > MAXN)
					r = 0;
			}
	}
	print(sze);
	*ip.t++ = ' ';
	print(MAX - MIN + 1);
	*ip.t++ = '\n';
	
}
int main()
{
	n = read();
	fa[1] = read();
	for (re int i = 2; i <= n; ++i)
	{
		fa[i] = read();
		insert(i, fa[i]);
	}
	dfs(1);
	for (re int i = 1; i <= n; ++i)
		col[i] = read();
	re int m;
	m = read();
	int opt,x, y;
	for (re int i = 1; i <= m; ++i)
	{
		opt = read();
		x = read();
		if (opt == 3)
			query(x);
		else
		{
			y = read();
			if (opt == 1)
				change_one(x, y);
			else 	
				change_all(x, y);
		}
	}
	return 0;
}


