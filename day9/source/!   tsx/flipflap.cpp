#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
int n,m;
ll sum[1000005];
void pushup(int x)
{
	sum[x]=sum[x*2]+sum[x*2+1];
}
void modify(int x,int l,int r,int ql,int qr,int v)
{
	if(l>qr||r<ql) return;
	if(l==r)
	{
		sum[x]+=v;
		return;
	}
	int mid=(l+r)/2;
	modify(x*2,l,mid,ql,qr,v);
	modify(x*2+1,mid+1,r,ql,qr,v);
	pushup(x);
}
int query(int x,int l,int r,int ql,int qr,int v)
{
	if(l>qr||r<ql) return 0;
	int ans=0;
	if(sum[x]<=v) ans++;
	if(l==r) return ans;
	int mid=(l+r)/2;
	ans=ans+query(x*2,l,mid,ql,qr,v);
	ans=ans+query(x*2+1,mid+1,r,ql,qr,v);
	return ans;
}
int main()
{
	freopen("flipflap.in","r",stdin);
	freopen("flipflap.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int op,l,r,v;
		scanf("%d%d%d%d",&op,&l,&r,&v);
		if(op==1) modify(1,1,n,l,r,v);
		else printf("%d\n",query(1,1,n,l,r,v));
	}
	return 0;
}
