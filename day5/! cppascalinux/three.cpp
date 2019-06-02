#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define db double
#define eps 1e-10
#define pi 3.1415926535897932384626433832795
using namespace std;
struct pt
{
	db x,y;
	pt(){}
	pt(db a,db b){x=a,y=b;}
	pt operator +(pt p){return pt(x+p.x,y+p.y);}
	pt operator -(pt p){return pt(x-p.x,y-p.y);}
	db operator ^(pt p){return x*p.y-y*p.x;}
};
int n;
char s[100009];
pt p[100009];
int sgn(db x)
{
	return x>eps?1:(x<-eps?-1:0);
}
void solve()
{
	int ans=0;
	for(int i=1;i<=n;i++)
		p[i]=pt(cos(2*pi/n*(i-1)),sin(2*pi/n*(i-1)));
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++)
				if(i!=j&&j!=k&&i!=k&&(s[i]||s[j]||s[k]))
				{
					db s1=fabs((p[i]^p[j])+(p[j]^p[k])+(p[k]^p[i]));
					for(int i2=1;i2<=n;i2++)
						for(int j2=i2+1;j2<=n;j2++)
							for(int k2=j2+1;k2<=n;k2++)
								if(!(i2==i&&j2==j&&k2==k)&&(s[i2]||s[j2]||s[k2]))
								{
									db s2=fabs((p[i]^p[j])+(p[j]^p[k])+(p[k]^p[i]));
									if(sgn(s1-s2)==0)
										ans++;
								}
				}
	printf("%d",ans/2);
}
int main()
{
	freopen("three.in","r",stdin);
	freopen("three.out","w",stdout);
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;i++)
		s[i]-='0';
	if(n<=10)
		solve();
	else
		printf("0");
	return 0;
}