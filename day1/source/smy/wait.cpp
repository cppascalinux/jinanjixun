#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <set>
#define rep(x, a, b) for(int x = (a); x <= (b); ++x)
#define rop(x, a, b) for(int x = (a); x < (b); ++x)
#define per(x, a, b) for(int x = (a); x >= (b); --x)
using namespace std;
typedef long long LL;
typedef double DB;
typedef unsigned int ui;
set<int> S;
struct node {
	int wz, op, w, id;
}p[60005];
bool operator < (const node &a, const node &b) {
	return a.wz < b.wz;
}
int tt, l[30005], r[30005], w[30005], m;
namespace work2 {
	void main() {
		int N = 1 << m;
		rop(S, 0, N) {
			int bj = 1;
			rep(i, 1, m) if(w[i] != -1 && (S >> (i - 1) & 1) != w[i]) {bj = 0; break;}
			if(bj == 0) continue;
			int nw = 0;
			rep(i, 1, tt) {
				if(p[i].op == 0) {
					if((S >> (p[i].id - 1)) & 1) ++nw;
					else  --nw;
				}
				if(p[i].op == 1) {
					if((S >> (p[i].id - 1)) & 1) --nw;
					else  ++nw;
				}
				if(nw > 1 || nw < -1) {bj = 0; break;}
			}
			if(bj) {rep(i, 1, m) cout << (S >> (i - 1) & 1) << " "; return;}
		}
		puts("-1");
	}
}
int main() {
	freopen("wait.in", "r", stdin);
	freopen("wait.out", "w", stdout);
	scanf("%d%*d", &m);
	int BJ = 1;
	rep(i, 1, m) {
		scanf("%d%d%d", &l[i], &r[i], &w[i]);
		p[++tt].wz = l[i];
		p[tt].op = 0;
		p[tt].w = w[i];
		p[tt].id = i;
		p[++tt].wz = r[i];
		p[tt].op = 1;
		p[tt].w = w[i];
		p[tt].id = i;
		if(w[i] != -1) BJ = 0;
	}
	sort(p + 1, p + 1 + tt);
	if(m <= 20) work2 :: main();
	else if(BJ) work1 :: main();
	return 0;
}
