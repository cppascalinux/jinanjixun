#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,k,p[25],now,a[1000005],from[1000005],to[1000005],num;
void solve(int l,int r)
{
	if(l==r)return;
	int mid=(l+r)/2;
	solve(l,mid);
	solve(mid+1,r);
	from[++num]=mid+1;
	to[num]=l;
	a[mid+1]=0;
	a[l]*=2;
}
void solve2(int l,int r)
{
	int x=1;
	while(x<=r-l+1)x<<=1;
	x>>=1;
	solve(l,l+x-1);
	if(l+x<r)solve2(l+x,r);
	if(l+x<=r)
	{
		while(a[l+x]<a[l])
		{
			from[++num]=1;
			to[num]=l+x;
			a[1]-=a[l+x];
			a[l+x]*=2;
		}
		from[++num]=l+x;
		to[num]=l;
		a[l+x]=0;
		a[l]*=2;
	}
}
int main()
{
	freopen("chemistry.in","r",stdin);
	freopen("chemistry.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)a[i]=1;
	int x=1;
	while(x<=k)x<<=1;
	x>>=1;
	solve(1,x);
	if(x==k)
	{
		printf("%d\n",num);
		for(int i=1;i<=num;i++)printf("%d %d\n",from[i],to[i]);
		return 0;
	}
	int m;
	if(k&1)m=k+2;
	else m=k+1;
	if(m>n)
	{
		printf("-1\n");
		return 0;
	}
	n=m;
	solve2(x+1,n);
	while(a[1]!=k)
	{
		if(a[1]<a[x+1])
		{
			from[++num]=x+1;
			to[num]=1;
			a[x+1]-=a[1];
			a[1]*=2;
		}
		else
		{
			from[++num]=1;
			to[num]=x+1;
			a[1]-=a[x+1];
			a[x+1]*=2;
		}
	}
	printf("%d\n",num);
	for(int i=1;i<=num;i++)printf("%d %d\n",from[i],to[i]);
	return 0;
}
