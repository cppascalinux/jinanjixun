#include<cstdio>
#include<iostream>
#include<cstring>
#define maxn 100010
#define re register
#define mid ((l+r)>>1)
#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r
#define ll long long
using namespace std;
int n,m,flag[maxn],sl[maxn],sr[maxn],sa[maxn];
ll a[maxn<<2],laz[maxn<<2];
inline int read()
{
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int res,siz[maxn<<2];

void push_down(int rt,int len)
{
	laz[rt<<1]+=laz[rt],laz[rt<<1|1]+=laz[rt];
	a[rt<<1]+=laz[rt]*(len-(len>>1));
	a[rt<<1|1]+=(laz[rt]*(len>>1));
	laz[rt]=0;
}
void update(int rt,int l,int r,int L,int R,int k)
{
	if(L<=l&&r<=R)
	{
		laz[rt]+=k;
		a[rt]+=k*(r-l+1);
	}
	else
	{
		if(laz[rt]) push_down(rt,r-l+1);
		if(L<=mid) update(lson,L,R,k);
		if(R>mid) update(rson,L,R,k);
		a[rt]=a[rt<<1]+a[rt<<1|1];
	}
}
void query(int rt,int l,int r,int L,int R,int k)
{
	if(L<=l&&r<=R)
	{
		if(a[rt]<=k) {res+=siz[rt];return;}
		if(l==r) return;
	}
		if(laz[rt]) push_down(rt,r-l+1);
		if(L<=mid) query(lson,L,mid,k);
		if(R>mid) query(rson,mid+1,R,k);
}
void dfs(int rt,int l,int r)
{
	if(l==r){siz[rt]=1;return ;}
	dfs(lson);
	dfs(rson);
	siz[rt]+=siz[rt<<1];
	siz[rt]+=siz[rt<<1|1];
	siz[rt]++;
}
int main()
{
	freopen("flipflap.in","r",stdin);
	freopen("flipflap.out","w",stdout);
	n=read(),m=read();
	for(re int i=1;i<=m;++i)
	{
		flag[i]=read(),sl[i]=read(),sr[i]=read(),sa[i]=read();
	}
	dfs(1,1,n);
	for(re int i=1;i<=m;++i)
	{
		if(flag[i]==1)
		{
			update(1,1,n,sl[i],sr[i],sa[i]);
		}
		else
		{
			res=0;
			query(1,1,n,sl[i],sr[i],sa[i]);
			printf("%d\n",res);
		}	
	}
		
	return 0;
}
