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

struct io {
	char ibuf[ 40 << 20 ], *s, obuf[ 20 << 20 ], *t;
	int a[24];
	io() : t( obuf ) {
		freopen( "yuki.in" , "r" , stdin );
		freopen( "yuki.out" , "w" , stdout );
		fread( s = ibuf , 1 ,  40 << 20  , stdin );
	}
	~io() {
		fwrite( obuf , 1 , t - obuf , stdout );
		fclose(stdin);
		fclose(stdout);
	}
	inline int read() {
		register int u = 0;
		while( * s < 48 ) s++;
		while( * s > 32 )
			u = u * 10 + * s++ - 48;
		return u;
	}
	template < class T >
	inline void print( register T u ) {
		static int * q = a;
		if( !u ) * t++ = 48;
		else {
			while( u ) * q++ = u % 10 + 48 , u /= 10;
			while( q != a ) * t++ = * --q;
		}
		* t++ = '\n';
	}
	inline void pc (register char u) {
		* t++ = u;
	}
} ip;

#define read ip.read
#define print ip.print
#define pc ip.pc

const int N = 1e6 + 650;

int head[N], to[N << 1], val[N], nxt[N << 1], tot;
int dep[N], fa[N], dfn[N], d[N];

void add(int x, int y) { to[++ tot] = y, nxt[tot] = head[x], head[x] = tot; }

void dfs(int now, int f) {
	dep[now] = dep[f] + 1;
	fa[now] = f;
	dfn[now] = ++ dfn[0];
	for(int i = head[now]; i; i = nxt[i]) {
		if(to[i] == f) continue;
		dfs(to[i], now);
	}
}

void ch(int x, int y, int v) {
	if(dep[x] < dep[y]) swap(x, y);
	while(dep[x] > dep[y]) {
		val[x] += v;
		x = fa[x];
	}
	while(x != y) {
		val[x] += v;
		val[y] += v;
		x = fa[x];
		y = fa[y];
	}
	val[x] += v;
}

int kth(int x, int y) {
	vi p;
	p.pb(val[x]);
	for(int i = head[x]; i; i = nxt[i]) p.pb(val[to[i]]);
	sort(p.begin(), p.end());
	return p[y - 1];
}

struct tree_array {
	LL t[N];
	void add(int x, int v) {
		for(int i = x; i < N; i += (i & -i)) t[i] += v;
	}
	LL query(int x) {
		LL ans = 0;
		for(int i = x; i; i -= (i & -i)) ans += t[i];
		return ans;
	}
	tree_array() { memset(t, 0, sizeof t); }
} t;

void change(int x, int y, int v) {
	x = dfn[x];
	y = dfn[y];
	if(x > y) swap(x, y);
	t.add(y + 1, -v);
	t.add(x, v);
}

LL getkth(int x, int k) {
	vector <LL> p;
	p.pb(t.query(dfn[x]));
	for(int i = head[x]; i; i = nxt[i]) {
		p.pb(t.query(dfn[to[i]]));
	}
	sort(p.begin(), p.end());
	return p[k - 1];
}

int main() {
	int n = read(), m = read(), x, y, v;
	rep(i, 1, n) val[i] = read();
	rep(i, 1, n - 1) x = read(), y = read(), add(x, y), add(y, x), ++ d[x], ++ d[y];
	if(n <= 1000 && m <= 1000) {
		dfs(1, 0);
		rep(i, 1, m) {
			int op = read();
			if(op == 1) x = read(), y = read(), v = read(), ch(x, y, v);
			else x = read(), y = read(), print(kth(x, y));
		}
		return 0;
	}
	int pos = 1;
	rep(i, 1, n) if(d[i] == 1) { pos = i; break; }
	dfs(pos, 0);
	rep(i, 1, n) t.add(dfn[i], val[i]), t.add(dfn[i] + 1, -val[i]);
	rep(i, 1, m) {
		int op = read();
		if(op == 1) x = read(), y = read(), v = read(), change(x, y, v);
		else x = read(), y = read(), print(getkth(x, y));
	}
	return 0;
}

