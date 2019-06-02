#include <iostream>
#include <cstdio>
#include <cstring>
#define maxn 10010
#define re register
#define FOR(i, l, r) for(re int i = l; i <= r; ++i)
using namespace std;

int n, m, c, r, t, x, y, z;
int a[maxn];

int main() {
	freopen("one.in", "r", stdin);
	freopen("one.out", "w", stdout);
	scanf("%d", &n);
	FOR(i, 1, n)
	  scanf("%d", &a[i]); 
	if(n == 1) {
		puts("0");
		return 0;
	}
	if(a[1] > a[2])
	  puts("1");
	else
	  puts("0");
}
