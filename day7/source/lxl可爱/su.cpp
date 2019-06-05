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
		freopen( "su.in" , "r" , stdin );
		freopen( "su.out" , "w" , stdout );
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
	//	* t++ = '\n';
	}
	inline void pc (register char u) {
		* t++ = u;
	}
} ip;

#define read ip.read
#define print ip.print
#define pc ip.pc


const int N = 2e6 + 650;

int head[N], to[N << 1], val[N], nxt[N << 1], tot;
int dep[N], fa[N], dfn[N], col[N], n;

bool cmp(int x, int y) { return dep[x] < dep[y]; }

void add(int x, int y) { to[++ tot] = y, nxt[tot] = head[x], head[x] = tot; }

void dfs(int now) {
	dep[now] = dep[fa[now]] + 1;
	dfn[now] = ++ dfn[0];
	for(int i = head[now]; i; i = nxt[i]) {
		if(to[i] == fa[now]) continue;
		dfs(to[i]);
	}
}

vi bl;
int vis[N];

void getbl(int x) {
	if(vis[x]) return ;
	bl.pb(x);
	vis[x] = 1;
	for(int i = head[x]; i; i = nxt[i]) {
		if(col[to[i]] == col[x]) getbl(to[i]);
	}
}

void change(int x, int c) {
	bl.clear();
	rep(i, 1, n) vis[i] = 0;
	getbl(x);
	rop(i, 0, (int)bl.size()) col[bl[i]] = c;
}

void pt(int x) {
	bl.clear();
	rep(i, 1, n) vis[i] = 0;
	getbl(x);
	print(col[x]); pc(' ');
	print(bl.size()); pc(' ');
	sort(bl.begin(), bl.end(), cmp);
	print(dep[bl[(int)bl.size() - 1]] - dep[bl[0]] + 1); pc('\n');
}

int main() {
	n = read();
	fa[1] = read();
	rep(i, 2, n) fa[i] = read(), add(fa[i], i), add(i, fa[i]);
	rep(i, 1, n) col[i] = read();
	dfs(1);
	int m = read(), op, x, y;
	rep(i, 1, m) {
		op = read();
		if(op == 1) x = read(), y = read(), col[x] = y;
		if(op == 2) x = read(), y = read(), change(x, y);
		if(op == 3) x = read(), pt(x);
	}
}
	

