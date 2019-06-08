#include <iostream>
#include <cstdio>
#include <cctype>
#define il inline
#define re register
#define gc getchar
#define LL long long
#define file "determinant"
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
        freopen(file".out", "w", stdout);
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
const int MOD = 1000000007;
const int maxn = 200;
int a[maxn][maxn];
int tot = 0;
int qpow(int a, int b)
{
	int ans = 1;
	for (; b; b >>= 1, a = a * 1ll * a % MOD)
		if (b & 1)
			ans = ans * 1ll * a % MOD;
	return ans;
}
void gauss_jordan(int n)
{
    for (int i = 0; i < n; ++i)
    {
        int idx = i; 
        for (int j = i + 1; j < n; ++j)
            if (a[j][i] > a[idx][i])
                idx = j;
        if (idx != i)
        {
        	++tot;
            for (int j = i; j <= n; ++j)
                swap(a[i][j], a[idx][j]);
		}
        for (int j = 0; j < n; ++j)
        {
            if (i != j)
            {
            	int temp = qpow(a[i][i] % MOD, MOD - 2) * 1ll * a[j][i] % MOD;
                for (int k = n; k >= i; --k) 
                    a[j][k] -= a[i][k] * 1ll * temp % MOD,
                    a[j][k] %= MOD,
                    a[j][k] = (a[j][k] < 0 ? a[j][k] + MOD : a[j][k]);
			}
		}
    }
}
struct node
{
	int x1, x2, y1, y2;
}ma[100005];
int main()
{
	int T, n;
	T = read();
	while (T--)
	{
		int s = 0;
		tot = 0;
		n = read();
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				a[i][j] = 0;
		for (int i = 1; i <= n; ++i)
		{
			ma[i].x1 = read(), ma[i].x2 = read(), ma[i].y1 = read(), ma[i].y2 = read();
			s = (ma[i].y2 - ma[i].y1 + 1) * 1ll * (ma[i].x2 - ma[i].x1 + 1) % MOD;
			s = qpow(s, MOD - 2) % MOD;
			for (int j = ma[i].x1; j <= ma[i].x2; ++j)
				for (int k = ma[i].y1; k <= ma[i].y2; ++k)
					a[j - 1][k - 1] = (a[j - 1][k - 1] + s) % MOD;
		}
		gauss_jordan(n);
		int ans = ((tot & 1) ? MOD - 1 : 1);
		for (int i = 0; i < n; ++i)
			ans = ans * 1ll * a[i][i] % MOD;
		print(ans);
	}
	return 0;
}
