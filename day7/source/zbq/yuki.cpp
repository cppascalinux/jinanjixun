
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

int siz[M * 50], ch[M * 50][2], father[M * 50], valuer[M * 50], tot;

struct SPlay {
	int root, sz;
	void pushup(int now) {
		// cerr << "!";
		if(now == 0)return;
		siz[now] = siz[ch[now][0]] + siz[ch[now][1]] + 1;
	}
	void rotate(int &rt, int x) {
		int y = father[x], q = father[y];
		bool dy = (ch[y][1] == x), dz = (ch[q][1] == y);
		if(y == rt) father[x] = 0, rt = x;
		else father[x] = q, ch[q][dz] = x;
		father[ch[x][dy ^ 1]] = y;
		ch[y][dy] = ch[x][dy ^ 1];
		ch[x][dy ^ 1] = y;
		father[y] = x;
		//if(y == 0) cout << "?";
		pushup(y);
		pushup(x);
	}

	void splay(int &rt, int x) {
		while(x != rt) {
			//	cerr << ")";
			int y = father[x], q = father[y];
			if(y != rt) {
				if((ch[y][1] == x) ^ (ch[q][1] == y)) rotate(rt, x);
				else rotate(rt, y);
			}
			rotate(rt, x);
		}
	}


	void insert(int x) {
		sz++;
		if(root == 0) {
			root = ++tot;
			valuer[root] = x;
			siz[root] = 1;
			return;
		}
		int now = root, f = 0;
		while(1) {
			if(now == 0) {
				tot++;
				valuer[tot] = x;
				siz[tot] = 1;
				ch[f][valuer[f] < x] = tot;
				father[tot] = f;
				pushup(f);
				splay(root, tot);
				return;
			}
			f = now;
			now = ch[now][valuer[now] < x];
		}
	}

	int kth(int k) {
		if(k == 0) return 0;
		int now = root;
		while(1) {
			if(k > siz[ch[now][0]] + 1) {
				k -= siz[ch[now][0]] + 1;
				now = ch[now][1];
			} else {
				if(k == siz[ch[now][0]] + 1) return valuer[now];
				else now = ch[now][0];
			}
		}
	}

	void find(int x) {
		int now = root;
		while(1) {
			//	cerr << "!";
			if(valuer[now] == x) {
				splay(root, now);
				return;
			}
			if(valuer[now] < x) now = ch[now][1];
			else now = ch[now][0];
		}
	}

	int p() {
		int x = ch[root][0];
		while(ch[x][1]) x = ch[x][1];
		return x;
	}


	void del(int x) {
		find(x);
		if(ch[root][0] == 0 || ch[root][1] == 0) {
			root = ch[root][0] + ch[root][1];
			father[root] = 0;
			return;
		}
		int lbig = p(), ort = root;
		splay(root, lbig);
		father[ch[ort][1]] = root;
		ch[root][1] = ch[ort][1];
		pushup(root);

	}

} sp[M];

vector<int> to[M];
int v[M], fa[M], dfn[M], low[M], id[M], sz[M], son[M], du[M], ver[M], deep[M], top[M], n, m, dft;
int biao;



struct T {
#define ls now << 1
#define rs now << 1 | 1
#define lson l, mid, now << 1
#define rson mid + 1, r, now << 1 | 1
	int v[M << 2], laz[M << 2], len[M << 2];

	void add(int now, int vv) {
		laz[now] += vv;
		v[now] += len[now] * vv;
	}

	void pushdown(int now) {
		add(ls, laz[now]);
		add(rs, laz[now]);
		laz[now] = 0;
	}

	void build(int l, int r, int now) {
		len[now] = r - l + 1;
		if(l == r) {
			v[now] = ver[id[l]];
			return;
		}
		int mid = (l + r) >> 1;
		build(lson);
		build(rson);
	}

	int get(int l, int r, int now, int pl) {
		if(l > pl || r < pl) return 0;
		if(l == r) return v[now];
		pushdown(now);
		int mid = (l + r) >> 1;
		return get(lson, pl) + get(rson, pl);
	}

