#include <bits/stdc++.h>
using namespace std;
struct io
{
    static const int LEN = 1 << 8 | 1;
    char buf[LEN];
    inline char getchar()
    {
        static char *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, LEN, stdin)), s == t ? -1 : *s++;
    }
    template <class t>
    inline io &operator>>(t &x)
    {
        char c;
        bool b;
        for (c = getchar(), b = 0; !isdigit(c); c = getchar())
        {
            if (c == -1)
                return *this;
            b |= c == '-';
        }
        for (x = 0; isdigit(c); c = getchar())
            x = x * 10 + c - '0';
        b && (x = -x);
        return *this;
    }
    template <class t>
    inline io &operator<<(t x)
    {
        if (!x)
            putchar('0');
        bool b = x < 0;
        b && (x = -x);
        b &&putchar('-');
        t ano = 0;
        while (x)
            ano = ano * 10 + x % 10, x /= 10;
        while (ano)
            putchar(ano % 10 + '0'), ano /= 10;
        return *this;
    }
    inline io &operator<<(char c)
    {
        putchar(c);
        return (*this);
    }
} f;
const int mod = 998244353;
int n, m, l, w;
bool cans[61][61][61];
int val[61][61][61];
int cantsum[61][61][61];
int valsum[61][61][61];
void extgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return;
    }
    extgcd(b, a % b, y, x);
    y -= a / b * x;
}
int main()
{
    freopen("dream.in","r",stdin);
    freopen("dream.out","w",stdout);
    f >> n >> m >> l >> w;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = 1; k <= l; k++)
            {
                f >> cans[i][j][k];
                cantsum[i][j][k] = cantsum[i - 1][j][k] + cantsum[i][j - 1][k] + cantsum[i][j][k - 1] - cantsum[i - 1][j - 1][k] - cantsum[i - 1][j][k - 1] - cantsum[i][j - 1][k - 1] + cantsum[i - 1][j - 1][k - 1] + (1 - cans[i][j][k]);
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = 1; k <= l; k++)
            {
                f >> val[i][j][k];
                val[i][j][k] %= mod;
                valsum[i][j][k] = (((valsum[i - 1][j][k] + valsum[i][j - 1][k]) % mod + valsum[i][j][k - 1]) % mod - valsum[i - 1][j - 1][k] - valsum[i - 1][j][k - 1] - valsum[i][j - 1][k - 1] + valsum[i - 1][j - 1][k - 1] + val[i][j][k]) % mod;
            }
        }
    }
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = 1; k <= l; k++)
            {
                for (int i1 = 1; i1 <= i; i1++)
                {
                    for (int j1 = 1; j1 <= j; j1++)
                    {
                        for (int k1 = 1; k1 <= k; k1++)
                        {
                            if (cantsum[i][j][k] - cantsum[i1 - 1][j][k] - cantsum[i][j1 - 1][k] - cantsum[i][j][k1 - 1] + cantsum[i1 - 1][j1 - 1][k] + cantsum[i1 - 1][j][k1 - 1] + cantsum[i][j1 - 1][k1 - 1] - cantsum[i1 - 1][j1 - 1][k1 - 1] == 0)
                            {
                                sum = ((sum + valsum[i][j][k]) % mod - valsum[i1 - 1][j][k] - valsum[i][j1 - 1][k] - valsum[i][j][k1 - 1] + valsum[i1 - 1][j1 - 1][k] + valsum[i1 - 1][j][k1 - 1] + valsum[i][j1 - 1][k1 - 1] - valsum[i1 - 1][j1 - 1][k1 - 1]) % mod;
                            }
                        }
                    }
                }
            }
        }
    }
    int fm = 0, tmp = 0;
    extgcd(n * (n + 1) * m * (m + 1) * l * (l + 1) / 8, mod, fm, tmp);
    f << (((long long)sum * fm) % mod + mod) % mod << '\n';
}
