#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int n,m,k,a[500001],T,s1,s0,B;

int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	
	scanf("%d",&T);
	for(;T;T--)
	{
		memset(a,0,sizeof(a));
		scanf("%d%d",&n,&m);
		s1=s0=0; B=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			a[i]%=2;
			if(a[i]) s1++;
			else s0++;
		}
		if(n==1)
		{
			if(s1) printf("B\n");
			else printf("A\n");
			continue;
		}
		if((n+m+1)&1)
		{
			printf("A\n");
			continue;
		}
		if(n==2 && s1)
		{
			printf("B\n");
			continue;
		}
		
		if(m)
		{
			int d=0;
			for(int i=1;i<=n;i+=2)if(!a[i])
			{
				if(!d) i-=1, d=1;
				else d=-1;
			}
			if(d==-1)	printf("A\n");
			else printf("B\n");
			continue;
		}
		
		for(int i=1;i<=n;i+=2) if(!a[i])
		{
			printf("A\n"); B=1;
			break;
		}
		if(!B) printf("B\n");
	}
}
