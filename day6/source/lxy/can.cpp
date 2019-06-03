#include <iostream>
#include <cstdio>
#include <cctype>
#include <cmath>
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
int ans = 0;
int n, m, k;
char ch[10][10];
bool vis[10][10];
int belong[10][10];
int sze[2];
void nxt(int i, int j);
void dfs(int i, int j);
il void nxt(re int i, re int j)
{
	if (j == m)
		dfs(i + 1, 1);
	else
		dfs(i, j + 1);
}
il bool check_sze()
{
	return abs(sze[1] - sze[0]) <= k;
}
const int mx[] = {-1, 0, 1, 0}, my[] = {0, 1, 0, -1};
void travel(re int i, re int j, re int w)
{
	if (belong[i][j] == w && !vis[i][j])
		vis[i][j] = 1;
	else
		return;
	for (re int k = 0; k < 4; ++k)
		travel(i + mx[k], j + my[k], w);
}
il bool check_each()
{
	for (re int i = 1; i <= n; ++i)
		for (re int j = 1; j <= m; ++j)
			vis[i][j] = 0;
	for (re int i = 1; i <= n; ++i)
		for (re int j = 1; j <= m; ++j)
		{
			if (belong[i][j] == 1)
			{
				travel(i, j, 1);
				goto qwq1;
			}
		}
	qwq1:
	for (re int i = 1; i <= n; ++i)
		for (re int j = 1; j <= m; ++j)
		{
			if (belong[i][j] == 2)
			{
				travel(i, j, 2);
				goto qwq2;
			}
		}
	qwq2:
	for (re int i = 1; i <= n; ++i)
		for (re int j = 1; j <= m; ++j)
			if (!vis[i][j])
				return false;
	return true;
}
il bool is_same(re int i, re int j)
{
	return belong[i][j] == belong[i - 1][j] && belong[i][j] == belong[i][j - 1] && belong[i][j] == belong[i - 1][j - 1];
}
il bool check_equ()
{
	for (re int i = 1; i <= n; ++i)
		for (re int j = 1; j <= m; ++j)
			if (is_same(i, j))
				return false;
	return true;
}
il int check()
{
	if (check_sze() && check_each() && check_equ())
		return 1;
	else
		return 0;
}
void dfs(re int i, re int j)
{
	if (i == n + 1)
	{
		ans += check();
		return;
	}
	if (abs(sze[1] - sze[0]) - (n - i) * m - (m - j + 1) > k)
		return;
	if (ch[i][j] == 'A')
	{
		belong[i][j] = 1;
		++sze[1];
		if (!is_same(i, j))
			nxt(i, j);
		--sze[1];
	}
	else if (ch[i][j] == 'B')
	{
		belong[i][j] = 2;
		++sze[0];
		if (!is_same(i, j))
			nxt(i, j);
		--sze[0];
	}
	else
	{
		++sze[1];
		belong[i][j] = 1;
		if (!is_same(i, j))
			nxt(i, j);
		--sze[1];
		++sze[0];
		belong[i][j] = 2;
		if (!is_same(i, j))
			nxt(i, j);
		--sze[0];
	}
}
int main()
{
#ifdef DEBUG
	cout << "This is stdin&stdout\n";
#else
	freopen("can.in", "r", stdin);
	freopen("can.out", "w", stdout);
#endif
	rd(n), rd(m), rd(k);
	for (re int i = 1; i <= n; ++i)
		for (re int j = 1; j <= m; ++j)
			while (!isalpha(ch[i][j] = gc()));
	dfs(1, 1);
	printf("%d", ans);
	return 0;
}
