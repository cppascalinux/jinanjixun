#include <iostream>
#include <cstdio>
#include <cmath>
#include <map>
#define maxn 100001
#define maxm 301
#define mp make_pair
using namespace std;

typedef pair<int, int> pii;

map<pii, int> ma;

int n, m;

int a[maxn];

struct _ {
    int lans;
    inline void solve_1() {
        int x, y; scanf("%d%d", &x, &y); x^= lans; y ^= lans;
        for (int i = 1; i <= n; ++i) if (a[i] == x) a[i] = y; 
    }

    inline void solve_2() {
        int x, y, p1 = -1, p2 = -1, ans = n; scanf("%d%d", &x, &y);
        x ^= lans; y ^= lans;
        for (int i = 1; i <= n; ++i) {
            if (a[i] == x) p1 = i;
            if (a[i] == y) p2 = i;
            if (~p1 && ~p2) ans = min(ans, abs(p1 - p2));
        }
        if (ans == n) puts("Chtholly"), lans = 0;
        else printf("%d\n", (lans = ans)); 
    }

    int Main() {
        for (int i = 1; i <= m; ++i) {
            int opt; scanf("%d", &opt);
            switch(opt) {
            case 1 : solve_1(); break;
            case 2 : solve_2(); break; 
            }
        }
        return 0; 
    }
} _;

int num, blo, l[maxm], r[maxm], bl[maxn], d[maxm][maxn], mx;
void init_blo() {
    blo = min(200, (int) sqrt(n)); num = n / blo; if (n % blo) ++num;
    for (int i = 1; i <= n; ++i) bl[i] = (i - 1) / blo + 1;
    for (int i = 1; i <= num; ++i) {
        l[i] = (i - 1) * blo + 1;
        r[i] = i * blo; 
    } r[num] = n;
    for (int i = n; i; --i) d[bl[i]][a[i]] = i;
    for (int i = 1; i <= num; ++i) {
        for (int j = l[i]; j <= r[i]; ++j)
            for (int k = j + 1; k <= r[i]; ++k) {
                int x = a[j], y = a[k];
                if (x > y) swap(x, y);
                if (!ma.count(mp(x, y))) ma[mp(x, y)] = k - j;
                ma[mp(x, y)] = min(ma[mp(x, y)], k - j);
            }
    }
}

int lans, s1[maxm], s2[maxm], ans;
void work(int x, int y) {
    s1[num + 1] = s2[num + 1] = -1; 
    for (int i = num; i; --i) {
        s1[i] = s1[i + 1];
        s2[i] = s2[i + 1];
        if (d[i][x]) s1[i] = d[i][x];
        if (d[i][y]) s2[i] = d[i][y]; 
    } int p1 = 0, p2 = 0; 
    for (int i = 1; i < num; ++i) {
        p1 = d[i][x]; p2 = d[i][y];
        if (~s1[i + 1] && p2) ans = min(ans, s1[i + 1] - p2);
        if (~s2[i + 1] && p1) ans = min(ans, s2[i + 1] - p1); 
    }
    if (x > y) swap(x, y); 
    if (ma.count(mp(x, y))) ans = min(ans, ma[mp(x, y)]); 
}

int main() {
	freopen("busy.in", "r", stdin);
	freopen("busy.out", "w", stdout);
    scanf("%d%d", &n, &m); 
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), mx = max(mx, a[i]);
    init_blo(); 
    if (n <= 1000 && m <= 1000) return _.Main();
    for (int i = 1; i <= m; ++i) {
        int opt, x, y; scanf("%d%d%d", &opt, &x, &y); x ^= lans; y ^= lans;
        ans = n; work(x, y);
        if (ans == n) puts("Chtholly"), lans = 0;
        else printf("%d\n", (lans = ans)); 
    }
    return 0;
}
