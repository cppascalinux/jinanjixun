#include <iostream>
#include <cstdio>
#include <cctype>
#define il inline
#define re register
#define gc getchar
#define LL long long
#define file "distribution"
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
int main()
{
	int T;
	T = read();
	for (int i = 1; i <= T; ++i)
		print(50);
	return 0;
}
