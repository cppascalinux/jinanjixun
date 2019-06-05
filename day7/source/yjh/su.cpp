#include <cstdio>
#include <algorithm>
#define maxn 100005
#define bufsz 10000005
struct io
{
	char ibuf[ bufsz ] , * s , obuf[ bufsz ] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "su.in" , "r" , stdin );
		freopen( "su.out" , "w" , stdout );
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

int n, m;
int head[maxn], ver[maxn], nxt[maxn], tot;

inline void add(int u, int v) {
	ver[++tot] = v, nxt[tot] = head[u], head[u] = tot;
	ver[++tot] = u, nxt[tot] = head[v], head[v] = tot;
}

int col[maxn];
int fa[maxn], dep[maxn];

void dfs(int u, int lst) {
	dep[u] = dep[lst] + 1;
	for(int p = head[u]; p; p = nxt[p]) {
		int v = ver[p];
		if(v != lst) dfs(v, u);
	}
}

void recol(int u, int lst, int t) {
	for(int p = head[u]; p; p = nxt[p]) {
		int v = ver[p];
		if(v != lst && col[v] == col[u]) recol(v, u, t);
	}
	col[u] = t;
}

int sum, mx, mn;

void getans(int u, int lst) {
	++sum, mx = std::max(mx, dep[u]), mn = std::min(mn, dep[u]);
	for(int p = head[u]; p; p = nxt[p]) {
		int v = ver[p];
		if(v != lst && col[v] == col[u]) getans(v, u);
	}
}

int main() {
	n = read();
	for(int i = 1; i <= n; ++i) {
		fa[i] = read();
		if(fa[i]) add(fa[i], i);
	}
	for(int i = 1; i <= n; ++i) col[i] = read();
	dfs(1, 0);
	m = read();
	while(m--) {
		int op = read();
		if(op == 1) {
			int x = read(), y = read();
			col[x] = y;
		}
		else if(op == 2) {
			int x = read(), y = read();
			recol(x, 0, y);
		}
		else {
			int x = read();
			sum = 0, mx = 0, mn = n+1;
			getans(x, 0);
			printf("%d %d %d\n", col[x], sum, mx-mn+1);
		}
	}
	return 0;
}
