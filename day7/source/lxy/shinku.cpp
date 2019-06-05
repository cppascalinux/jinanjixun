#include <cctype>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define il inline
#define re register
#define gc getchar
#define LL long long
#define rt re int
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
int read()
{
    re bool p = 0;
    re char ch;
    re int s = 0;
    while (ch = getchar(), p |= ch == '-', ch < '0' || ch > '9')
        ;
    while (s = s * 10 + ch - '0', ch = getchar(), ch >= '0' && ch <= '9')
        ;
    return s * (p ? -1 : 1);
}
const int MAX = 2000000;
#define _isl(i) (i.x / block)
int block;
int cnt[MAX];
int a[MAX];
struct node{
    int x, y, num;
    int ans[15];
}que[MAX];
int ans[15];
bool cmp(const node& i, const node& j)
{
    return _isl(i) ^ _isl(j) ? _isl(i) < _isl(j) : (_isl(i) & 1) ? i.y < j.y : i.y > j.y; 
}
il void add(re int x)
{
	++cnt[x];
	if (cnt[x] == 1)
	{
		re int llen = 0, rlen = 0, len;
		for (re int i = x - 1; ~i && cnt[i] && llen <= 10; --i, ++llen)
			;
		for (re int i = x + 1; cnt[i] && rlen <= 10; ++i, ++rlen)
			;
		--ans[llen];
		--ans[rlen];
		len = min(llen + rlen + 1, 11);
		++ans[len];
	}
}
il void del(re int x)
{
	--cnt[x];
	if (cnt[x])
		return;
	re int llen = 0, rlen = 0, len;
	for (re int i = x - 1; ~i && cnt[i] && llen <= 10; --i, ++llen)
		;
	for (re int i = x + 1; cnt[i] && rlen <= 10; ++i, ++rlen)
		;
	++ans[llen];
	++ans[rlen];
	len = min(llen + rlen + 1, 11);
	--ans[len];
}
void get_ans(re int o)
{
	for (re int i = 1; i <= 10; ++i)
		que[o].ans[i] = ans[i];
}
void print_ans(re int o)
{
	for (re int i = 1; i <= 10; ++i)
		putchar('0' + que[o].ans[i] % 10);
	putchar('\n');
}
int main()
{
	freopen("shinku.in", "r", stdin);
	freopen("shinku.out", "w", stdout);
	re int n, m;
    n = read();
    m = read();
    for (re int i = 1; i <= n; ++i)
        a[i] = read();
    block = n / sqrt(m * 2 / 3);
    for (re int i = 1; i <= m; ++i)
        que[i].x = read(),
        que[i].y = read(),
        que[i].num = i;
    sort(que + 1, que + 1 + m, cmp);
    for (rt i = que[1].x; i <= que[1].y; ++i)
        add(a[i]);
    re int l, r;
    l = que[1].x,
    r = que[1].y;
    get_ans(que[1].num);
    for (rt i = 2; i <= m; ++i)
    {
        while (l < que[i].x) del(a[l++]);
        while (l > que[i].x) add(a[--l]);
        while (r < que[i].y) add(a[++r]);
        while (r > que[i].y) del(a[r--]);
    	get_ans(que[i].num);
    }
    for (rt i = 1; i <= m; ++i)
        print_ans(i);
	return 0;
}
// m * 2 / 3      22.93
// m * 9 / 10     23.7
// m              23.92
