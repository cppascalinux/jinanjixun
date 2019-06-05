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
		freopen( "shinku.in" , "r" , stdin );
		freopen( "shinku.out" , "w" , stdout );
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

const int N = 1e6 + 60;

struct query {
	int l, r, id;
	int bl;
} q[N];

int block;

bool operator< (const query &a, const query &b) {
	return a.bl == b.bl ? ((a.bl & 1) ? a.r < b.r : a.r > b.r) : a.bl < b.bl;
}

int buff[N];
int a[N];

int ans[N][11];
int now[11];

inline void add(int x) {
	buff[x] ++;
	if(buff[x] != 1) return ;
	int l = 0, r = 0;
	per(i, x - 1, x - 11) {
		if(buff[i] == 0) break;
		++ l;
	}
	rep(i, x + 1, x + 11) {
		if(buff[i] == 0) break;
		++ r;
	}
	if(l != 0) now[l] --;
	if(r != 0) now[r] --;
	now[min(l + r + 1, 11)] ++;
	
}

inline void del(int x) {
	buff[x] --;
	if(buff[x] != 0) return ;
	int l = 0, r = 0;
	per(i, x - 1, x - 11) {
		if(buff[i] == 0) break;
		++ l;
	}
	rep(i, x + 1, x + 11) {
		if(buff[i] == 0) break;
		++ r;
	}
	now[min(l + r + 1, 11)] --;
	if(l != 0) now[l] ++;
	if(r != 0) now[r] ++;
	
}

int main() {
	int n, m; n = read(), m = read();
	block = n / sqrt(m);
	rep(i, 1, n) a[i] = read();
	rep(i, 1, m) q[i].l = read(), q[i].r = read(), q[i].id = i, q[i].bl = q[i].l / block;
	sort(q + 1, q + 1 + m);
	int l = 1, r = 0;
	rep(i, 1, m) {
		while(l > q[i].l) add(a[-- l]);
		while(l < q[i].l) del(a[l ++]);
		while(r < q[i].r) add(a[++ r]);
		while(r > q[i].r) del(a[r --]);
		memcpy(ans[q[i].id], now, sizeof(now));
	}
	rep(i, 1, m) {
		rep(j, 1, 10) {
			pc(ans[i][j] % 10 + 48);
		}
		pc('\n');
	}
	return 0;
}
