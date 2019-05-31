#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
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
const int N = 800;
int n, m;
char gra[N][N];
void print3(int l, int r)
{
	puts("+");
	for (int i = 1; i < l; ++i)
		putchar('0');
	for (int i = l ; i <= r; ++i)
		putchar('1');
	for (int i = r + 1; i <= m; ++i)
		putchar('0');
	puts("");
}
void solve3()
{
	int ans = 0;
	int i = 1, l;
	while (i < m)
	{
		while (gra[1][i] != '1' && i <= m)
			++i;
		if (i > m)
			break;
		l = i;
		while (gra[1][i] == '1' && i <= m)
			++i;
		--i;
		++ans;
		++i;
	}
	printf("%d\n", ans);
	i = 1;
	while (i < m)
	{
		while (gra[1][i] != '1' && i <= m)
			++i;
		if (i > m)
			break;
		l = i;
		while (gra[1][i] == '1' && i <= m)
			++i;
		--i;
		print3(l, i);
		++i;
	}
}
int main()
{
	freopen("bitbit.in", "r", stdin);
	freopen("bitbit.out", "w", stdout);
	rd(n, m);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			while (!isdigit(gra[i][j] = gc()));
//	if (n == 1)
		solve3();
	return 0;
}

