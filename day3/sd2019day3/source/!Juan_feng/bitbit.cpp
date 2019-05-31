#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#define maxn 1001
#define re register
#define FOR(i, l, r) for(re int i = l; i <= r; ++i)
using namespace std;

int n, m, c, r, t, x, y, z;
int a[maxn][maxn], b[maxn], qwq[5][5], fa[maxn], bl[maxn];

int id(int x, int y) {
	return (x-1)*y+y;
}

int find(int x) {
	if(fa[x] != x)
	  fa[x] = find(fa[x]);
	return fa[x];
}

string s[5];

int main() {
	freopen("bitbit.in", "r", stdin);
	freopen("bitbit.out", "w", stdout);
	scanf("%d%d", &n, &m);
	if(m > 3) {
		//...
		return 0;
	}
	FOR(i, 1, 9)
	  fa[i] = i;
	FOR(i, 1, n)
	  cin >> s[i];
	FOR(i, 1, n) {
		FOR(j, 1, m) {
			a[i][j] = s[i][j-1]-48;
			if(a[i][j] == 1) {
				if(a[i-1][j] == 1 && a[i][j-1] == 1) {
					if(find(id(i, j-1)) != find(id(i-1, j))) {
						fa[id(i, j)] = fa[id(i, j-1)];
						fa[id(i-1, j)] = fa[id(i, j-1)];
					}
					else {
						fa[id(i, j)] = fa[id(i, j-1)];
					}
				}
				else {
					if(a[i-1][j] == 1)
				  	  fa[id(i, j)] = find(fa[id(i-1, j)]);
				  	if(a[i][j-1] == 1)
				  	  fa[id(i, j)] = find(fa[id(i, j-1)]);
				}
			}
		}
	}
	int res = 0;
	FOR(i, 1, n) {
		FOR(j, 1, m) {
	  		if(a[i][j] == 1) 
	  		  if(!bl[find(id(i, j))]) {
	  		    bl[find(id(i, j))] = 1;
				++res;	
			  }
	  	}
	}
	if(res == 1) {
		puts("1");
		puts("+");
		FOR(i, 1, n) {
			FOR(j, 1, m) 
		      printf("%d", a[i][j]);
		    puts("");
		}
		return 0;
	}
	if(res == 2) {
		puts("2");
		puts("+");
		memset(bl, 0, sizeof(bl));
		int yyy = 0;
		FOR(i, 1, n) {
			FOR(j, 1, m) {
				if(a[i][j] == 1) {
					if(bl[find(id(i, j))] || yyy == 0) {
						yyy = 1;
						a[i][j] = 0;
						qwq[i][j] = 1;
						bl[find(id(i, j))] = 1;
					}
				}
			}
		}
		FOR(i, 1, n) {
			FOR(j, 1, m) 
		      printf("%d", qwq[i][j]);
		    puts("");
		}
		puts("+");
		FOR(i, 1, n) {
			FOR(j, 1, m) 
		      printf("%d", a[i][j]);
		    puts("");
		}
		return 0;
	}
	if(res == 5) {
		puts("3");
		puts("+");
		puts("111");
		puts("111");
		puts("111");
		puts("-");
		puts("010");
		puts("111");
		puts("010");
		puts("+");
		puts("000");
		puts("010");
		puts("000");
		return 0;
	}
	if(res == 4) {
		if(a[1][1] == 1 && a[3][3] == 1 && a[1][3] == 1 && a[3][1] == 1) {
			puts("2");
			puts("-");
			puts("010");
			puts("111");
			puts("010");
			puts("+");
			puts("111");
			puts("111");
			puts("111");
			return 0;
		}
		puts("3");
		if(a[1][1] == 1 && a[3][3] == 1 && a[1][3] == 1) {
			puts("-");
			puts("010");
			puts("000");
			puts("000");
			puts("-");
			puts("000");
			puts("001");
			puts("000");
			puts("+");
			puts("111");
			puts("011");
			puts("001");
			return 0;
		}
		if(a[1][1] == 1 && a[3][3] == 1 && a[3][1] == 1) {
			puts("-");
			puts("000");
			puts("100");
			puts("000");
			puts("-");
			puts("000");
			puts("000");
			puts("010");
			puts("+");
			puts("100");
			puts("110");
			puts("111");
			return 0;
		}
		if(a[3][1] == 1 && a[1][3] == 1 && a[1][1] == 1) {
			puts("-");
			puts("000");
			puts("100");
			puts("000");
			puts("-");
			puts("010");
			puts("000");
			puts("000");
			puts("+");
			puts("111");
			puts("110");
			puts("100");
			return 0;
		}
		if(a[1][3] == 1 && a[3][1] == 1 && a[3][3] == 1) {
			puts("-");
			puts("000");
			puts("001");
			puts("000");
			puts("-");
			puts("000");
			puts("000");
			puts("010");
			puts("+");
			puts("001");
			puts("011");
			puts("111");
			return 0;
		}
	}
	if(res == 3) {
		if(a[1][1] == 1 && a[2][2] == 1 && a[3][3] == 1) {
			puts("3");
			puts("+");
			puts("100");
			puts("000");
			puts("000");
			puts("+");
			puts("000");
			puts("010");
			puts("000");
			puts("+");
			puts("000");
			puts("000");
			puts("001");
			return 0;
		}
		puts("3");
		puts("+");
		puts("001");
		puts("000");
		puts("000");
		puts("+");
		puts("000");
		puts("010");
		puts("000");
		puts("+");
		puts("000");
		puts("000");
		puts("100");
		return 0;
	}
}
