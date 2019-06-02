#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define N 123000
#define ll long long
#define double long double
struct Point{
	double x,y;
	Point (double _x=0,double _y=0) : x(_x),y(_y) {}
	Point operator + (const Point &B) const {return Point(x+B.x,y+B.y);}
	Point operator / (const double &B) const {return Point(x/B,y/B);}
	double operator ^ (const Point &B) const {return x*B.y-y*B.x;}
	Point operator - (const Point &B) const {return Point(x-B.x,y-B.y);}
}P[N];
double dis(Point A,Point B) {return sqrtl((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));}
char s[N];double a[1203000];const double pi=3.14159265358979323l,eps=1e-5;
int main()
{
	freopen("three.in","r",stdin);
	freopen("three.out","w",stdout);
	int n,c=0;bool Z=false;ll ans=0;
	scanf("%d%s",&n,s+1);
	for (int i=1;i<=n;++i) Z|=s[i]=='1';
	for (int i=1;i<=n;++i) P[i]=Point(cosl(2*pi*i/n),sinl(2*pi*i/n));
	if (!Z) return !printf("0");
	for (int i=1;i<=n;++i)
		for (int j=i+1;j<=n;++j)
			for (int k=j+1;k<=n;++k)
			{
				if (s[i]!='1'&&s[j]!='1'&&s[k]!='1') continue;
				a[++c]=((P[k]-P[i])^(P[j]-P[i]))/2;
			}
	sort(a+1,a+1+c);
	for (int i=1,j=1;i<=c;i=j+1)
	{
		j=i;
		while(j<=c&&fabsl(a[j+1]-a[j])<eps) ++j;
		ans+=1ll*(j-i+1)*(j-i)/2;
	}
	printf("%lld",ans);
	return 0;
}

//by qlwpc
