#include <set>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
#define R register
#define ll long long
#define it set<int>::iterator
using namespace std;
const int N = 110000;

int n, q, a[32], num;
set<int> s;

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

inline bool insrt(int x) {
	for (R int i = n - 1; ~i; --i)
		if (x & (1 << i)) {
			if (a[i])
				x ^= a[i];
			else
				return a[i] = x, 1;
		}
	return 0;
}

int main() {
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	int opt, x, flag;
	read(n), read(q);
	while (q--) {
		read(opt), read(x);
		if (opt == 1)
			s.insert(x), num += insrt(x);
		else {
			s.erase(x), num = 0;
			for (R int i = n - 1; ~i; --i)
				a[i] = 0;
			for (R it i = s.begin(); i != s.end(); ++i)
				num += insrt(*i);
		}
		printf("%d\n", 1 << num);
	}
	return 0;
}
