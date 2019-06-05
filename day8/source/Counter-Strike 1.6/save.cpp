#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;
const int N=100100;
template <class nmsl> inline void read(nmsl &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}

int n, m, sum[N*4], tag[N*4];
int rubbish[N];
#define mid ((l+r)>>1)
#define lc (k<<1)
#define rc ((k<<1)+1)
inline void build(int k, int l, int r)
{
	if(l==r)
	{
		sum[k]=rubbish[l];
		return;
	}
	build(lc, l, mid);
	build(rc, mid+1, r);
	sum[k]=sum[lc] xor sum[rc];
	return;
}
inline void pushdown(int k, int l, int r)
{
	
	if((mid-l+1)&1)sum[lc]^=tag[k];
	if((r-mid)&1)sum[rc]^=tag[k];
	tag[lc]^=tag[k], tag[rc]^=tag[k];
	tag[k]=0;
}
inline void modify(int k, int l, int r, int x, int y, int v)
{
	if(l>=x && r<=y)
	{
		if((r-l+1)&1)sum[k]^=v;
		tag[k]^=v;
		return;
	}
	pushdown(k, l, r);
	if(x<=mid)modify(lc, l, mid, x, y, v);
	if(y>mid)modify(rc, mid+1, r, x, y, v);
	sum[k]=sum[lc] xor sum[rc];
	return;
}
inline void Modify(int k, int l, int r, int pos, int v)
{
	if(l==r)
	{
		sum[k]=v;
		return;
	}
	pushdown(k, l, r);
	if(pos<=mid)Modify(lc, l, mid, pos, v);
	else Modify(rc, mid+1, r, pos, v);
	sum[k]=sum[lc] xor sum[rc];
	return;
}
inline int query(int k, int l, int r, int x, int y)
{
	if(l>=x && r<=y)return sum[k];
	int res=0;
	pushdown(k, l, r);
	if(x<=mid)res^=query(lc, l, mid, x, y);
	if(y>mid)res^=query(rc, mid+1, r, x, y);
	return res;
}
inline void File()
{
	freopen("save.in", "r", stdin);
	freopen("save.out", "w", stdout);
}
int main()
{
	File();
	read(n), read(m);
	for(R int i=1; i<=n; i++)read(rubbish[i]);
	build(1, 1, n);
	for(R int o=1, qa, qb, qc, qd; o<=m; o++)
	{
		read(qa), read(qb), read(qc);
		if(qa==1)
		{
			read(qd);
			modify(1, 1, n, qb, qc, qd);
		}
		if(qa==2)
		{
			int num=0;
			for(R int i=qb; i<=qc; i++)rubbish[++num]=query(1, 1, n, i, i);
			sort(rubbish+1, rubbish+1+num);
			num=0;
			for(R int i=qb; i<=qc; i++)Modify(1, 1, n, i, rubbish[++num]);
		}
		if(qa==3)printf("%d\n", query(1, 1, n, qb, qc));
	}
	return 0;
}
