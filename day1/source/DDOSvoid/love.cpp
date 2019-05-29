#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define maxn 100010
#define ll long long
#define cn const node
using namespace std;

int n, m;

int w[maxn];

struct Edge {
    int to, next, w; 
} e[maxn]; int head[maxn], c1; 
inline void add_edge(int u, int v, int w) {
    e[c1].to = v; e[c1].w = w;
    e[c1].next = head[u]; head[u] = c1++; 
}

int fa[maxn], f[maxn];
void Dfs(int u, int Fa) {
    for (int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].to, w = e[i].w; if (v == Fa) continue ; 
        f[v] = w; fa[v] = u; Dfs(v, u); 
    }
}

int g[maxn], p1, p2, p3; ll dp[maxn], ans[maxn], Max;
void dfs(int u, int fa) {
    dp[u] = 0; g[u] = u; 
    for (int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].to; if (v == fa) continue ; 
        dfs(v, u);
        if (dp[u] + dp[v] + f[v] > Max) {
            Max = dp[u] + dp[v] + f[v];
            p3 = u; p1 = g[u]; p2 = g[v]; 
        }
        if (dp[v] + f[v] > dp[u]) {
            dp[u] = dp[v] + f[v];
            g[u] = g[v]; 
        }
    }
}

ll sum[3010][3010], Ans; bool F = 1; 
int main() { memset(head, -1, sizeof head);
    freopen("love.in", "r", stdin);
    freopen("love.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int x, y, z; scanf("%d%d%d", &x, &y, &z);
        add_edge(x, y, z); add_edge(y, x, z); Ans += 2 * z;
    }
    Dfs(1, 0); printf("%lld ", Ans); 
    for (int i = 1; i <= m; ++i) scanf("%d", &w[i]);
    for (int i = 1; i <= m; ++i) {
        Max = 0; p1 = p2 = p3 = 1; dfs(1, 0);
        ans[i] = ans[i - 1] + Max;
        while (p1 != p3) {
            f[p1] = -f[p1];
            p1 = fa[p1]; 
        }
        while (p2 != p3) {
            f[p2] = -f[p2];
            p2 = fa[p2]; 
        }  
    }
    for (int i = 1; i <= m; ++i) {
        sort(w + 1, w + i + 1);
        for (int j = 1; j <= i; ++j) 
            sum[i][j] = sum[i][j - 1] + w[j]; 
    } int k = 0; ll mn = Ans;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= i; ++j)
            mn = min(mn, Ans - ans[j] + sum[i][j]);
        printf("%lld ", mn);
    }
    return 0; 
}
