#include <iostream>
#include <queue>
#include <cstdio>
#include <cctype>
#define re register
#define gc getchar
#define LL long long
#define pq priority_queue
using namespace std;
typedef pair<int, int> P;
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
const int N = 65;
const int MOD = 998244353;
int a1[N][N][N], a2[N][N][N];
LL s1[N][N][N], s2[N][N][N], s3[N][N][N], s4[N][N][N];
int n, m, l, w;
int qpow(int a, int n)
{
	int ans = 1;
	for (; n; n >>= 1, a = (a * 1ll * a) % MOD)
		if (n & 1)
			ans = ans * 1ll * a % MOD;
	return ans;
}
void init()
{
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			for (int k = 1; k <= l; ++k)
			{
				rd(a1[i][j][k]);
				a1[i][j][k] = !a1[i][j][k];
				s1[i][j][k] = s1[i][j][k - 1] + s1[i][j - 1][k] + s1[i - 1][j][k] - s1[i - 1][j - 1][k] - s1[i - 1][j][k - 1] - s1[i][j - 1][k - 1] + s1[i - 1][j - 1][k - 1] + a1[i][j][k];
			}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			for (int k = 1; k <= l; ++k)
			{
				rd(a2[i][j][k]);
				s2[i][j][k] = s2[i][j][k - 1] + s2[i][j - 1][k] + s2[i - 1][j][k] - s2[i - 1][j - 1][k] - s2[i - 1][j][k - 1] - s2[i][j - 1][k - 1] + s2[i - 1][j - 1][k - 1] + a2[i][j][k];
			}
}
int query_1(int il, int ir, int jl, int jr, int kl, int kr)
{
	return s1[ir][jr][kr] - s1[il - 1][jr][kr] - s1[ir][jl - 1][kr] - s1[ir][jr][kl - 1] + s1[il - 1][jl - 1][kr] + s1[il - 1][jr][kl - 1] + s1[ir][jl - 1][kl - 1] - s1[il - 1][jl - 1][kl - 1];
}
LL query_2(int il, int ir, int jl, int jr, int kl, int kr)
{
	return (s2[ir][jr][kr] - s2[il - 1][jr][kr] - s2[ir][jl - 1][kr] - s2[ir][jr][kl - 1] + s2[il - 1][jl - 1][kr] + s2[il - 1][jr][kl - 1] + s2[ir][jl - 1][kl - 1] - s2[il - 1][jl - 1][kl - 1]) % MOD; 
}
void run1()
{
	LL ans = 0;
	for (int il = 1; il <= n; ++il)
	for (int ir = il; ir <= n; ++ir)
	for (int jl = 1; jl <= m; ++jl)
	for (int jr = jl; jr <= m; ++jr)
	for (int kl = 1; kl <= l; ++kl)
	for (int kr = kl; kr <= l; ++kr)
		if (query_1(il, ir, jl, jr, kl, kr) == 0)
			ans = (ans + query_2(il, ir, jl, jr, kl, kr)) % MOD;
		else
			break;
	LL p = 1;
	p = p * n * m * l * 1ll * (n + 1) * (m + 1) * (l + 1) / 8;
	ans = (ans % MOD * qpow(p, MOD - 2)) % MOD;
	if (ans < 0)
		ans += MOD;
	printf("%lld", ans);
}
void add(int il, int ir, int jl, int jr, int kl, int kr)
{
	++s3[il][jl][kl];
	--s3[ir + 1][jl][kl];
	--s3[il][jr + 1][kl];
	--s3[il][jl][kr + 1];
	++s3[ir + 1][jr + 1][kl];
	++s3[ir + 1][jl][kr + 1];
	++s3[il][jr + 1][kr + 1];
	--s3[ir + 1][jr + 1][kr + 1];
}
void run2()
{
	LL ans = 0;
	LL s, c = 0;
	s = 1ll * n * m * l * 1ll * (n + 1) * (m + 1) * (l + 1) * 1ll / 8;
	for (int il = 1; il <= n; ++il)
	for (int ir = il; ir <= n; ++ir)
	for (int jl = 1; jl <= m; ++jl)
	for (int jr = jl; jr <= m; ++jr)
	for (int kl = 1; kl <= l; ++kl)
	for (int kr = kl; kr <= l; ++kr)
		if (query_1(il, ir, jl, jr, kl, kr) == 0)
		{
			++c;
			add(il, ir, jl, jr, kl, kr);
		}
		else
			break;
	c %= MOD;
	LL p = qpow(qpow(s, w), MOD - 2) % MOD;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			for (int k = 1; k <= l; ++k)
			{
				s4[i][j][k] = s4[i][j][k - 1] + s4[i][j - 1][k] + s4[i - 1][j][k] - s4[i - 1][j - 1][k] - s4[i - 1][j][k - 1] - s4[i][j - 1][k - 1] + s4[i - 1][j - 1][k - 1] + s3[i][j][k];
				s4[i][j][k] %= MOD;
				ans = (ans + a2[i][j][k] * 1ll * (qpow(c, w) - qpow(c - s4[i][j][k], w)) % MOD * 1ll * p % MOD) % MOD;
			}
	if (ans < 0)
		ans += MOD;
	printf("%lld", ans);
}
int main()
{
	freopen("dream.in", "r", stdin);
	freopen("dream.out", "w", stdout);
	rd(n, m, l, w);
	init();
	if (w == 1)
		run1();
	else
		run2();
	return 0;
}
