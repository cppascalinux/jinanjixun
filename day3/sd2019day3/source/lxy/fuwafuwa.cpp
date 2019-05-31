#include <iostream>
#include <cstdio>
#include <cctype>
#define il inline
#define re register
#define gc getchar
#define LL long long
using namespace std;
template <typename T>
void rd(T &s)
{
	s = 0;
	bool p = 0;
	char ch;
	while (ch = gc(), p |= ch == '-', !isdigit(ch));
	while (s = s * 10 + ch - '0', ch = gc(), isdigit(ch));
	s *= (p ? -1 : 1);
}
template <typename T, typename... Args>
void rd(T &s, Args&... args)
{
	rd(s);
	rd(args...);
}
LL a, b, m, n;
int main()
{
	freopen("fuwafuwa.in", "r", stdin);
	freopen("fuwafuwa.out", "w", stdout);
	int T;
	rd(T);
	while (T--)
	{
		re LL l, r, dep = -1, lst;
		rd(a, b, m, n);
		a %= m;
		b %= m;
		lst = (a + n % m * b) % m;
		LL x = a;
		l = 0, r = m;
		for (re LL i = 1; i <= n; ++i)
		{
			x = x + b;
			if (x >= m)
				x -= m;
			if (x >= l && x < r)
			{
				++dep;
				if (lst >= x)
					l = x;
				else
					r = x;				
			}
		}
		printf("%lld\n", dep);
	}
	return 0;
}

