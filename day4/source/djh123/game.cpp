#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(x, a, b) for(int x = (a); x <= (b); ++x)
#define per(x, a, b) for(int x = (a); x >= (b); --x)
#define rop(x, a, b) for(int x = (a); x < (b); ++x)
using namespace std;
typedef long long LL;
typedef unsigned int ui;
typedef double DB;
int op, T;
int n, a[100005];
int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &op);
		rep(i, 1, n) scanf("%d", &a[i]), a[i] = a[i] & 1;
		if(n == 1) {
			if(a[1] == 1) puts("B");
			else puts("A");
		}else if(op == 0) {
			if((n & 1) == 0) {puts("A"); continue;}
			int K = 1;
			for(int i = 1; i <= n; i += 2) K &= a[i];
			puts(K ? "B" : "A");
		} else {
			if(n & 1) {puts("A"); continue;}
			int K = 0;
			for(int i = 1; i <= n; i += 2) {
				if(a[i] & 1) continue;
				else {
					if((i & 1) == 0) {K = 100; break;}
					if(a[i + 1] == 1) ++i;
					else {K = 100; break;}
				}
			}
			puts(K <= 1 ? "B" : "A");
		}
	}
}
