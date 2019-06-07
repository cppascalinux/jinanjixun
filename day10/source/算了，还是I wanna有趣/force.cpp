#include <iostream>
#include <cstdio>
#include <cctype>
#define il inline
#define re register
#define gc getchar
#define LL long long
#define file "guess"
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
int read()
{
    re bool p = 0;
    re char ch;
    re int s = 0;
    while (ch = gc(), p |= ch == '-', !isdigit(ch))
        ;
    while (s = s * 10 + ch - '0', isdigit(ch = gc()))
        ;
    return s * (p ? -1 : 1);
}
struct io
{
    char obuf[22 << 20], *t;
    int a[40];
    io() : t(obuf)
    {
        freopen(file".in", "r", stdin);
        freopen("force.out", "w", stdout);
    }
    ~io()
    {
        fwrite(obuf, 1, t - obuf, stdout);
    }
    template <class T>
    inline void print(register T u)
    {
        static int *q = a;
        if (u < 0)
            *t++ = '-', u = -u;
        if (!u)
            *t++ = 48;
        else
        {
            while (u)
                *q++ = u % 10 + 48, u /= 10;
            while (q != a)
                *t++ = *--q;
        }
        *t++ = '\n';
    }
} ip;
#define print ip.print
const int MAXN = 10005;
int a[MAXN], n;
int dp[MAXN][MAXN];
int g[MAXN];
int main()
{
	char ch;
	while (!isdigit(ch = gc()));
	while (a[++n] = ch - '0', dp[n][n] = a[n], g[n] = 1, isdigit(ch = gc()));
	for (int len = 1; len < n; ++len)
		for (int l = 1; l + len <= n; ++l)
		{
			dp[l][l + len] = 0x3fffffff;
			for (int m = l; m <= l + len; ++m)
			{
				int temp = max(dp[l][m - 1], dp[m + 1][l + len]) + a[m];
				if (temp < dp[l][l + len])	
					dp[l][l + len] = temp;
			}
		}
//	for (int i = 1; i <= n; ++i)
//	{
//		for (int j = i; j <= n; ++j)
//			printf("%d\t", dp[i][j]);
//		printf("\n");
//	}
	print(dp[1][n]);
	return 0;
}

