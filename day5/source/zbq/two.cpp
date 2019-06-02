
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#include<map>
#include<set>
#define ll long long
#define M 200010
#define mmp make_pair
const int inf = 0x3e3e3e3e;
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
int siz[M * 50], ch[M * 50][2], fa[M * 50], ver[M * 50], tot;

struct SPlay {
	int root, sz;
	void pushup(int now) {
		// cerr << "!";
		if(now == 0)return;
		siz[now] = siz[ch[now][0]] + siz[ch[now][1]] + 1;
	}
	void rotate(int &rt, int x) {
		int y = fa[x], q = fa[y];
		bool dy = (ch[y][1] == x), dz = (ch[q][1] == y);
		if(y == rt) fa[x] = 0, rt = x;
		else fa[x] = q, ch[q][dz] = x;
		fa[ch[x][dy ^ 1]] = y;
		ch[y][dy] = ch[x][dy ^ 1];
		ch[x][dy ^ 1] = y;
		fa[y] = x;
		//if(y == 0) cout << "?";
		pushup(y);
		pushup(x);
	}

	void splay(int &rt, int x) {
		while(x != rt) {
		//	cerr << ")";
			int y = fa[x], q = fa[y];
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
			ver[root] = x;
			siz[root] = 1;
			return;
		}
		int now = root, f = 0;
		while(1) {
			if(now == 0) {
				tot++;
				ver[tot] = x;
				siz[tot] = 1;
				ch[f][ver[f] < x] = tot;
				fa[tot] = f;
				pushup(f);
				splay(root, tot);
				return;
			}
			f = now;
			now = ch[now][ver[now] < x];
		}
	}

	int kth(int k) {
		if(k > sz) return inf;
		if(k == 0) return 0;
		int now = root;
		while(1) {
			if(k > siz[ch[now][0]] + 1) {
				k -= siz[ch[now][0]] + 1;
				now = ch[now][1];
			} else {
				if(k == siz[ch[now][0]] + 1) return ver[now];
				else now = ch[now][0];
			}
		}
	}

	void find(int x) {
		int now = root;
		while(1) {
		//	cerr << "!";
			if(ver[now] == x) {
				splay(root, now);
				return;
			}
			if(ver[now] < x) now = ch[now][1];
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
			fa[root] = 0;
			return;
		}
		int lbig = p(), ort = root;
		splay(root, lbig);
		fa[ch[ort][1]] = root;
		ch[root][1] = ch[ort][1];
		pushup(root);

	}

} sp[M];

struct Note {
	map<char, int> ch;
	int sz, fa, len;
} note[M];
int lst = 1, cnt = 1;
vector<int> to[M];
char s[M];
int n, k, sz[M];
int id[M];
set<int> st[M];
int pig[M];
void insert(char c, int ed) {
	int p = ++cnt, f = lst;
	lst = p;
	note[cnt].len = note[f].len + 1;
	note[cnt].sz = 1;
	//st[cnt].insert(ed);
	pig[cnt] = ed;
	while(f && note[f].ch.find(c) == note[f].ch.end()) note[f].ch[c] = p, f = note[f].fa;
	if(f == 0) {
		note[p].fa = 1;
	} else {
		int q = note[f].ch[c];
		if(note[q].len == note[f].len + 1) note[p].fa = q;
		else {
			int nq = ++cnt;
			note[nq] = note[q];
			note[nq].sz = 0;
			note[nq].len = note[f].len + 1;
			note[p].fa = note[q].fa = nq;
			note[nq].fa = f;
			while(f && note[f].ch[c] == q) note[f].ch[c] = nq, f = note[f].fa;
		}
	}
}
set<int>::iterator it, tt, gg;

void a_insert(int now, int v) {
	it = st[now].lower_bound(v);
	if(it == st[now].end()) {
		if(!st[now].empty()) {
			tt = it;
			it--;
			sp[now].insert(v - *it);
		}
	} else if(it == st[now].begin()) {
		sp[now].insert(*it - v);
	} else {
		tt = it;
		it--;
		sp[now].del(*tt - *it);
		sp[now].insert(*tt - v);
		sp[now].insert(v - *it);
	}
	st[now].insert(v);
}

ll ans = 0;
void work(int now, int tot, int L, int R) {
	if(sz[now] < k) return;
	int x = sz[now] - k;
	int L1 = sp[now].kth(x), R1 = sp[now].kth(x + 1) - 1;
	L = max(L, L1);
	R = min(R, R1);
//	cerr << " " << max(0, R - L + 1) << "\n";
	ans += max(0, R - L + 1);
}

void dfs(int now) {
	sz[now] = note[now].sz;
	for(int i = 0; i < to[now].size(); i++) {
		int vj = to[now][i];
		dfs(vj);
	}
	for(int i = 0; i < to[now].size(); i++) {
		int vj = to[now][i];
		if(sz[id[now]] < sz[id[vj]]) swap(id[now], id[vj]);
		sz[id[now]] += sz[id[vj]];
		for(gg = st[id[vj]].begin(); gg != st[id[vj]].end(); gg++) {
		//	cerr << *gg << "\n";
			a_insert(id[now], *gg);
		}
	}
//	cerr << "!";
	if(pig[now]) a_insert(id[now], pig[now]);
//	cerr << now << " " << note[now].len - note[note[now].fa].len<< "";
	work(id[now], sz[now], note[note[now].fa].len + 1, note[now].len);
}


int main() {
	freopen("two.in", "r", stdin); freopen("two.out", "w", stdout);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	k = read();

	for(int i = 1; i <= n; i++) {
		insert(s[i], i);
	}
	for(int i = 2; i <= cnt; i++) {
		to[note[i].fa].push_back(i);
	//	cerr << note[i].fa << " ";
	}
//	for(int i = 1; i <= cnt; i++) cerr << pig[i] << " ";
	
	for(int i = 1; i <= cnt; i++) id[i] = i;
	dfs(1);
	cout << ans << "\n";
	return 0;
}


