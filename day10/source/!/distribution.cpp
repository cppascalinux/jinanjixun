#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cstdlib>
using namespace std;
int t,n,top,num[10005];
double p,res[10005],ans[105][10005];
int main()
{
	freopen("distribution.in","r",stdin);
	freopen("distribution.out","w",stdout);
	srand((unsigned int)time(0));
	scanf("%d%lf",&t,&p);
	for(n=1;n<=100;n++)
	{
		int T=10;
		for(int o=1;o<=T;o++)
		{
			top=0;
			for(int i=1;i<=1000;i++)
			{
				double ans=0;
				for(int j=1;j<=n;j++)
				{
					int x=rand()%100+1;
					if(x<=p*100+0.5)ans+=1;
				}
				ans+=(rand()%101-50)/100.0;
				ans-=n*p;
				ans/=sqrt(n*p*(1-p));
				res[++top]=ans;
			}
			sort(res+1,res+top+1);
			for(int i=1;i<=top;i++)ans[n][i]+=res[i];
		}
		for(int i=1;i<=1000;i++)ans[n][i]/=t;
	}
//	for(int i=1;i<=1000;i++)
//	{
//		for(int j=1;j<=100;j++)printf("%lf ",ans[j][i]);
//		printf("\n");
//	}
	while(t--)
	{
		int answer;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%lf",&res[i]);
		sort(res+1,res+n+1);
//		for(int i=1;i<=n;i++)printf("%lf ",res[i]);
//		printf("\n");
		double minans=1e100;
		int minp=0;
		for(int i=1;i<=100;i++)
		{
			double x=0;
			for(int j=1;j<=n;j++)
			  x+=(ans[i][(j-1)/10+1]-res[j])*(ans[i][(j-1)/10+1]-res[j])*(ans[i][(j-1)/10+1]-res[j])*(ans[i][(j-1)/10+1]-res[j])*(ans[i][(j-1)/10+1]-res[j])*(ans[i][(j-1)/10+1]-res[j])*fabs(ans[i][(j-1)/10+1]-res[j]);
			if(x<minans)
			{
				minans=x;
				minp=i;
			}
//			printf("%lf ",x);
		}
//		printf("\n");
		printf("%d\n",minp);
	}
	return 0;
}
