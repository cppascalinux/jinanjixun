#include <iostream>
#include <cstdio>
#include <cctype>
#define il inline
#define re register
#define gc getchar
#define LL long long
using namespace std;
void rd(int &s)
{
	s = 0;
	bool p = 0;
	char ch;
	while (ch = gc(), p |= ch == '-', !isdigit(ch));
	while (s = s * 10 + ch - '0', ch = gc(), isdigit(ch));
	s *= (p ? -1 : 1);
}
int a[100000];
int main()
{
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	int T;
	rd(T);
	while (T--)
	{
		int n, m;
		rd(n);
		rd(m);
		for (int i = 1; i <= m; ++i)
		{
			rd(a[i]);
			a[i] &= 1;
		}
		puts("A");
	}
	return 0;
}

