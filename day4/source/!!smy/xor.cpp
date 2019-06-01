#include <cstdio>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <bitset>
#include <iostream>
#include <queue>

using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef unsigned long long ULL;
typedef double db;
typedef pair <int, int> pii;
typedef vector <int> vi;

#define Fi first
#define Se second
#define pb push_back
#define mp make_pair

#define rep(i, x, y) for(int i = (x); i <= (y); ++ i)
#define rop(i, x, y) for(int i = (x); i < (y); ++ i)
#define per(i, x, y) for(int i = (x); i >= (y); -- i)
#define por(i, x, y) for(int i = (x); i > (y); -- i)

const int N = 1e5 + 50;
int m, q;

struct Base {
	uint f[30];
	int cnt;
	Base() { memset(f, 0, sizeof f); cnt = 0; }
	void init() { memset(f, 0, sizeof f); cnt = 0; }
	void insert(uint v) {
		per(i, m, 0) {
			if(f[i] == 0) {
				f[i] = v;
				++ cnt;
				return ;
			}
			v ^= f[i];
		}
	}
};

Base operator+ (Base a, const Base &b) {
	rep(i, 0, m) if(b.f[i]) a.insert(b.f[i]);
	return a;
}

struct Segment_tree_node {
	int l, r;
	Base v;
} t[N << 2];

void bt(int now, int l, int r) {
	t[now].l = l;
	t[now].r = r;
	if(l == r) return ;
	int mid = (l + r) >> 1;
	int ls = now << 1;
	int rs = ls | 1;
	bt(ls, l, mid);
	bt(rs, mid + 1, r);
}

void ch(int now, int pos, uint val) {
	t[now].v.insert(val);
	if(t[now].l == t[now].r) return ;
	int ls = now << 1;
	int rs = ls | 1;
	if(pos <= t[ls].r) ch(ls, pos, val);
	if(pos >= t[rs].l) ch(rs, pos, val);
}

void er(int now, int pos) {
	if(t[now].l == t[now].r) {
		t[now].v.init();
		return ;
	}
	int ls = now << 1;
	int rs = ls | 1;
	if(pos <= t[ls].r) er(ls, pos);
	if(pos >= t[rs].l) er(rs, pos);
	t[now].v = t[ls].v + t[rs].v;
}

int op[N];
uint v[N];

int main() {
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	int size_s = 0;
	int max_size_s = 0;
	set <int> s;
	map <uint, int> pos;
	scanf("%d%d", &m, &q); -- m;
	rep(i, 1, q) {
		scanf("%d%u", &op[i], &v[i]);
		if(op[i] == 1) ++ size_s, max_size_s = max(max_size_s, size_s);
		else -- size_s;
	}
	rep(i, 1, max_size_s) s.insert(i);
	bt(1, 1, max_size_s);
	rep(i, 1, q) {
		if(op[i] == 1) {
			int ipos = *s.begin();
			s.erase(s.begin());
			pos[v[i]] = ipos;
			ch(1, ipos, v[i]);
		}
		else {
			int ipos = pos[v[i]];
			s.insert(ipos);
			er(1, ipos);
		}
		printf("%u\n", 1u << t[1].v.cnt);
	}

}
		

