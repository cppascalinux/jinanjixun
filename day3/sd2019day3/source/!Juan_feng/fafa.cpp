#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define maxn 100010 
#include <algorithm>
#define re register
#define FOR(i, l, r) for(re int i = l; i <= r; ++i)
using namespace std;

int n, m, c, r, t, x, y, z, k;
int a[maxn], b[maxn], ans;

int pd() {
	int res = 0, bl = 0, maxx = 0, siz = 0;
	FOR(i, 1, n) {
		FOR(j, k, n) {
	  	    int now = i+j-1;
	  	    if(now > n)
	  	      continue;
	  	    bl = 0;
	  	    FOR(L, 1, j) {
	  	    	if(L%2 == 0 && (a[i+L-2] < a[i+L-1] || (a[i+L-1] > a[i+L] && L != j))) {
	  	      		bl = 1;
	  	      		break;
			  	}
			}
	  	      
			if(bl == 0)
			  maxx = j;
		    else
		      break;
	 	}
	}
	return maxx;
}

void dfs(int x) {
	if(x > n) {
		int qwq = pd();
		if(qwq == k)
		  ++ans;
		return;
	}
	FOR(i, 1, n) {
		if(b[i] == 1)
		  continue;
		b[i] = 1;
		a[x] = i;
		dfs(x+1);
		b[i] = 0;
		a[x] = 0;
	}
}

int main() {
	freopen("fafa.in", "r", stdin);
	freopen("fafa.out", "w", stdout);
	scanf("%d%d", &n, &k);
	dfs(1);
	printf("%d", ans);
}

