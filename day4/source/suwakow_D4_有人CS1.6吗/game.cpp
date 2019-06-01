#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
#define R register
#define ll long long
using namespace std;
const int N = 110000;

int t, n, m, a[N];
char win[3] = "AB";

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

int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	read(t);
	while (t--) {
		read(n), read(m);
		for (R int i = 1; i <= n; ++i)
			read(a[i]), a[i] &= 1;
		if (n == 1) {
			printf("%c\n", win[a[1]]);
			continue;
		}
		if ((n ^ m ^ 1) & 1) {
			printf("A\n");
			continue;
		}
		int k = (n - m) >> 1, j = 0;
		for (R int i = 1; i <= n; ++i)
			a[i] ? ++j : (k -= (j + 1) >> 1, j = 0);
		k -= (j + 1) >> 1;
		printf("%c\n", win[k < 0]);
	}
	return 0;
}
