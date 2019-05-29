#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define il inline
#define re register
#define gc getchar
#define LL long long
using namespace std;
int n, m;
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
const int N = 500000;
vector<int> v;
bool p = 0;
int ql[N], qr[N], w[N];
int a[N];
bool check()
{
	int k = 0;
	for (int i = 1; i <= n; ++i)
	{
		k += a[i];
		if (k < -1 || k > 1)
			return false;
	}
	return true;
}
void print()
{
	for (int i = 1; i <= m; ++i)
		printf("%d ", w[i]);
}
void dfs(int u)
{
	if (p)
		return;
	if (u == m + 1)
	{
		if (check())
		{
			print();
			p = 1;
		}
		return;
	}
	if (w[u] != -1)
	{
		dfs(u + 1);
		return;
	}
	w[u] = 1;
	a[ql[u]] += 1;
	a[qr[u] + 1] -= 1;
	dfs(u + 1);
	w[u] = 0;
	a[ql[u]] += -2;
	a[qr[u] + 1] -= -2;
	dfs(u + 1);
	a[ql[u]] += 1;
	a[qr[u] + 1] -= 1;
	w[u] = -1;
}
int main()
{
	freopen("wait.in", "r", stdin);
	freopen("wait.out", "w", stdout);
	rd(m, n);
	for (int i = 1; i <= m; ++i)
	{
		rd(ql[i], qr[i], w[i]);
		v.push_back(ql[i]);
		v.push_back(qr[i]);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	for (int i = 1; i <= m; ++i)
	{
		ql[i] = lower_bound(v.begin(), v.end(), ql[i]) - v.begin() + 1;
		qr[i] = lower_bound(v.begin(), v.end(), qr[i]) - v.begin() + 1;
		if (w[i] != -1)
		{
			a[ql[i]] += (w[i] == 0 ? -1 : 1);
			a[qr[i] + 1] -= (w[i] == 0 ? -1 : 1);
		}
	}
	n = v.size();
	dfs(1);
	if (!p)
		printf("-1");
	return 0;
}
