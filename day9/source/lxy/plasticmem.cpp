#include <iostream>
#include <cstdio>
#include <cctype>
#define il inline
#define re register
#define gc getchar
#define LL long long
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
int read()
{
	re bool p = 0;
	re char ch;
	re int s = 0;
	while (ch = getchar(), p |= ch == '-', ch < '0' || ch > '9')
		;
	while (s = s * 10 + ch - '0', ch = getchar(), ch >= '0' && ch <= '9')
		;
	return s * (p ? -1 : 1);
}
struct io
{
	char obuf[ 22 << 20 ] , * t;
	int a[40];
	io() : t( obuf )
	{
		freopen( "plasticmem.in" , "r" , stdin );
		freopen( "plasticmem.out" , "w" , stdout );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
	}
	template < class T >
	inline void print( register T u )
	{
		static int * q = a;
        if (u < 0)
            *t++ = '-', u = -u;
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
#define print ip.print
int a[1000001];
void modify(int l, int r, int k)
{
	for (int i = l; i <= r; ++i)
		a[i] = k;
}
void modify3(int l, int r)
{
	for (int i = l; i < r; ++i)
		a[i] |= a[i + 1];
}
void modify4(int l, int r)
{
	for (int i = r; i > l; --i)
		a[i] |= a[i - 1];
}
void modify5(int l, int r)
{
	for (int i = l; i < r; ++i)
		a[i] &= a[i + 1];
}
void modify6(int l, int r)
{
	for (int i = r; i > l; --i)
		a[i] &= a[i - 1];
}
void query(int l, int r)
{
	int ans = 0;
	for (int i = l; i <= r; ++i)
		ans += a[i];
	print(ans);
}
int main()
{
	int n, m, opt, l, r;
	n = read(), m = read();
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	for (int i = 1; i <= m; ++i)
	{
		opt = read(), l = read(), r = read();
		if (opt == 1)
			modify(l, r, 0);
		else if (opt == 2)
			modify(l, r, 1);
		else if (opt == 3)
			modify3(l, r);
		else if (opt == 4)
			modify4(l, r);
		else if (opt == 5)
			modify5(l, r);
		else if (opt == 6)
			modify6(l, r);
		else
			query(l, r);
	}
	return 0;
}



