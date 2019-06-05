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
		freopen( "end.in" , "r" , stdin );
		freopen( "end.out" , "w" , stdout );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
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
#define print ip.print
const int MOD = 1000000007;
int ans = 0;
char ch;
int a[1000];
int n, k, sum = 0, len = 0;
il bool check()
{
	re bool p = 1;
	for (re int l = 0; l <= len; ++l)
	{
		re bool t = 1;
		for (re int i = 1; i <= n; ++i)
			t ^= (a[i] >> l) & 1;
		if (!t)
		{
			p = 0;
			break;
		}
	}
	return p;
}
void dfs(re int u, re int l)
{
	if (u == n + 1)
	{
		if (check())
			++ans;
		return;
	}
	for (re int i = l + 1; i < sum; ++i)
	{
		a[u] = i;
		dfs(u + 1, i);
	}
}
int main()
{
	n = read(), k = read();
	while (!isdigit(ch = gc()));
	while (sum = (sum << 1) + ch - '0', ++len, isdigit(ch = gc()))
		;
	if (n == 3)
	{
		for (int i = 0; i < sum; ++i)
		for (int j = i + 1; j < sum; ++j)
		for (int k = j + 1; k < sum; ++k)
		{
			bool p = 1;
			for (int l = 0; l <= len; ++l)
				if ((((i >> l) & 1) + ((j >> l) & 1) + ((k >> l) & 1)) & 1)
				{
					p = 0;
					break;
				}
			if (p)
				++ans;
		}	
		print(ans);
		return 0;
	}
	dfs(1, -1);
	print(ans);
	return 0;
}
