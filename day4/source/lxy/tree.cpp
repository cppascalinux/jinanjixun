#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#define il inline
#define re register
#define gc getchar
#define LL long long
using namespace std;
void rd(int &s)
{
    s = 0;
    bool p = 0;
    char ch;
    while (ch = gc(), p |= ch == '-', !isdigit(ch))
        ;
    while (s = s * 10 + ch - '0', ch = gc(), isdigit(ch))
        ;
    s *= (p ? -1 : 1);
}
int rt;
const int N = 5000;
int cnt = 0;
vector<int> hq[N];
int dep[N];
int head[N], nxt[N], to[N];
int x[N], y[N];
int fa[N];
int vis[N];
int visit[N];
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
    dep[u] = dep[f] + 1;
    fa[u] = f;
    for (int i = head[u]; i; i = nxt[i])
        if (to[i] != f)
            dfs(to[i], u);
}
void modify(int id, int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    while (dep[u] != dep[v])
    {
        hq[id].push_back(u);
        u = fa[u];
    }
    while (u != v)
    {
        hq[id].push_back(u);
        hq[id].push_back(v);
        u = fa[u], v = fa[v];
    }
    hq[id].push_back(u);
}
int ans = 0;
void getans(int u)
{
	visit[u] = 1;
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa[u] && vis[to[i]] && !visit[to[i]])
			getans(to[i]);
}
void get(int u)
{
	if (vis[u] && !visit[u])
	{
		++ans;
		getans(u);
	}
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa[u])
			get(to[i]);
}
int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    srand(time(NULL));
    int n, m, q, u, v;
    rd(n), rd(m), rd(q);
    rt = rand() % n + 1;
    for (int i = 1; i < n; ++i)
    {
        rd(u);
        rd(v);
        insert(u, v);
    }
    dfs(rt, 0);
    for (int i = 1; i <= m; ++i)
    {
        rd(u), rd(v);
        modify(i, u, v);
    }
    for (int i = 1; i <= q; ++i)
    {
        ans = 0;
        rd(u), rd(v);
        fill(vis + 1, vis + 1 + n, 0);
        fill(visit + 1, visit + 1 + n, 0);
        for (int j = u; j <= v; ++j)
            for (vector<int>::iterator it = hq[j].begin(); it != hq[j].end(); ++it)
            	vis[*it] = 1;
    	get(rt);
		printf("%d\n", ans);
    }
    return 0;
}

