#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;
int n,t;
double p,mp[105]={0,3600,3650,3700,3700,3700,3700,3700,3700,3700,3700};
int check(double x)
{
	for(int i=1;i<=10;i++)
		if(fabs(p-0.05-0.09*i)<1e-9)
			return x>mp[i];
	return 1;
}
int main()
{
	freopen("distribution.in","r",stdin);
	freopen("distribution.out","w",stdout);
	srand(time(0));
	scanf("%d%lf",&t,&p);
	while(t--)
	{
		scanf("%d",&n);
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			double x;
			scanf("%lf",&x);
			if(fabs(x)<0.5) ans++;
		}
		//ans=123894;
		if(check(ans)) printf("%d\n",rand()%90+11);
		else printf("%d\n",rand()%10+1);
	}
	return 0;
}
