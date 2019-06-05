#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <vector>
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
		freopen( "yuki.in" , "r" , stdin );
		freopen( "yuki.out" , "w" , stdout );
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
		* t++ = '\n';
	}
} ip;
#define print ip.print
int n, m;
namespace subtask1
{
vector<int> V;
int cnt = 0;
const int MAXN = 200000;
int val[MAXN];
int head[MAXN], nxt[MAXN], to[MAXN];
int dep[MAXN], fa[MAXN];
void ins(int u, int v)
{
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
}
void insert(int u, int v)
{
	ins(u, v);
	ins(v, u);
}
void dfs(int u, int f)
{
	fa[u] = f;
	dep[u] = dep[f] + 1;
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != f)
			dfs(to[i], u);
}
void modify(int x, int y, int w)
{
	if (dep[x] < dep[y])
		swap(x, y);
	while (dep[x] != dep[y])
		val[x] += w, x = fa[x];
	while (x != y)
		val[x] += w, val[y] += w, x = fa[x], y = fa[y];
	val[x] += w;
}
int query(int x, int y)
{
	V.clear();
	V.push_back(val[x]);
	for (int i = head[x]; i; i = nxt[i])
		V.push_back(val[to[i]]);
	nth_element(V.begin(), V.begin() + y - 1, V.end());
	return V[y - 1];
}
void run()
{
	int u, v, opt, w;
	for (int i = 1; i <= n; ++i)
		val[i] = read();
	for (int i = 1; i < n; ++i)
	{
		u = read(), v = read();
		insert(u, v);
	}
	dfs(1, 0);
	for (int i = 1; i <= m; ++i)
	{
		opt = read(), u = read(), v = read();
		if (opt == 1)
		{
			w = read();
			modify(u, v, w);
		}
		else
			printf("%d\n", query(u, v));
	}
}
} // namespace subtask1
namespace bit
{
const int MAXN = 5000000;
int tree[MAXN];
int n;
#define lowbit(x) ((x) & -(x))
il void modify(re int x, re int w)
{
	while (x <= n)
		tree[x] += w, x += lowbit(x);
}
il int query(re int x)
{
	re int ans = 0;
	while (x)
		ans += tree[x], x -= lowbit(x);
	return ans;
}
} // namespace bit
namespace subtask2
{
vector<int> V;
int cnt = 0;
const int MAXN = 5000000;
int val[MAXN];
int du[MAXN], dep[MAXN];
int head[MAXN], nxt[MAXN], to[MAXN], fa[MAXN];
il void ins(re int u, re int v)
{
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
}
il void insert(re int u, re int v)
{
	++du[u];
	++du[v];
	ins(u, v);
	ins(v, u);
}
il void dfs(re int u)
{
	fa[u] = -1;
	dep[u] = 1;
	for (re int i = head[u]; i; i = nxt[i])
		if (to[i] != fa[u])
		{
			fa[to[i]] = u;
			dep[to[i]] = dep[u] + 1;
			u = to[i];
			i = head[u];
		}
}
il void modify(int x, int y, re int w)
{
	if (dep[x] > dep[y])
		swap(x, y);
	bit::modify(dep[x], w);
	bit::modify(dep[y] + 1, -w);
}
il int query(re int x, re int y)
{
	V.clear();
	V.push_back(bit::query(dep[x]));
	for (re int i = head[x]; i; i = nxt[i])
		V.push_back(bit::query(dep[to[i]]));
	nth_element(V.begin(), V.begin() + y - 1, V.end());
	return V[y - 1];
}
void run()
{
	re int rt;
	re int u, v, opt, w;
	bit::n = n;
	for (re int i = 1; i <= n; ++i)
		val[i] = read();
	for (int i = 1; i < n; ++i)
	{
		u = read(), v = read();
		insert(u, v);
	}
	rt = 1;
	for (re int i = 1; i <= n; ++i)
		if (du[i] == 1)
			rt = i;
	dfs(rt);
	for (re int i = 1; i <= n; ++i)
		modify(i, i, val[i]);
	for (re int i = 1; i <= m; ++i)
	{
		opt = read(), u = read(), v = read();
		if (opt == 1)
		{
			w = read();
			modify(u, v, w);
		}
		else
			print(query(u, v));
	}
}
} // namespace subtask2
void run()
{
	n = read(), m = read();
	if (n * 1ll * m <= 1000000ll)
		subtask1::run();
	else
		subtask2::run();
}
int main()
{
	run();
	return 0;
}


