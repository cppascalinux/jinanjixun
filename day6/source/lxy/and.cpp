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
const int MOD = 1000000007;
const int MAXN = 11;
LL dp[MAXN][1 << 22];
int a[MAXN], b[MAXN];
int n, m;
int ans = 0;
bool check(int u)
{
	return (((a[u - 1] & b[u - 1]) <= (a[u] & b[u])) && ((a[u - 1] | b[u - 1]) >= (a[u] | b[u])));
}
int solve(int u, int k)
{
	if (u == 1)
		return 1;
	if (~dp[u][k])
		return dp[u][k];
	a[u] = k;
	LL &ans = dp[u][k];
	ans = 0;
	for (int i = 0; i < (1 << m); ++i)
	{
		a[u - 1] = i;
		if (check(u))
			ans += solve(u - 1, i);
		ans %= MOD;
	}
	return ans;
}
int main()
{
#ifdef DEBUG
	cout << "This is stdin&stdout\n";
#else
	freopen("and.in", "r", stdin);
	freopen("and.out", "w", stdout);
#endif
	rd(n);
	rd(m);
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < (1 << m); ++j)
			dp[i][j] = -1;
	for (int i = 1; i <= n; ++i)
		rd(b[i]);
	LL ans = 0;
	for (int i = 0; i < (1 << m); ++i)
		ans += solve(n, i),
		ans %= MOD;
	printf("%lld", ans);
	return 0;
}

/*
8 30
123456789
998244353
991608907
177744201
19491001
20190603
23333333
100000007

728096396
*/
