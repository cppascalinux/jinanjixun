#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const double PI=acos(-1.0);
const int mod=998244353;
struct P
{
	double x,y;
	int col;
	P(){col=0;}
}a[10003];
int n,ans;
double s[1000003];
bool check(int x,int y,int z,int xx,int yy,int zz)
{
	if(x==xx&&y==yy&&z==zz) return 0;
	if((a[x].col||a[y].col||a[z].col)&&(a[xx].col||a[yy].col||a[zz].col)) return 1;
	return 0;
}
double S(int x,int y,int z)
{
	double res=a[x].x*a[y].y-a[x].y*a[y].x+a[y].x*a[z].y-a[y].y*a[z].x+a[z].x*a[x].y-a[z].y*a[x].x;
	return fabs(res/2);
}
int main()
{
	freopen("three.in","r",stdin);
	freopen("three.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%1d",&a[i].col);
	for(int i=1;i<=n;i++)
	{
		a[i].x=cos(PI*(i-1<<1)/n);
		a[i].y=sin(PI*(i-1<<1)/n);
	}
	if(n<=10)
	{
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				for(int k=j+1;k<=n;k++)
					for(int l=1;l<=n;l++)
						for(int o=l+1;o<=n;o++)
							for(int p=o+1;p<=n;p++)
								if(check(i,j,k,l,o,p)&&fabs(S(i,j,k)-S(l,o,p))<1e-12)
									ans++;
		printf("%d",ans/2);
	}
	else if(n<=100)
	{
		int cnt=0;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				for(int k=j+1;k<=n;k++)
					if(a[i].col||a[j].col||a[k].col) s[++cnt]=S(i,j,k);
		sort(s+1,s+cnt+1);
		int lst=1;
		for(int i=2;i<=cnt+1;i++)
			if(fabs(s[i]-s[lst])>1e-12)
			{
				ans=(ans+(long long)(i-lst)*(i-lst-1)/2)%mod;
				lst=i;
			}
		printf("%d",ans);
	}
	else puts("0");
	fclose(stdin);
	fclose(stdout);
	return 0;						
}
