#include <cstdio>
#include <cctype>
#include <algorithm>
#define maxn 100005
#define Inf 0x3f3f3f3f
inline int read() {
	int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return d;
}

int n, m, lans;
int a[maxn];

int main() {
	freopen("busy.in", "r", stdin);
	freopen("busy.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	while(m--) {
		int op = read(), x = read()^lans, y = read()^lans;
		if(op == 1) {for(int i = 1; i <= n; ++i) if(a[i] == x) a[i] = y;}
		else {
			int i = 0, j = 0, k = 0, l = Inf;
			for(; k <= n; ++k) if(a[k] == x) break;
			if(k > n) puts("Chtholly"), lans = 0;
			else {
				for(; i <= n; ++i) {
					if(a[i] == x) {
						if(j) l = std::min(l, i-j);
						k = i;
					}
					else if(a[i] == y) {
						if(k) l = std::min(l, i-k);
						j = i;
					}
				}
				if(l < Inf) printf("%d\n", lans = l);
				else puts("Chtholly"), lans = 0;
			}
		}
	}
	return 0;
}
