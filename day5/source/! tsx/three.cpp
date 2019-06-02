#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;
const double pi=acos(-1);
struct pt
{
	double x,y;
}f[1000005];
double getl(pt a,pt b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double getans(double x,double y,double z)
{
	double p=(x+y+z)/2;
	return sqrt(p*(p-x)*(p-y)*(p-z));
}
bool check(double x,double y)
{
	return fabs(x-y)<1e-9;
}
int n,t=0;
double tans[1000005];
char s[100005];
int main()
{
	scanf("%d",&n);
	if(n>100)
	{
		printf("0");
		return 0;
	}
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
	{
		double nw=2*pi*i/(double)n;
		f[i].x=cos(nw);
		f[i].y=sin(nw);
		//printf("x=%lf,y=%lf\n",f[i].x,f[i].y);
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++)
				if(s[i]=='1'||s[j]=='1'||s[k]=='1')
				{
					double x=getl(f[i],f[j]),y,z;
					y=getl(f[i],f[k]);
					z=getl(f[j],f[k]);
					tans[++t]=getans(x,y,z);
					//printf("tans=%.2lf,x=%lf,y=%lf,z=%lf\n",tans[t],x,y,z);
				}
	if(t==0)
	{
		printf("0");
		return 0;
	}
	sort(tans+1,tans+t+1);
	int ans=0,sum=1;
	double nww=tans[1];
	for(int i=2;i<=t;i++)
	{
		if(!check(tans[i],nww))
		{
			ans=ans+(sum-1)*sum/2;
			sum=1;
			nww=tans[i];
		}
		else sum++;
	}
	ans=ans+(sum-1)*sum/2;
	printf("%d",ans);
	return 0;
}
