#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int a[101010];
int main()
{
	int T,n,i,j,k,sum=0,m,q,h;
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d",&T);
	while(1)
	{
		loop:;
		T--;
		if(T<0)
			return 0;
		scanf("%d",&n);
		scanf("%d",&m);
		for(i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			a[i]%=2;
		}
		if(n==1&&m==1&&a[1]==1)
		{
			puts("B");
			goto loop;
		}
		if(m==0&&n%2==0)
		{
			puts("A");
			goto loop;
		}
		if(m==1&&n%2==1)
		{
			puts("A");
			goto loop;
		}
		if(m==0)
		{
			for(i=1;i<=n;i+=2)
			{
				if(a[i]==0)
				{
					puts("A");
					goto loop;
				}
			}
			puts("B");
			goto loop;
		}
		for(i=1;i<=n;i+=2)
			if(a[i]==0)
				break;
		q=i-2;
		for(i=n;i>=0;i-=2)
			if(a[i]==0)
				break;
		h=i+2;
		for(i=1;i<=n;i+=2)
		{
			if(a[i]+a[i+1]==1||a[i]*a[i+1]==1)
			{
				if(q>=i-2&&h<=i+3)
				{
					puts("B");
					goto loop;
				}
			}
		}
		for(i=2;i<=n;i+=2)
		{
			if(q>=i-1&&h<=i+2)
			{
				puts("B");
				goto loop;
			}
		}
		puts("A");
	}
	return 0;
}

