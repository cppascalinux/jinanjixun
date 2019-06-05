#include <cstdio>
#include <algorithm>
#define maxn 1000005
#define bufsz 50000005
struct io
{
	char ibuf[ bufsz ] , * s , obuf[ bufsz ] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "shinku.in" , "r" , stdin );
		freopen( "shinku.out" , "w" , stdout );
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
int a[maxn];
int b[maxn];
int ans[15];

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read();
	while(m--) {
		int l = read(), r = read();
		for(int i = l; i <= r; ++i) b[i] = a[i];
		std::sort(b+l, b+r+1);
		r = std::unique(b+l, b+r+1)-b-1;
		int now = 1;
		for(int i = 1; i <= 10; ++i) ans[i] = 0;
		for(int i = l+1; i <= r; ++i) {
			if(b[i] != b[i-1]+1) {
				if(now <= 10) ++ans[now];
				now = 1;
			}
			else ++now;
		}
		if(now <= 10) ++ans[now];
		for(int i = 1; i <= 10; ++i) printf("%d", ans[i]%10);
		puts("");
	}
	return 0;
}