	void modify(int l, int r, int now, int ln, int rn, int z) {
		if(l > rn || r < ln) return;
		if(l >= ln && r <= rn) {
			add(now, z);
			return;
		}
		pushdown(now);
		int mid = (l + r) >> 1;
		modify(lson, ln, rn, z);
		modify(rson, ln, rn, z);
	}
} t;
void dfs(int now, int f) {
	fa[now] = f;
	sz[now] = 1;
	deep[now] = deep[f] + 1;
	for(int i = 0; i < to[now].size(); i++) {
		int vj = to[now][i];
		if(vj == f) continue;
		dfs(vj, now);
		sz[now] += sz[vj];
		if(sz[vj] > sz[son[now]]) son[now] = vj;
	}
}

void dfss(int now) {
	dfn[now] = ++dft;
	id[dft] = now;
	if(son[now]) {
		top[son[now]] = top[now];
		dfss(son[now]);
	}
	for(int i = 0; i < to[now].size(); i++) {
		int vj = to[now][i];
		if(vj == fa[now] || vj == son[now]) continue;
		top[vj] = vj;
		dfs(vj, now);
	}
	low[now] = dft;
}
int sta[M], tp, p[M], td;

int lca(int a, int b) {
	while(top[a] != top[b]) {
		if(deep[top[a]] < deep[top[b]]) swap(a, b);
		a = fa[top[a]];
	}
	if(deep[a] > deep[b]) swap(a, b);
	return a;
}

void getnew(int now, int x, int y, int z) {
	

}

void modify(int x, int y, int z) {
	while(top[x] != top[y]) {
		if(deep[top[x]] < deep[top[y]]) swap(x, y);
		t.modify(1, n, 1, dfn[top[x]], dfn[x], z);
		x = fa[top[x]];
	}
	if(deep[x] > deep[y]) swap(x, y);
	t.modify(1, n, 1, dfn[x], dfn[y], z);
	for(int i = 1; i <= td; i++) {
		getnew(p[i], x, y, z);
	}
}

int getver(int x) {
	return t.get(1, n, 1, dfn[x]);
}

int main() {
	//	freopen("sample1.in", "r", stdin); freopen("sample.out", "w", stdout);
	freopen("yuki.in", "r", stdin); freopen("yuki.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; i++) ver[i] = read();
	for(int i = 1; i < n; i++) {
		int vi = read(), vj = read();
		du[vi]++;
		du[vj]++;
		to[vi].push_back(vj);
		to[vj].push_back(vi);
	}
	biao = 5 * sqrt(n);
	dfs(1, 0);
	top[1] = 1;
	dfss(1);
	if(n <= 1000 && m <= 1000) {
		for(int t = 1; t <= m; t++) {
			int op = read();
			if(op == 1) {
				int x = read(), y = read(), z = read();
				while(x != y) {
					if(deep[x] < deep[y]) swap(x, y);
					ver[x] += z;
					x = fa[x];
				}
				ver[x] += z;
			} else {
				int x = read(), y = read();
				tp = 0;
				sta[++tp] = ver[x];
				for(int i = 0; i < to[x].size(); i++) {
					int vj = to[x][i];
					sta[++tp] = ver[vj];
				}
				sort(sta + 1, sta + tp + 1);
				cout << sta[y] << "\n";
			}
		}
	} else {
		t.build(1, n, 1);
		for(int i = 1; i <= n; i++) {
			if(du[i] > biao) {
				p[++td] = i;
				sp[i].insert(ver[i]);
				for(int j = 0; j < to[i].size(); j++) {
					int vj = to[i][j];
					sp[i].insert(vj);
				}
			}
		}
		for(int i = 1; i <= m; i++) {
			int op = read();
			if(op == 1) {
				int x = read(), y = read(), z = read();
				modify(x, y, z);
			} else {
				int x = read(), y = read();
				if(du[x] <= biao) {
					tp = 0;
					sta[++tp] = getver(x);
					for(int i = 0; i < to[x].size(); i++) {
						int vj = to[x][i];
						sta[++tp] = getver(vj);
					}
					sort(sta + 1, sta + tp + 1);
					cout << sta[y] << "\n";
				} else {
					cout << sp[x].kth(y) << "\n";
				}
			}
		}
	}
	return 0;
}


