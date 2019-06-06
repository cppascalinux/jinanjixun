#include <cstdio>
#include <cctype>
#define maxn 1000005
inline int read() {
	int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return d;
}

int n, m;
int a[maxn];

int main() {
	freopen("plasticmem.in", "r", stdin);
	freopen("plasticmem.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	while(m--) {
		int op = read(), l = read(), r = read();
		if(op == 1) {for(int i = l; i <= r; ++i) a[i] = 0;}
		else if(op == 2) {for(int i = l; i <= r; ++i) a[i] = 1;}
		else if(op == 3) {for(int i = l; i < r; ++i) a[i] |= a[i+1];}
		else if(op == 4) {for(int i = r; i > l; --i) a[i] |= a[i-1];}
		else if(op == 5) {for(int i = l; i < r; ++i) a[i] &= a[i+1];}
		else if(op == 6) {for(int i = r; i > l; --i) a[i] &= a[i-1];}
		else {
			int sum = 0;
			for(int i = l; i <= r; ++i) sum += a[i];
			printf("%d\n", sum);
		}
	}
	return 0;
}
