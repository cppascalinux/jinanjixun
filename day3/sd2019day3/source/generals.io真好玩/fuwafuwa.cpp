#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int a,b,m;
		long long n;
		scanf("%d %d %d %lld",&a,&b,&m,&n);
		a%=m;
		b%=m;
		int l=-1,r=m;
		int nowdep=0;
		int o=((long long)a+(long long)n%m*b)%m;
		int cur=a;
		for(int i=1;i<n;i++)
		{
			cur+=b;
			if(cur>=m)cur-=m;
			if(cur>=l&&cur<r){
				nowdep++;
				if(cur<=o)l=cur;
				else r=cur;
			}
		}
		printf("%d\n",nowdep);
	}
	return 0;
}
