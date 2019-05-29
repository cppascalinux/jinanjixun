#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
struct Data
{
	int x;
	int p;
	bool lorr;
}a[60005];
int n,m,l[30005],r[30005],t[30005],d[60005];
bool cmp(Data a,Data b)
{
	return a.x<b.x;
}
int main()
{
	freopen("wait.in","r",stdin);
	freopen("wait.out","w",stdout);
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&l[i],&r[i],&t[i]);
		a[i*2-1].x=l[i];
		a[i*2-1].p=i;
		a[i*2-1].lorr=0;
		a[i*2].x=r[i]+1;
		a[i*2].p=i;
		a[i*2].lorr=1;
	}
	sort(a+1,a+2*m+1,cmp);
	int now=0;
	for(int i=1;i<=2*m;i++)
	{
		if(a[i].x!=a[i-1].x)now++;
		if(a[i].lorr==0)l[a[i].p]=now;
		else r[a[i].p]=now-1;
	}
	n=now;
	for(int s=0;s<(1<<m);s++)
	{
		bool flag=1;
		for(int i=1;i<=n;i++)d[i]=0;
		for(int i=0;i<m;i++)
		{
			if((1<<i)&s)
			{
				if(t[i+1]==0)
				{
					flag=0;
					break;
				}
				for(int j=l[i+1];j<=r[i+1];j++)d[j]++;
			}
			else
			{
				if(t[i+1]==1)
				{
					flag=0;
					break;
				}
				for(int j=l[i+1];j<=r[i+1];j++)d[j]--;
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(abs(d[i])>1)
			{
				flag=0;
				break;
			}
		}
		if(flag)
		{
			for(int i=0;i<m;i++)printf("%d ",(bool)((1<<i)&s));
			printf("\n");
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}
