#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
#define il inline
#define re register
#define gc getchar
#define LL long long
#include <cmath>
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
		freopen( "busy.in" , "r" , stdin );
		freopen( "busy.out" , "w" , stdout );
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
vector<int> v[100005];
vector<int> temp;
typedef vector<int>::iterator it;
int n, m;
namespace subtask1
{
int lst = 0;
void merge(int from, int to)
{
	if (from == to)
		return;
	temp.clear();
	it l1 = v[from].begin(), r1 = v[from].end(), l2 = v[to].begin(), r2 = v[to].end();
	while (l1 != r1 && l2 != r2)
		if (*l1 < *l2)
			temp.push_back(*(l1++));
		else
			temp.push_back(*(l2++));
	while (l1 != r1)
		temp.push_back(*(l1++));
	while (l2 != r2)
		temp.push_back(*(l2++));
	v[from].clear();
	v[to].clear();
	for (auto x : temp)
		v[to].push_back(x);
}
void query(int x, int y)
{
	if (v[x].empty() || v[y].empty())
	{
		* ip.t++ = 'C';
		* ip.t++ = 'h';
		* ip.t++ = 't';
		* ip.t++ = 'h';
		* ip.t++ = 'o';
		* ip.t++ = 'l';
		* ip.t++ = 'l';
		* ip.t++ = 'y';
		* ip.t++ = '\n';
		lst = 0;
		return;
	}
	if (x == y)
	{
		lst = 0;
		* ip.t++ = '0';
		* ip.t++ = '\n';
		return;
	}
	int ans = 0x3fffffff;
	it l1 = v[x].begin(), r1 = v[x].end(), l2 = v[y].begin(), r2 = v[y].end();
	while (l1 != r1)
	{
		while (l2 + 1 != r2 && *(l2 + 1) < *l1)
//			ans = min(ans, *l1 - *l2),
			++l2;
		if (*l1 > *l2)
			ans = min(ans, *l1 - *l2);
		else
			ans = min(ans, *l2 - *l1);
		if (l2 + 1 != r2)
			ans = min(ans, *(l2 + 1) - *l1);
		++l1;
	}
	print(ans);
	lst = ans;
}
void solve()
{
	int opt, x, y;
	for (int i = 1; i <= m; ++i)
	{
		opt = read(), x = read(), y = read();
		x ^= lst, y ^= lst;
		if (opt == 1)
			merge(x, y);
		else
			query(x, y);
	}
}
}
int main()
{
	int x;
	n = read();
	m = read();
	for (int i = 1; i <= n; ++i)
	{
		x = read();
		v[x].push_back(i);
	}
	subtask1::solve();
	return 0;
}



