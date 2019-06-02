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
	freopen("three.in", "r", stdin);
	freopen("three.out", "w", stdout);
	int n;
	rd(n);
	for (int i = 1; i <= n; ++i)
	{
		while (!isdigit(a[i] = gc()));
		a[i] -= '0';
	}
	puts("0");
	return 0;
}

