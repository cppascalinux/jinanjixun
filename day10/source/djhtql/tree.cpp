#include <iostream>
#include <cstdio>
#include <cctype>
#define il inline
#define re register
#define gc getchar
#define LL long long
#define rt re int
#define file "tree"
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
int read()
{
    re bool p = 0;
    re char ch;
    re int s = 0;
    while (ch = gc(), p |= ch == '-', !isdigit(ch))
        ;
    while (s = s * 10 + ch - '0', isdigit(ch = gc()))
        ;
    return s * (p ? -1 : 1);
}
struct io
{
    char obuf[22 << 20], *t;
    int a[40];
    io() : t(obuf)
    {
        freopen(file".in", "r", stdin);
        freopen(file".out", "w", stdout);
    }
    ~io()
    {
        fwrite(obuf, 1, t - obuf, stdout);
    }
    template <class T>
    inline void print(register T u)
    {
        static int *q = a;
        if (u < 0)
            *t++ = '-', u = -u;
        if (!u)
            *t++ = 48;
        else
        {
            while (u)
                *q++ = u % 10 + 48, u /= 10;
            while (q != a)
                *t++ = *--q;
        }
        *t++ = '\n';
    }
} ip;
#define print ip.print
const int MOD = 1000000007;
namespace tree1
{
int cnt;
const int MAXN = 1000000;
int head[MAXN], nxt[MAXN], to[MAXN], val[MAXN];
int sze[MAXN], top[MAXN], dep[MAXN], fa[MAXN], son[MAXN];
int dis[MAXN], vis[MAXN];
il void ins(int u, int v, int w)
{
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
	val[cnt] = w;
}
il void insert(int u, int v, int w)
{
	ins(u, v, w);
	ins(v, u, w);
}
void dfs(rt u)
{
    sze[u] = 1; 
    dep[u] = dep[fa[u]] + 1;
    for (rt i = head[u]; i; i = nxt[i])
    {
        rt v = to[i];
        if (v == fa[u])
            continue;
        dis[v] = (dis[u] + val[i]) % MOD;
        fa[v] = u;
        dfs(v);
        sze[u] += sze[v];
        if (sze[v] > sze[son[u]])
            son[u] = v;
    }
}
il void dfs2(rt u, rt t)
{
    top[u] = t;
    if (son[u])
        dfs2(son[u], t);
    for (rt i = head[u]; i; i = nxt[i])
    {
        rt v = to[i];
        if (v == fa[u] || v == son[u])
            continue;
        dfs2(v, v);
    }
}
il int query(rt x, rt y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            y = fa[top[y]];
        else
            x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
il void init()
{
	dfs(1);
	dfs2(1, 1);
}
il int get_dis(int u, int v)
{
	return ((dis[u] + dis[v]) % MOD - 2ll * dis[query(u, v)]) % MOD;
}
}
namespace tree2
{
int cnt;
const int MAXN = 1000000;
int head[MAXN], nxt[MAXN], to[MAXN], val[MAXN];
int sze[MAXN], top[MAXN], dep[MAXN], fa[MAXN], son[MAXN];
int dis[MAXN], vis[MAXN];
il void ins(int u, int v, int w)
{
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
	val[cnt] = w;
}
il void insert(int u, int v, int w)
{
	ins(u, v, w);
	ins(v, u, w);
}
void dfs(rt u)
{
    sze[u] = 1; 
    dep[u] = dep[fa[u]] + 1;
    for (rt i = head[u]; i; i = nxt[i])
    {
        rt v = to[i];
        if (v == fa[u])
            continue;
        dis[v] = (dis[u] + val[i]) % MOD;
        fa[v] = u;
        dfs(v);
        sze[u] += sze[v];
        if (sze[v] > sze[son[u]])
            son[u] = v;
    }
}
il void dfs2(rt u, rt t)
{
    top[u] = t;
    if (son[u])
        dfs2(son[u], t);
    for (rt i = head[u]; i; i = nxt[i])
    {
        rt v = to[i];
        if (v == fa[u] || v == son[u])
            continue;
        dfs2(v, v);
    }
}
il int query(rt x, rt y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            y = fa[top[y]];
        else
            x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
il void init()
{
	dfs(1);
	dfs2(1, 1);
}
il int get_dis(int u, int v)
{
	return ((dis[u] + dis[v]) % MOD - 2ll * dis[query(u, v)]) % MOD;
}
}
int main()
{
	int n, u, v, w;
	n = read();
	for (int i = 1; i < n; ++i)
		u = read(), v = read(), w = read(), tree1::insert(u, v, w);
	for (int i = 1; i < n; ++i)
		u = read(), v = read(), w = read(), tree2::insert(u, v, w);
	tree1::init();
	tree2::init();
	LL ans = 0;
	for (int u = 1; u <= n; ++u)
		for (int v = u + 1; v <= n; ++v)
			if (u != v)
				ans = (tree1::get_dis(u, v) * 1ll * tree2::get_dis(u, v) % MOD + ans) % MOD;			
	if (ans < 0)
		ans += MOD;
	ans = ans * 2 % MOD;
	print(ans);
	return 0;
}


