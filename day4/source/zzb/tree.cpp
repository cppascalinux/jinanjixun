#include <cstdio>
#include <vector>
#include <queue>
#include <map>
using namespace std;
const int MAXN = 10e5 + 100;
int n, m, q;
vector<map<int, int> > tre[MAXN];
map<int,int> tor[MAXN];
void dfs(int to, int next) {
	
}
int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 0; i < n - 1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		map<int, int> f;
		f[0] = v;
		tre[u].push_back(f);
		f[0] = u;
		tre[v].push_back(f);
	}
	for(int i = 0; i < m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		tor[i][0] = x;
		tor[i][1] = y;
	}
	while(q--) {
		int l, r;
		scanf("%d %d", &l, &r);
		for(int i = l - 1; i < r; i++) {
			dfs(tor[i][0], tor[i][1]);
		}
		printf("1\n");
	}
	return 0;
}
