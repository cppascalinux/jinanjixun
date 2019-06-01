#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
#include <map>
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
int two[32];
il void init()
{
	two[0] = 1;
	for (re int i = 1; i <= 30; ++i)
		two[i] = two[i - 1] << 1;
}
struct node
{
	int Bit[32];
	int p;
	int ls, rs, l, r;
	node()
	{
		ls = 0, rs = 0, l = 0, r = 0, p = 0;
		for (int i = 30; i >= 0; --i)
			Bit[i] = 0;
	}
	il void insert(re int x)
	{
		for (re int i = 30; i >= 0; --i)
		{
			if (x & two[i])
			{
				if (!Bit[i])
				{
					Bit[i] = x;
					++p;
					return;
				}
				else
					x ^= Bit[i];
			}
		}
	}
	il void modify(node &y)
	{
		for (re int i = 30; i >= 0; --i)
			if (y.Bit[i])
				insert(y.Bit[i]);
	}
}tree[1600000];
int id[1000000];
int cnt = 0;
int rt;
#define new_node() (++cnt)
void build(re int l, re int r, int& o)
{
	o = new_node();
	tree[o].l = l, tree[o].r = r;
	if (l == r)
	{
		id[l] = o;
		return;
	}
	build(l, (l + r) >> 1, tree[o].ls),
	build(((l + r) >> 1) + 1, r, tree[o].rs);
}
void modify(re int l, re int r, re int x, re int o)
{
	if (tree[o].l == l && tree[o].r == r)
	{
		tree[o].insert(x);
		return;
	}
	re int mid = (tree[o].l + tree[o].r) >> 1;
	if (r <= mid)
		modify(l, r, x, tree[o].ls);
	else
		if (l > mid)
			modify(l, r, x, tree[o].rs);
		else
			modify(l, mid, x, tree[o].ls),
			modify(mid + 1, r , x, tree[o].rs);
}
void travel(re int o)
{
	if (tree[o].l == tree[o].r)
		return;
	tree[tree[o].ls].modify(tree[o]);
	travel(tree[o].ls);
	tree[tree[o].rs].modify(tree[o]);
	travel(tree[o].rs);
}
map<int, int> MAP;
int main()
{
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	init();
	int x;
	int m, q, opt;
	rd(m), rd(q);
	build(1, q, rt);
	for (re int i = 1; i <= q; ++i)
	{
		rd(opt), rd(x);
		if (opt == 1)
			MAP[x] = i;
		else
		{
			map<int, int>::iterator it = MAP.find(x);
			modify(it->second, i - 1, x, rt);
			MAP.erase(it);
		}
	}
    map<int, int>::iterator IT;
    for (IT = MAP.begin(); IT != MAP.end(); ++IT)
        modify(IT->second, q, IT->first, rt);
    travel(rt);
    for (re int i = 1; i <= q; ++i)
        printf("%d\n", 1 << tree[id[i]].p);
    return 0;
}

