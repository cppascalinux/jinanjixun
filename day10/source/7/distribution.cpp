#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

int n,m,T,res,d;
double a[10000],p,k,sum,tot,w;

int main()
{
	freopen("distribution.in","r",stdin);
	freopen("distribution.out","w",stdout);
	scanf("%d%lf",&T,&p);
	for(;T;T--)
	{
		sum=0; tot=1000000000.0;
		scanf("%d",&m);
		for(int i=1;i<=m;i++) scanf("%lf",&a[i]);
		for(int n=1;n<=100;n++)
		{
			w=0; sum=0; int B=1;
			for(int i=1;i<=m;i++)
			{
				k=a[i];
				k*=sqrt(n*p*(1-p));
				k+=n*p;
				d=k;
				if(k-d>d+1-k) d+=1;
				if(d>n) B=0;
				sum+=fabs(1.0*d-n*p);
			}
			if(B && tot>sum) tot=sum, res=n;
		}
		printf("%d\n",res);
		
	}
}
