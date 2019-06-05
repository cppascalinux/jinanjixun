#include <iostream>
#include <cstdio>
#include <algorithm>
#define maxn 100010
#define lowbit(i) ((i) & (-i))
using namespace std;

int n, m;

int a[maxn];

struct _ {
    inline void solve_1() {
        int x, y, z; scanf("%d%d%d", &x, &y, &z);
        for (int i = x; i <= y; ++i) a[i] ^= z;    
    }

    inline void solve_2() {
        int x, y; scanf("%d%d", &x, &y);
        sort(a + x, a + y + 1); 
    }

    inline void solve_3() {
        int x, y, s = 0; scanf("%d%d", &x, &y);
        for (int i = x; i <= y; ++i) s ^= a[i];
        printf("%d\n", s);
    }

    int Main() {
        for (int i = 1; i <= m; ++i) {
            int opt; scanf("%d", &opt);
            switch(opt) {
            case 1 : solve_1(); break;
            case 2 : solve_2(); break;
            case 3 : solve_3(); break; 
            }
        }
        return 0; 
    }
} _;

#define lc i << 1
#define rc i << 1 | 1
struct seg {
    int v, add; 
} T[maxn * 4];

void build(int i, int l, int r) {
    if (l == r) return T[i].v = a[l], void();
    int m = l + r >> 1;
    build(lc, l, m); build(rc, m + 1, r);
    T[i].v = T[lc].v ^ T[rc].v; 
}

void update(int i, int l, int r, int L, int R, int v) {
    if (l > R || r < L) return ;
    T[i].v ^= (min(R, r) - max(l, L) + 1 & 1) * v;
    if (L <= l && r <= R) return T[i].v ^= v, void();
    int m = l + r >> 1;
    update(lc, l, m, L, R, v); update(rc, m + 1, r, L, R, v);
}

int query(int i, int l, int r, int L, int R, int v) {
    if (l > R || r < L) return 0;
    if (L <= l && r <= R) return T[i].v ^ (r - l + 1 & 1) * v;
    int m = l + r >> 1;
    return query(lc, l, m, L, R, v ^ T[i].v) ^ query(rc, m + 1, r, L, R, v ^ T[i].v);
}

inline void solve_1() {
    int x, y, z; scanf("%d%d%d", &x, &y, &z);
    update(1, 1, n, x, y, z);
}

inline void solve_3() {
    int x, y, s = 0; scanf("%d%d", &x, &y);
    printf("%d\n", query(1, 1, n, x, y, 0)); 
}


int main() {
	freopen("save.in", "r", stdin);
	freopen("save.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]); 
    if (n <= 10000 && m <= 10000) return _.Main();
    build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        int opt; scanf("%d", &opt);
        switch(opt) {
        case 1 : solve_1(); break;
        case 3 : solve_3(); break; 
        }
    }
    return 0; 
}
