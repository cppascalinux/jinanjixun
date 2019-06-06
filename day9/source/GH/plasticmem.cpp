#include<cstdio>
#include<iostream>
#define maxn 100010
#define re register
using namespace std;
inline int read()
{
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int a[maxn],n,m,flag[maxn],l[maxn],r[maxn];
int main()
{
	freopen("plasticmem.in","r",stdin);
	freopen("plasticmem.out","w",stdout);
	n=read(),m=read();
	for(re int i=1;i<=n;++i) a[i]=read();
	for(re int i=1;i<=m;++i)
	{
		flag[i]=read(),l[i]=read(),r[i]=read();
	}
	for(re int i=1;i<=m;++i)
	{
		if(flag[i]==1)
		{
			for(re int j=l[i];j<=r[i];++j)
			{
				a[j]=0;
			}
		}
		else if(flag[i]==2)
		{
			for(re int j=l[i];j<=r[i];++j)
			{
				a[j]=1;
			}
		}
		else if(flag[i]==3)
		{
			for(re int j=l[i];j<=r[i]-1;++j)
			{
				a[j]|=a[j+1];
			}
		}
		else if(flag[i]==4)
		{
			for(re int j=r[i];j>=l[i]+1;--j)
			{
				a[j]|=a[j-1];
			}
		}
		else if(flag[i]==5)
		{
			for(re int j=l[i];j<=r[i]-1;++j)
			{
				a[j]&=a[j+1];
			}
		}
		else if(flag[i]==6)
		{
			for(re int j=r[i];j>=l[i]+1;--j)
			{
				a[j]&=a[j-1];
			}
		}
		else
		{
			long long tmp=0;
			for(re int j=l[i];j<=r[i];++j)
			{
				tmp+=a[j];
			}
			printf("%lld\n",tmp);
		}
	}
	return 0;
}
