#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define maxn 60010
#define ll long long
#define cn const node
#define INF 100000000
#define lowbit(i) ((i) & (-i)) 
using namespace std;

int n, m, s, t, ss, tt;

int a[maxn];

int l[maxn], r[maxn], c[maxn], col[maxn];
void init_hash() {
    int c1 = 0; 
    for (int i = 1; i <= m; ++i) {
        c[++c1] = l[i]; c[++c1] = r[i];
    } sort(c + 1, c + c1 + 1); n = unique(c + 1, c + c1 + 1) - c + 1; 
    for (int i = 1; i <= m; ++i) {
        l[i] = lower_bound(c + 1, c + n + 1, l[i]) - c;
        r[i] = lower_bound(c + 1, c + n + 1, r[i]) - c; 
    } 
}

int Bit[maxn];
inline void update(int l, int r, int v) {
    ++r;
    while (l <= n) Bit[l] += v, l += lowbit(l);
    while (r <= n) Bit[r] -= v, r += lowbit(r); 
}

inline int get_sum(int i) {
    int s = 0;
    while (i) s += Bit[i], i -= lowbit(i);
    return s; 
}

int ans[maxn]; bool Ans;
int main() {
    freopen("wait.in", "r", stdin);
    freopen("wait.out", "w", stdout); 
    cin >> m >> n; 
    for (int i = 1; i <= m; ++i) scanf("%d%d%d", &l[i], &r[i], &col[i]); init_hash();
    int c1 = 0; 
    for (int i = 1; i <= m; ++i) {
        if (~col[i]) continue ;
        a[++c1] = i; 
    } int M = (1 << c1) - 1;
    for (int st = 1; st <= M; ++st) {
        for (int i = 1; i <= n; ++i) Bit[i] = 0;
        for (int i = 1; i <= m; ++i) if (~col[i]) update(l[i], r[i], col[i] ? 1 : -1); 
        for (int i = 1; i <= c1; ++i) {
            if (st >> i & 1) update(l[a[i]], r[a[i]], 1);
            else update(l[a[i]], r[a[i]], -1); 
        } bool F = 1; 
        for (int i = 1; i <= n; ++i) {
            int s = get_sum(i); 
            if (s < -1 || s > 1) F = 0;
        }
        if (F) {
            Ans = 1;
            for (int i = 1; i <= c1; ++i) ans[a[i]] = st >> i & 1; 
        }
    }
    if (!Ans) return puts("-1"), 0;
    for (int i = 1; i <= m; ++i) {
        if (col[i] == -1) printf("%d ", ans[i]);
        else printf("%d ", col[i]); 
    }
    return 0;
}
