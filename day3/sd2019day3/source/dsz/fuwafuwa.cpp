#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define rep(a,b,c) for(int a=b;a<=c;++a)

using namespace std;
typedef long long ll;

int T, a, b, m;
ll N;

namespace BST {
	int rt, tot, ls[503], rs[503], key[503], dep[503];

	int New(int v) {
		key[++tot] = v;
		return tot;
	}

	int insert(int x, int y) {
		if(!x) return y;
		if(key[x] > key[y]) ls[x] = insert(ls[x], y);
		else rs[x] = insert(rs[x], y);
		return x;
	}
}
using namespace BST;

void dfs(int u, int fa) {
	if(!u) return;
	dep[u] = dep[fa] + 1;
	dfs(ls[u], u);
	dfs(rs[u], u);
}

int main() {
	freopen("fuwafuwa.in", "r", stdin);
	freopen("fuwafuwa.out", "w", stdout);
	cin >> T;
	while(T--) {
		tot = 0;
		memset(ls, 0, sizeof ls);
		memset(rs, 0, sizeof rs);
		memset(key, -1, sizeof key);
		cin >> a >> b >> m >> N;
		a = (a + b) % m;
		rt = insert(0, New(a));
		rep(i, 2, N) {
			a = (a + b) % m;
			insert(rt, New(a));
		}
		dfs(rt, 0);
		cout << dep[tot] - 1 << '\n';
	}
	return 0;
}

