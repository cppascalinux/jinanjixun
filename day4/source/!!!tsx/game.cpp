#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
namespace abc
{
	int a[200005];
	bool tcheck(int x)
	{
		int minn=99999999,maxn=-1,minm=99999999,maxm=-1;
		int cnt=0,xx=x;
		if(a[1]==0) cnt++;
		if(a[x]==0) cnt++;
		if(cnt>1) return 0;
		for(int i=1;i<=x;i+=2)
		{
			if(a[i]==0&&a[i+1]==0) return 0;
			if(a[i]==1&&a[i+1]==0)
			{
				minm=min(minm,xx);
				maxm=max(maxm,xx);
			}
			if(a[i]==0&&a[i+1]==1)
			{
				minn=min(minn,xx);
				maxn=max(maxn,xx);
			}
			xx-=2;
		}
		if(maxn==-1||maxm==-1) return 1;
		if(cnt==1) return 0;
		if(maxn<minm) return 1;
		return 0;
	}
	bool tcheck2(int x)
	{
		for(int i=1;i<=x;i+=2)
			if(a[i]!=1) return 0;
		return 1;
	}
	int t,n,m;
	void soe()
	{
		freopen("game.in","r",stdin);
		freopen("game.out","w",stdout);
		scanf("%d",&t);
		while(t--)
		{
			scanf("%d%d",&n,&m);
			memset(a,0,sizeof(a));
			for(int i=1;i<=n;i++)
			{
				scanf("%d",&a[i]);
				a[i]%=2;
			}
			if((n+m)%2==0)
			{
				printf("A\n");
				continue;
			}
			if(n%2)
			{
				if(tcheck2(n)) printf("B\n");
				else printf("A\n");
			}
			else
			{
				if(tcheck(n)) printf("B\n");
				else printf("A\n");
			}
		}
	}
}
int main()
{
	abc::soe();
	return 0;	
}
