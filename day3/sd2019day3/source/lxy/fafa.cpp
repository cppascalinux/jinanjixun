#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
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
const int INF = 0x3fffffff;
int main()
{
	freopen("fafa.in", "r", stdin);
	freopen("fafa.out", "w", stdout);
	int n, k, now, ans = 0;
	int dp[12][2];
	int a[12];
	rd(n, k);
	for (re int i = 1; i <= n; ++i)
		a[i] = i;
	do
	{
		now = 1;
		for (re int i = 1; i <= n; ++i)
			dp[i][1] = -INF, dp[i][0] = 1;
		for (re int i = 2; i <= n; ++i)
			for (re int j = 1; j < i; ++j)
			{
				if (a[j] < a[i])
					now = max(now, dp[i][0] = max(dp[i][0], dp[j][1] + 1));
				else
					now = max(now, dp[i][1] = max(dp[i][1], dp[j][0] + 1));
				if (now > k)
					goto qwq;
			}
		qwq:if (now == k)
			++ans;
	} while (next_permutation(a + 1, a + 1 + n));
	printf("%d\n", ans);
	return 0;
}

