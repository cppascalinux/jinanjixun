#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int t;
ll a,b,m,n;
int main()
{
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
	scanf("%d",&t);
	while(t--)
	{
		scanf("%lld%lld%lld%lld",&a,&b,&m,&n);
		a%=m,b%=m;
		int now=a,lst=(a+n%m*b%m)%m,dep=0;
		int l=0,r=m-1;
		for(int i=1;i<n;i++)
		{
			now+=b;
			if(now>=m) now-=m;
			if(now>=l&&now<=r)
			{
				dep++;
				if(now>=lst) r=now;
				else l=now;
			}
		}
		printf("%d\n",dep);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
