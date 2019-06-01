#include <cstdio>
#include <cctype>
#define maxn 100005
inline int read() {
	int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return d;
}

int n, m;
int a[maxn];

void work() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read()&1;
	if(n == 1) {
		puts(a[1] ? "B" : "A");
		return;
	}
	if(n == 2) {
		if(!m) puts("A");
		else if(a[1] || a[2]) puts("B");
		else puts("A");
		return;
	}
	if(n&1) {
		if(!m) {
			int fl = 1;
			for(int i = 1; i <= n; i += 2)
				if(!a[i]) {
					fl = 0; break;
				}
			puts(fl ? "B" : "A");
		}
		else puts("A");
	}
	else {
		if(!m) {
			puts("A");
			return;
		}
		int l, r;
		for(l = 1; l <= n && a[l]; l += 2);
		for(r = n; r >= 1 && a[r]; r -= 2);
		if(l+1 < r) puts("A");
		else if(l > r) puts("B");
		else if(a[l] || a[r]) puts("B");
		else puts("A");
	}
}

int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	for(int q = read(); q; --q) work();
	return 0;
}
