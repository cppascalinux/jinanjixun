#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define maxn 1201
#define int long long
#define re register
#define FOR(i, l, r) for(re int i = l; i <= r; ++i)
using namespace std;

int n, m, c, r, t, x, y, z, a, b;
int root;
int siz[maxn], depth[maxn], val[maxn], son[maxn][2];

int ins(int now, int x) {
	if(!root) {
		root = x;
		depth[x] = 0;
		return now;
	}
	if(!now)
	  return x;
	if(val[now] > val[x]) {
	 	son[now][0] = ins(son[now][0], x);	
	 	depth[son[now][0]] = depth[now] + 1;
	}
	else {
		son[now][1] = ins(son[now][1], x);
		depth[son[now][1]] = depth[now] + 1;
	}
	return now;
}

signed main() {
	freopen("fuwafuwa.in", "r", stdin);
	freopen("fuwafuwa.out", "w", stdout);
	scanf("%lld", &t);
	while(t--) {
		scanf("%lld%lld%lld%lld", &a, &b, &m, &n);
		memset(depth, 0, sizeof(depth));
		memset(val, 0, sizeof(val));
		memset(son, 0, sizeof(son));
		root = 0;
		FOR(i, 1, n) {
			val[i] = (a+i*b)%m; 
			ins(root, i);
		}
		printf("%lld\n", depth[n]);
	}
}
