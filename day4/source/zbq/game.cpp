
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ll long long
#define M 100010
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
int  n, m, a[M];
int main() {
	freopen("game.in", "r", stdin); freopen("game.out", "w", stdout);
	for(int T = read(); T; T--) {
		n = read(), m = read();
		for(int i = 1; i <= n; i++) a[i] = read() & 1;
		if((n + m) % 2 == 0) {
			puts("A");
			continue;
		}
		if(m == 0) {
			bool f = false;
			for(int i = 1; i <= n; i += 2) {
				if(a[i] == 0) f = true;
			}
			puts(f ? "A" :"B");
		} else {
			bool f = false;
			bool d = true, e = true;
			for(int i = 1; i <= n; i += 2) {
				if(a[i] == 0) {
					for(int j = i + 1; j <= n; j += 2) {
						if(a[j] == 0) d = false;
					}
					if(a[i + 1] != 0) {
						for(int j = i + 3; j <= n; j += 2) {
							if(a[j] == 0) e = false;
						}
					}
					else e = false;
					break;
				}
			}
			if(d || e) f = true;
			puts(f ? "B" : "A");
		}
	}
	return 0;
}
/*
1
6 0
1 1 1 1 1 1

1
7 1
1 1 1 1 1 1 1

1
7 1
0 0 1 0 1 1 1

1
8 1

1 0 1 0 1 1 0 1

1
8 1
1 0 0 1 0 1 0 1
*/


