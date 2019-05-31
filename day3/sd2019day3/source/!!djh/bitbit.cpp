#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <set>
#define rep(x, a, b) for(int x = (a); x <= (b); ++x)
#define per(x, a, b) for(int x = (a); x >= (b); --x)
#define rop(x, a, b) for(int x = (a); x < (b); ++x)
using namespace std;
typedef long long LL;
typedef unsigned int ui;
typedef double DB;
int n, m, a[505][505], b[505][505], vs[505][505];
int fa[2500005], mx;
inline int get(int x) {
	if(fa[x] == x) return x;
	return fa[x] = get(fa[x]);
}

void dfs2(int x, int y, int z) {
	a[x][y] = z;
	if(a[x + 1][y] == 1) dfs2(x + 1, y, z);
	if(a[x - 1][y] == 1) dfs2(x - 1, y, z);
	if(a[x][y + 1] == 1) dfs2(x, y + 1, z);
	if(a[x][y - 1] == 1) dfs2(x, y - 1, z);
}
int x[2500005], y[2500005];
int u = 0;
set<int> S[2500005], T[2500005];
void dfs3(int x, int y, int z) {
	if(x > n || x < 1 || y > m || y < 1) return;
	if(a[x][y] != 0) {
		if(S[z].find(get(a[x][y])) == S[z].end()) {
			S[z].insert(get(a[x][y]));
			T[a[x][y]].insert(z);
		}
		return;
	}
	vs[x][y] = 1;
	if(!vs[x + 1][y]) dfs3(x + 1, y, z);
	if(!vs[x - 1][y]) dfs3(x - 1, y, z);
	if(!vs[x][y + 1]) dfs3(x, y + 1, z);
	if(!vs[x][y - 1]) dfs3(x, y - 1, z);
}
void dfs4(int x, int y, int z, int e) {
	if(x > n || x < 1 || y > m || y < 1) return;
	int w = get(a[x][y]);
	if(w == 0) b[x][y] = 1;
	else if(T[w].size()) {
		fa[w] = z;
		set<int> :: iterator it = T[w].begin();
		while(it != T[w].end()) {
			S[*it].erase(w);
			S[*it].insert(z);
			++it;
		}
		T[w].erase(e);
		T[z].insert(T[w].begin(), T[w].end());
		T[w].clear();
		return;
	}
	a[x][y] = z;
	if((a[x + 1][y] == 0 && w == 0) || (get(a[x + 1][y]) != z && get(a[x + 1][y]))) dfs4(x + 1, y, z, e);
	if((a[x - 1][y] == 0 && w == 0) || (get(a[x - 1][y]) != z && get(a[x - 1][y]))) dfs4(x - 1, y, z, e);
	if((a[x][y + 1] == 0 && w == 0) || (get(a[x][y + 1]) != z && get(a[x][y + 1]))) dfs4(x, y + 1, z, e);
	if((a[x][y - 1] == 0 && w == 0) || (get(a[x][y - 1]) != z && get(a[x][y - 1]))) dfs4(x, y - 1, z, e);
}
int AS = 0, t = 0;
char D[50000005];
void dfs(int op) {
	++AS;
	rep(i, 1, n) rep(j, 1, m) b[i][j] = 0;
	int c = 1;
	rep(i, 1, n) rep(j, 1, m) if(a[i][j] == 1) dfs2(i, j, ++c), fa[c] = c;
	int N = c - 1;


	rep(i, 1, n) rep(j, 1, m) vs[i][j] = 0;
	rep(i, 1, u) x[i] = y[i] = 0, S[i].clear();
	u = 0;


	rep(i, 1, n) rep(j, 1, m) {
		if(a[i][j] == 0 && vs[i][j] == 0) {
			++u; x[u] = i; y[u] = j;
			dfs3(i, j, u);
		}
	}


	while(N > 1) {
		int z = 0, wz = 0;;
		rep(i, 1, u) {
			if(S[i].size() > z) {
				z = S[i].size();
				wz = i;
			}
		}
		N -= z - 1;
		++c; fa[c] = c;
		dfs4(x[wz], y[wz], c, wz);
	}


	
	if(op == 1) D[++t] = '+';
	else D[++t] = '-';
	D[++t] = '\n';
	rep(i, 1, n) {rep(j, 1, m) {
		if(a[i][j]) D[++t] = '1';
		else D[++t] = '0';
		}
		D[++t] = '\n';
	}
	rep(i, 1, n) rep(j, 1, m) a[i][j] = b[i][j];
	if(c != 2) dfs(op ^ 1);
}
char W[1005];
int main() {
	freopen("bitbit.in", "r", stdin);
	freopen("bitbit.out", "w", stdout);
	scanf("%d%d", &n, &m);
	int bj = 0;
	rep(i, 1, n) {
		scanf("%s", W + 1);
		rep(j, 1, m) a[i][j] = (W[j] == '1'), bj |= a[i][j];
	}
	if(bj == 0) {
		puts("0");
		return 0;
	}
	dfs(1);
	cout << AS << endl;
	printf("%s", D + 1);
	return 0;
}
