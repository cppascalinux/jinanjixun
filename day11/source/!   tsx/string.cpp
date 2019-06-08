#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,q,c[10000005],x[10000005],y[10000005],sa[10000005];
void getsa()
{
	for(int i=1;i<=m;i++)
		c[i]=0;
	for(int i=1;i<=n;i++)
		c[x[i]]++;
	for(int i=2;i<=m;i++)
		c[i]+=c[i-1];
	for(int i=1;i<=n;i++)
		sa[c[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int cnt=0;
		for(int i=n-k+1;i<=n;i++)
			y[++cnt]=i;
		for(int i=1;i<=n;i++)
			if(sa[i]>k) y[++cnt]=sa[i]-k;
		for(int i=1;i<=m;i++)
			c[i]=0;
		for(int i=1;i<=n;i++)
			c[x[i]]++;
		for(int i=2;i<=m;i++)
			c[i]+=c[i-1];
		for(int i=n;i>0;i--)
			sa[c[x[y[i]]]--]=y[i],y[i]=0;
		for(int i=1;i<=n;i++)
			swap(x[i],y[i]);
		cnt=1;
		x[sa[1]]=1;
		for(int i=2;i<=n;i++)
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&(sa[i]+k>n?-1:y[sa[i]+k])==
			(sa[i-1]+k>n?-1:y[sa[i-1]+k]))?cnt:++cnt;
		if(cnt==n) break;
		m=cnt;
	}
}
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	scanf("%d%d",&n,&q);
	n=(1<<n);
	x[1]=0;
	m=2;
	for(int i=2;i<=n;i++)
	{
		x[i]=x[(i-1)/2+1]+(i-1)%2;
		x[i]%=2;
	}
	for(int i=1;i<=n;i++)
		x[i]++;
	getsa();
	for(int i=1;i<=q;i++)
	{
		int tq;
		scanf("%d",&tq);
		printf("%d ",sa[tq]-1);
	}
	//printf("\n");
	//for(int i=1;i<=n;i++)
	///	printf("%d ",x[i]);
	return 0;
}
