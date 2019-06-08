#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
#define R register
#define ll long long
using namespace std;
const int N = 1 << 18 + 1;

int len, q, s[N], x[N], y[N << 1], sa[N], buc[N];

inline void read(int &x) {
	x = 0;
	char ch = getchar(), w = 0;
	while (!isdigit(ch))
		w = (ch == '-'), ch = getchar();
	while (isdigit(ch))
		x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	x = w ? -x : x;
	return;
}

inline int lowbit(int x) {
	return x & -x;
}

inline void pre() {
	int n = 1 << len, m = 3;
	for (R int i = 1; i < n; ++i)
		s[i] = s[i - lowbit(i)] ^ 1;
	for (R int i = n; i; --i)
		s[i] = s[i - 1] + 1;
	for (R int i = 1; i <= n; ++i)
		++buc[x[i] = s[i]];
	buc[2] += buc[1];
	for (R int i = 1; i <= n; ++i)
		sa[buc[x[i]]--] = i;
	for (R int l = 1; l <= n; l <<= 1) {
		int num = 0;
		for (R int i = n - l + 1; i <= n; ++i)
			y[++num] = i;
		for (R int i = 1; i <= n; ++i)
			if (sa[i] > l)
				y[++num] = sa[i] - l;
		for (R int i = 1; i <= m; ++i)
			buc[i] = 0;
		for (R int i = 1; i <= n; ++i)
			++buc[x[i]];
		for (R int i = 2; i <= m; ++i)
			buc[i] += buc[i - 1];
		for (R int i = n; i; --i)
			sa[buc[x[y[i]]]--] = y[i], y[i] = x[i];
		x[sa[1]] = num = 1;
		for (R int i = 2; i <= n; ++i)
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + l] == y[sa[i - 1] + l]) ? num : ++num;
		if (num == n) break;
		m = num;
	}
	return;
}

int main() {
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
	int x;
	read(len), read(q), pre();
	while (q--)
		read(x), printf("%d ", sa[x] - 1);
	return 0;
}
