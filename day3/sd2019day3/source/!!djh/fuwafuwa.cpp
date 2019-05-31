#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define rep(x, a, b) for(int x = (a); x <= (b); ++x)
#define per(x, a, b) for(int x = (a); x >= (b); --x)
#define rop(x, a, b) for(int x = (a); x < (b); ++x)
using namespace std;
typedef long long LL;
typedef unsigned int ui;
typedef double DB;
int T, n, m, a, b, rt, tt;
int de[505], ch[505][2], vl[505];
int NEW(int z) {
	++tt;
	de[tt] = ch[tt][1] = ch[tt][0] = 0;
	vl[tt] = z;
	return tt;
}
void ins(int &x, int z) {
	if(x == 0) {x = NEW(z); return;}
	if(z < vl[x]) ins(ch[x][0], z);
	else ins(ch[x][1], z);
	de[ch[x][0]] = de[ch[x][1]] = de[x] + 1;
}
int main() {
	freopen("fuwafuwa.in", "r", stdin);
	freopen("fuwafuwa.out", "w", stdout);
	scanf("%d", &T);
	rep(i, 1, T) {
		rt = 0; tt = 0;
		scanf("%d%d%d%d", &a, &b, &m, &n);
		rep(i, 1, n) {
			a = (a + b) % m;
			ins(rt, a);
		}
		printf("%d\n", de[n]);
	}
	return 0;
}
