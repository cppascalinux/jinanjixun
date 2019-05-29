#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;
const int N=20000010;
template <class nmsl> inline void read(nmsl &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}
int val[30010], lt[30010], rt[30010], color[30010];
int bl[30010];
int n, m, flag, pol, root;
int ls[N], rs[N], maxx[N], addtag[N], minn[N];
#define mid ((l+r)>>1)
inline int max(int a, int b){return a>b? a:b;}
inline int abs(int a){return a>0? a: -a;}
inline void pushdown(int k)
{
	if(!ls[k])ls[k]=++pol;
	if(!rs[k])rs[k]=++pol;
	addtag[ls[k]]+=addtag[k], addtag[rs[k]]+=addtag[k];
	maxx[ls[k]]+=addtag[k], maxx[rs[k]]+=addtag[k];
	minn[ls[k]]+=addtag[k], minn[rs[k]]+=addtag[k];
	addtag[k]=0;
}
inline void modify(int &k, int l, int r, int x, int y, int v)
{
	if(!k)k=++pol;
	if(l>=x && r<=y)
	{
		addtag[k]+=v;
		maxx[k]+=v;
		minn[k]+=v;
		return;
	}
	pushdown(k);
	if(x<=mid)modify(ls[k], l, mid, x, y, v);
	if(y>mid)modify(rs[k], mid+1, r, x, y, v);
	maxx[k]=max(maxx[ls[k]], maxx[rs[k]]);
	minn[k]=min(minn[ls[k]], minn[rs[k]]);
	return;
}
inline void dfs(int now)
{
	if(flag)return;
	if(now==m+1)
	{
		if((abs(maxx[root])<=1) && abs(minn[root])<=1)
		{
			flag=1;
			for(R int i=1; i<=m; i++)printf("%d ", color[i]);
		}
		return;
	}
	if(bl[now]==-1)
	{
		if(now&1)
		{
			color[now]=1;
			modify(root, 1, n, lt[now], rt[now], 1);
			dfs(now+1);
			if(flag)return;
			color[now]=0;
			modify(root, 1, n, lt[now], rt[now], -2);
			dfs(now+1);
			modify(root, 1, n, lt[now], rt[now], 1);
		}
		else 
		{
			color[now]=0;
			modify(root, 1, n, lt[now], rt[now], -1);
			dfs(now+1);
			if(flag)return;
			modify(root, 1, n, lt[now], rt[now], 2);
			color[now]=1;
			modify(root, 1, n, lt[now], rt[now], -1);
			dfs(now+1);
		}
	}
	if(bl[now]==1)
	{
		color[now]=1;
		modify(root, 1, n, lt[now], rt[now], 1);
		dfs(now+1);
		modify(root, 1, n, lt[now], rt[now], -1);
	}
	if(bl[now]==0)
	{
		color[now]=0;
		modify(root, 1, n, lt[now], rt[now], -1);
		dfs(now+1);
		modify(root, 1, n, lt[now], rt[now], 1);
	}
}
int main()
{
	freopen("wait.in", "r", stdin);
	freopen("wait.out", "w", stdout);
	read(m), read(n);
	for(R int i=1; i<=m; i++)read(lt[i]), read(rt[i]), read(bl[i]);
	dfs(1);
	if(!flag)printf("-1");
	return 0;
}
