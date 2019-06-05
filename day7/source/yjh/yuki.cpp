#include <cstdio>
#include <algorithm>
#define maxn 1000005
#define maxm 2000005
#define bufsz 50000005
struct io
{
	char ibuf[ bufsz ] , * s , obuf[ bufsz ] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "yuki.in" , "r" , stdin );
		freopen( "yuki.out" , "w" , stdout );
		fread( s = ibuf , 1 ,  bufsz  , stdin );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
	}
	inline int read()
	{
		register int u = 0;
		while( * s < 48 ) s++;
		while( * s > 32 )
			u = u * 10 + * s++ - 48;
		return u;
	}
	template < class T >
	inline void print( register T u )
	{
		static int * q = a;
		if( !u ) * t++ = 48;
		else
		{
			while( u ) * q++ = u % 10 + 48 , u /= 10;
			while( q != a )
				* t++ = * --q;
		}
		* t++ = '\n';
	}
} ip;

#define read ip.read
#define print ip.print
typedef long long ll;

int n, m;
ll val[maxn];
int head[maxn], ver[maxm], nxt[maxm], tot;

inline void add(int u, int v) {
	ver[++tot] = v, nxt[tot] = head[u], head[u] = tot;
	ver[++tot] = u, nxt[tot] = head[v], head[v] = tot;
}

int fa[maxn], dep[maxn];
int mxi;

void dfs(int u, int lst) {
	fa[u] = lst, dep[u] = dep[lst] + 1;
	if(dep[mxi] < dep[u]) mxi = u;
	for(int p = head[u]; p; p = nxt[p]) {
		int v = ver[p];
		if(v != lst) dfs(v, u);
	}
}

ll q[maxn], tots;

namespace solve1 {
	ll c[maxn];
	inline void add(int x, ll v) {for(; x <= n; x += x&-x) c[x] += v;}
	inline ll query(int x) {ll s = 0; for(; x; x -= x&-x) s += c[x]; return s;}
	inline void modify(int l, int r, ll v) {
		if(l > r) std::swap(l, r);
		add(l, v), add(r+1, -v);
	}
	
	ll di[maxn];
	
	void dfs2(int u, int lst) {
		fa[u] = lst, dep[u] = dep[lst] + 1;
		for(int p = head[u]; p; p = nxt[p]) {
			int v = ver[p];
			if(v != lst) dfs(v, u);
		}
	}
	
	int work() {
		dfs2(mxi, 0);
		for(int i = 1; i <= n; ++i) di[i] = val[i] - val[fa[i]];
		for(int i = 1; i <= n; ++i) add(dep[i], di[i]);
		while(m--) {
			int op = read();
			if(op == 1) {
				int x = read(), y = read(), z = read();
				modify(dep[x], dep[y], z);
			}
			else {
				int x = read(), y = read();
				q[tots = 1] = query(dep[x]);
				for(int p = head[x]; p; p = nxt[p])
					q[++tots] = query(dep[ver[p]]);
				std::sort(q+1, q+tots+1);
				printf("%lld\n", q[y]);
			}
		}
		return 0;
	}
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) val[i] = read();
	for(int i = 1; i < n; ++i) {
		int u = read(), v = read();
		add(u, v);
	}
	dfs(1, 0);
	if(n > 1000) return solve1::work();
	while(m--) {
		int op = read();
		if(op == 1) {
			int x = read(), y = read(), z = read();
			if(dep[x] < dep[y]) std::swap(x, y);
			while(dep[x] > dep[y]) val[x] += z, x = fa[x];
			while(x != y) val[x] += z, val[y] += z, x = fa[x], y = fa[y];
			val[x] += z;
		}
		else {
			int x = read(), y = read();
			q[tots = 1] = val[x];
			for(int p = head[x]; p; p = nxt[p])
				q[++tots] = val[ver[p]];
			std::sort(q+1, q+tots+1);
			printf("%lld\n", q[y]);
		}
	}
	return 0;
}
