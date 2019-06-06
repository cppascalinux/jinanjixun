#include <iostream>
#include <cstdio>
#include <cctype>
#include <set>
#define il inline
#define re register
#define gc getchar
#define LL long long
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
        freopen("flipflap.in", "r", stdin);
        freopen("flipflap.out", "w", stdout);
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

struct node
{
	node *ls, *rs;
	LL val;
	int l, r;
};
node *rt;
node *new_node()
{
	return new node;
}
#define mid(l, r) (((l) + (r)) >> 1)
void build(node *&o, int l, int r)
{
	o = new_node();
	o->l = l, o->r = r, o->val = 0;
	if (l == r)
		o->ls = o->rs = NULL;
	else
		build(o->ls, l, mid(l, r)), build(o->rs, mid(l, r) + 1, r);
}
void update(node *o)
{
	o->val = o->ls->val + o->rs->val;
}
void modify(node *o, int l, int r, int a)
{
	if (o->l == o->r)
	{
		o->val += a;
		return;
	}
	int MID = mid(o->l, o->r);
	if (r <= MID)
		modify(o->ls, l, r, a);
	else if (l > MID)	
		modify(o->rs, l, r, a);
	else 
		modify(o->ls, l, MID, a), modify(o->rs, MID + 1, r, a);
	update(o);
}
int ans;
void query(node *o, int l, int r, int a)
{
	if (o->l == l && o->r == r)
	{
		if (o->val <= a)
			++ans;
		if (l == r)
			return;
	}
	int MID = mid(o->l, o->r);
	if (r <= MID)
		query(o->ls, l, r, a);
	else if (l > MID)	
		query(o->rs, l, r, a);
	else 
		query(o->ls, l, MID, a), query(o->rs, MID + 1, r, a);
	
}
int main()
{
	int n, m;
	n = read();
	m = read();
	build(rt, 1, n);
	for (int i = 1; i <= m; ++i)
	{
		int op, l, r, a;
		op = read(), l = read(), r = read(), a = read();
		if (op == 1)
			modify(rt, l, r, a);
		else
		{
			ans = 0;
			query(rt, l, r, a);
			print(ans);
		}
	}
	return 0;
}
