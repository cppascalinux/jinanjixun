#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,a[1000005];
int sum[2000005],lazy[2000005];
void pushup(int x)
{
	sum[x]=(sum[x*2]^sum[x*2+1]);
}
void col(int x,int l,int r,int v)
{
	lazy[x]^=v;
	if((r-l+1)%2) sum[x]^=v;
}
void pushdown(int x,int l,int r)
{
	if(lazy[x])
	{
		int mid=(l+r)/2;
		col(x*2,l,mid,lazy[x]);
		col(x*2+1,mid+1,r,lazy[x]);
		lazy[x]=0;
	}
}
void build(int x,int l,int r)
{
	if(l==r)
	{
		sum[x]=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(x*2,l,mid);
	build(x*2+1,mid+1,r);
	pushup(x);
}
void modify(int x,int l,int r,int ql,int qr,int v)
{
	if(l>qr||r<ql) return;
	if(ql<=l&&r<=qr)
	{
		col(x,l,r,v);
		return;
	}
	pushdown(x,l,r);
	int mid=(l+r)/2;
	modify(x*2,l,mid,ql,qr,v);
	modify(x*2+1,mid+1,r,ql,qr,v);
	pushup(x);
}
int query(int x,int l,int r,int ql,int qr)
{
	if(l>qr||r<ql) return 0;
	if(ql<=l&&r<=qr) return sum[x];
	int mid=(l+r)/2,q1,q2;
	pushdown(x,l,r);
	q1=query(x*2,l,mid,ql,qr);
	q2=query(x*2+1,mid+1,r,ql,qr);
	return q1^q2;
}
int main()
{
	freopen("save.in","r",stdin);
	freopen("save.out","w",stdout);
	scanf("%d%d",&n,&m);
	if(n<=10000&&m<=10000)
	{
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=m;i++)
		{
			//printf("i=%d,m=%d\n",i,m);
			int op,l,r,x;
			scanf("%d%d%d",&op,&l,&r);
			if(op==1)
			{
				scanf("%d",&x);
				for(int j=l;j<=r;j++)
					a[j]^=x;
			}
			if(op==2)
			{
				sort(a+l,a+r+1);
			}
			if(op==3)
			{
				int ans=0;
				for(int j=l;j<=r;j++)
					ans^=a[j];
				printf("%d\n",ans);
			}
		}
		return 0;
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		int op,l,r,x;
		scanf("%d%d%d",&op,&l,&r);
		if(op==1) 
		{
			scanf("%d",&x);
			modify(1,1,n,l,r,x);
		}
		if(op==3) printf("%d\n",query(1,1,n,l,r));
	}
	return 0;
}
