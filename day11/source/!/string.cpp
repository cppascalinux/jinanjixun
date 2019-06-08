#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,k,q,sa[1000005],s[1000005];
int x[1000005],y[1000005],c[1000005];
void SA()
{
	int m=128;
	for(int i=1;i<=n;i++)c[x[i]=s[i]]++;
	for(int i=1;i<=m;i++)c[i]+=c[i-1];
	for(int i=n;i>=1;i--)sa[c[x[i]]--]=i;
	m=0;
	for(int k=1;m<n;k<<=1)
	{
		m=0;
		for(int i=n-k+1;i<=n;i++)y[++m]=i;
		for(int i=1;i<=n;i++)
		  if(sa[i]>k)y[++m]=sa[i]-k;
		for(int i=1;i<=m;i++)c[i]=0;
		for(int i=1;i<=n;i++)c[x[i]]++;
		for(int i=1;i<=m;i++)c[i]+=c[i-1];
		for(int i=n;i>=1;i--)sa[c[x[y[i]]]--]=y[i];
		for(int i=1;i<=n;i++)y[i]=x[i];
		m=x[sa[1]]=1;
		for(int i=2;i<=n;i++)
		{
			if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])x[sa[i]]=m;
			else x[sa[i]]=++m;
		}
	}
}
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	scanf("%d%d",&k,&q);
	n=1<<k;
	s[0]=0;
	for(int i=0;i*2<n;i++)
	{
		s[i*2]=s[i];
		s[i*2+1]=!s[i];
	}
	for(int i=n;i>=1;i--)s[i]=s[i-1];
	SA();
	while(q--)
	{
		int x;
		scanf("%d",&x);
		printf("%d ",sa[x]-1);
	}
	printf("\n");
	return 0;
}
