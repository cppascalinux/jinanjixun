
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#include<set>
#define ll long long
#define M  100010
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
int a[M], id[M], sz[M], n, m, cor[M], cnt;
vector<int> st[M];
vector<int>::iterator it;
int biao, sta[M], tp, as;
int f1[M], f2[M], minn[333][M];
int ab(int x) {
	return x > 0 ? x : -x;
}

void nw(int c) {
	cor[c] = ++tp;
	sta[tp] = c;
	memset(f1, 0, sizeof(f1));
	memset(f2, 0, sizeof(f2));
	for(int i = 1; i <= n; i++) {
		if(a[i] == c) f1[i] = i;
		else f1[i] = f1[i - 1];
	}
	for(int i = n; i >= 1; i--) {
		if(a[i] == c) f2[i] = i;
		else f2[i] = f2[i + 1];
	}
	for(int i = 1; i <= n; i++) minn[tp][a[i]] = min(minn[tp][a[i]], min(ab(i - f1[i]), ab(i - f2[i])));
}
int c[M], d[M], cn, dn;
int main() {
	freopen("busy.in", "r", stdin); freopen("busy.out", "w", stdout);
//	freopen("sample1.in", "r", stdin);
//	freopen("sample.outt", "w", stdout);

	n = read(), m = read();
	for(int i = 1; i <= n; i++) {
		a[i] = read();
		sz[a[i]]++;
		st[a[i]].push_back(i);
	}
	if(n <= 1000) {
		int tt = 0;
		while(m--) {
		//	tt++;
			int op = read(), x = read() ^ as, y = read() ^ as;
			if(op == 1) {
				for(int i = 1; i <= n; i++) if(a[i] == x) a[i] = y;
			} else {
				cn = dn = 0;
				for(int i = 1; i <= n; i++) {
					if(a[i] == x) c[++cn] = i;
					if(a[i] == y) d[++dn] = i;
				}
				int nowans = 0x3e3e3e3e, cbe = 1, dbe = 1;
				while(cbe <= cn && dbe <= dn) {
					nowans = min(nowans, ab(c[cbe] - d[dbe]));
					if(c[cbe] < d[dbe]) cbe++;
					else dbe++;
				}
				if(nowans == 0x3e3e3e3e) puts("Chtholly"), as = 0;
				else printf("%d\n", nowans), as = nowans;
			}
	//		if(tt > 1000) return 0;
		}
	} else {
		memset(minn, 0x3e, sizeof(minn));
		biao = sqrt(n);
		for(int i = 1; i <= 100000; i++) {
			if(sz[i] > biao) {
				nw(i);
			}
		}
		while(m--) {
			int op = read(), x = read() ^ as, y = read() ^ as;
			if(op == 1) {
			} else {
				if(sz[x] > sz[y]) swap(x, y);
				if(sz[y] > biao) {
					if(sz[x]) {
						as = minn[cor[y]][x];
						cout << as << "\n";
					} else {
						puts("Chtholly"), as = 0;
					}
				} else {
					cn = dn = 0;
					for(it = st[x].begin(); it != st[x].end(); it++) {
						c[++cn] = *it;
					}
					for(it = st[y].begin(); it != st[y].end(); it++) {
						d[++dn] = *it;
					}
					int nowans = 0x3e3e3e3e, cbe = 1, dbe = 1;
					while(cbe <= cn && dbe <= dn) {
						nowans = min(nowans, ab(c[cbe] - d[dbe]));
						if(c[cbe] < d[dbe]) cbe++;
						else dbe++;
					}
					if(nowans == 0x3e3e3e3e) puts("Chtholly"), as = 0;
					else printf("%d\n", nowans), as = nowans;
				}
			}
		}
	}
	return 0;
}


