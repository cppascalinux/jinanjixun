#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
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
	while (ch = getchar(), p |= ch == '-', ch < '0' || ch > '9')
		;
	while (s = s * 10 + ch - '0', ch = getchar(), ch >= '0' && ch <= '9')
		;
	return s * (p ? -1 : 1);
}
struct io
{
	char obuf[ 22 << 20 ] , * t;
	int a[40];
	io() : t( obuf )
	{
		freopen( "save.in" , "r" , stdin );
		freopen( "save.out" , "w" , stdout );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
	}
	template < class T >
	inline void print( register T u )
	{
		static int * q = a;
		if( !u ) * t++ = 48;
		else
		{
			while( u ) * q++ = u % 10 + 48 , u /= 10;
			while( q != a )
				* t++ = * --q;
		}
		* t++ = '\n';
	}
} ip;
#define print ip.print
const int MAXN = 200000;
int a[MAXN];
int n, m;
namespace subtask1
{
	void modify(int l, int r, int x)
	{
		for (int i = l; i <= r; ++i)
			a[i] ^= x;
	}
	void modify_sort(int l, int r)
	{
		sort(a + l, a + r + 1);
	}
	void query(int l, int r)
	{
		int ans = 0;
		for (int i = l; i <= r; ++i)
			ans ^= a[i];
		print(ans);
	}
	void solve()
	{
		int opt, l, r, x;
		for (int i = 1; i <= m; ++i)
		{
			opt = read(), l = read(), r = read();
			if (opt == 1)
			{
				x = read();
				modify(l, r, x);
			}
			else if (opt == 2)
				modify_sort(l, r);
			else
				query(l, r);
		}
	}
}
namespace subtask2
{
	struct node
	{
		node *ls, *rs;
		int val, tag, l, r;
		node () {ls = rs = NULL; val = tag = l = r = 0;}
	}st[MAXN << 2];
	int cnt = 0;
	#define new_node() (&(st[cnt++]))
	#define mid(l, r) (((l) + (r)) >> 1)
	node *rt;
	il void update(node *o)
	{
		o->val = o->ls->val ^ o->rs->val;
	}
	il void push_down(node *o)
	{
		int x = o->tag;
		o->tag = 0;
		if (o->ls)
		{
			((o->ls->r - o->ls->l + 1) & 1) ? (o->ls->val ^= x) : 0;
			o->ls->tag ^= x;
		}
		if (o->rs)
		{
			((o->rs->r - o->rs->l + 1) & 1) ? (o->rs->val ^= x) : 0;
			o->rs->tag ^= x;
		}
	}
	void build(node *&o, int l, int r)
	{
		o = new_node();
		o->l = l, o->r = r;
		o->tag = 0;
		if (l == r)
		{
			o->val = a[l];
			return;
		}
		build(o->ls, l, mid(l, r));
		build(o->rs, mid(l, r) + 1, r);
		update(o);
	}
	void modify(node *o, int l, int r, int x)
	{
		if (o->l == l && o->r == r)
		{
			((o->r - o->l + 1) & 1) ? o->val ^= x : 0;
			o->tag ^= x;
			return;
		}
		push_down(o);
		int MID = mid(o->l, o->r);
		if (r <= MID)
			modify(o->ls, l, r, x);
		else if (l > MID)
			modify(o->rs, l, r, x);
		else
			modify(o->ls, l, MID, x), modify(o->rs, MID + 1, r, x);
		update(o);
	}
	void modify_sort(node *o, int l, int r)
	{
		// I don't know how to do this;
		// qwq
	}
	int query(node *o, int l, int r)
	{
		if (o->l == l && o->r == r)
			return o->val;
		push_down(o);
		int MID = mid(o->l, o->r);
		if (r <= MID)
			return query(o->ls, l, r);
		else if (l > MID)
			return query(o->rs, l, r);
		else
			return query(o->ls, l, MID) ^ query(o->rs, MID + 1, r);		
	}
	void solve()
	{
		build(rt, 1, n);
		int opt, l, r, x;
		for (int i = 1; i <= m; ++i)
		{
			opt = read(), l = read(), r = read();
			if (opt == 1)
			{
				x = read();
				modify(rt, l, r, x);
			}
			else if (opt == 2)
				modify_sort(rt, l, r);
			else
				print(query(rt, l, r));			
		}
	}
}
int main()
{
	n = read(), m = read();	
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	if (n * 1ll * m <= 100000000ll)
		subtask1::solve();
	else
		subtask2::solve();
	return 0;
}



