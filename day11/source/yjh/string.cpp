#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define maxn 9000005
inline int read() {
	int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return d;
}

inline int popcnt(int x) {
	int ans = 0; while(x) ++ans, x -= x&-x;
	return ans;
}

int n, k, q;
int s[maxn];
int sa[maxn], rk[maxn], tp[maxn], tax[maxn];
int m;

inline void rsort() {
	for(int i = 1; i <= m; ++i) tax[i] = 0;
	for(int i = 1; i <= n; ++i) ++tax[rk[i]];
	for(int i = 1; i <= m; ++i) tax[i] += tax[i-1];
	for(int i = n; i >= 1; --i) sa[tax[rk[tp[i]]]--] = tp[i];
}

void getsa() {
	m = 2;
	for(int i = 1; i <= n; ++i) rk[i] = s[i]+1, tp[i] = i;
	rsort();
	for(int p = 0, w = 1; p < n && w <= n; m = p, w <<= 1) {
		p = 0;
		for(int i = n-w+1; i <= n; ++i) tp[++p] = i;
		for(int i = 1; i <= n; ++i)
			if(sa[i] > w) tp[++p] = sa[i]-w;
		rsort();
		std::swap(rk, tp);
		rk[sa[1]] = p = 1;
		for(int i = 2; i <= n; ++i)
			rk[sa[i]] = (tp[sa[i]] == tp[sa[i-1]] && (sa[i]+w > n ? -1 : tp[sa[i]+w]) == (sa[i-1]+w > n ? -1 : tp[sa[i-1]+w])) ? p : ++p;
	}
}

int main() {
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
	k = read(), q = read();
	n = 1<<k;
	for(int i = 0; i < n; ++i)
		s[i+1] = popcnt(i)&1;
	getsa();
	for(int i = 1; i <= n; ++i) {
		int p = read();
		printf("%d ", sa[p]-1);
	}
	return 0;
}
