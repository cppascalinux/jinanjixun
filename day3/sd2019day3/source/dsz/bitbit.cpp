#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define rep(a,b,c) for(int a=b;a<=c;++a)

using namespace std;

namespace hty {
	int N, M, st, ans, s[503][503], z[503][503];

	void solve(int mode) {
		if(mode == 3) {
			rep(i, 1, M) if(z[1][i - 1] && !z[1][i]) ++ans;
			printf("%d\n", ans);
			rep(i, 1, M) {
				if(!z[1][i - 1] && z[1][i]) st = i;
				if(z[1][i - 1] && !z[1][i]) {
					memset(s, 0, sizeof s);
					rep(j, st, i - 1) s[1][j] = 1;
					puts("+");
					rep(j, 1, M) printf("%d", s[1][j]);
					puts("");
				}
			}
		}
	}

	int main() {
		scanf("%d%d", &N, &M);
		rep(i, 1, N) rep(j, 1, M)
			scanf("%1d", &z[i][j]);
		if(N == 1) solve(3);
		return 0;
	}
}

int main() {
	freopen("bitbit.in", "r", stdin);
	freopen("bitbit.out", "w", stdout);
	return hty::main();
}

