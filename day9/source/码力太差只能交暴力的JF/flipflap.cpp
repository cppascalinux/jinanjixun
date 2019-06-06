#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#define maxn 400010
#define re register
#define FOR(i, l, r) for(re int i = l ; i <= r; ++i)
using namespace std;

int n, m, c, r, t, x, y, z, k, res;
int sq;
int a[maxn], b[maxn], tag[maxn], ans[maxn], val[maxn];

inline int read(){
    int x=0;int f=1;char c=getchar();
    while(c<'0'||c>'9'){
        if(c==-1) return 0;
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c<='9'&&c>='0'){
        x=(x<<1)+(x<<3)+(c^'0');
        c=getchar();
    }
    return x*f;
}

inline int ls(int x) {
	return x << 1;
}

inline int rs(int x) {
	return x << 1 | 1;
}

void push_up(int x) {
	ans[x] = ans[ls(x)] + ans[rs(x)];
}

void change(int qx, int qy, int x, int y, int z, int p) {
	if(qx <= x && y <= qy && x == y) {
		ans[p] += k;
		return;
	}
	int mid = (x+y) >> 1;
	if(qx <= mid) 
	  change(qx, qy, x, mid, z, ls(p));
	if(qy > mid)
	  change(qx, qy, mid+1, y, z, rs(p));
	push_up(p);
}

void query(int qx, int qy, int x, int y, int k, int p) {
	if(qx <= x && y <= qy) {
		if(ans[p] <= k)
		  ++res;
		if(x == y)
		  return;
	}
	int mid = (x+y) >> 1;
	if(qx <= mid) 
	  query(qx, qy, x, mid, k, ls(p));
	if(qy > mid)
	  query(qx, qy, mid+1, y, k, rs(p));	  
}

int main() {
	freopen("flipflap.in", "r", stdin);
	freopen("flipflap.out", "w", stdout);
	n = read(), m = read();
	FOR(i, 1, m) {
		t = read();
		x = read();
		y = read();
		k = read();
		if(t == 1) {
			change(x, y, 1, n, k, 1);
		}
		if(t == 2) {
			res = 0;
			query(x, y, 1, n, k, 1);
			printf("%d\n", res);
		}
	}
}
