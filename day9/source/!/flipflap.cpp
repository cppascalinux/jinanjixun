#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
#define lson o<<1
#define rson o<<1|1
#define mid (l+r)/2
using namespace std;
int n,m;
ll sum[400005];
void pushup(int o)
{
	sum[o]=sum[lson]+sum[rson];
}
void add(int o,int l,int r,int from,int to,ll v)
{
	if(l==r)
	{
		sum[o]+=v;
		return;
	}
	if(from<=mid)add(lson,l,mid,from,to,v);
	if(to>mid)add(rson,mid+1,r,from,to,v);
	pushup(o);
}
int query(int o,int l,int r,int from,int to,ll v)
{
	if(l==r)
	{
		if(sum[o]<=v)return 1;
		return 0;
	}
	int ans=0;
	if(l>=from&&r<=to&&sum[o]<=v)ans=1;
	if(from<=mid)ans+=query(lson,l,mid,from,to,v);
	if(to>mid)ans+=query(rson,mid+1,r,from,to,v);
	return ans;
}
int main()
{
	freopen("flipflap.in","r",stdin);
	freopen("flipflap.out","w",stdout);
	scanf("%d%d",&n,&m);
	while(m--)
	{
		int opt,l,r,v;
		scanf("%d%d%d%d",&opt,&l,&r,&v);
		if(opt==1)add(1,1,n,l,r,v);
		else printf("%d\n",query(1,1,n,l,r,v));
	}
	return 0;
}
