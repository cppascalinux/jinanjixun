#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
struct Point
{
	ll x,y;
	int id,w;
	Point(ll xx=0,ll yy=0){x=xx,y=yy;}
	Point operator+(Point p){return Point(x+p.x,y+p.y);}
	Point operator-(Point p){return Point(x-p.x,y-p.y);}
	Point operator*(ll d){return Point(x*d,y*d);}
	Point operator/(ll d){return Point(x/d,y/d);}
	ll dot(Point p){return x*p.x+y*p.y;}
	ll det(Point p){return x*p.y-y*p.x;}
	ll abs2(){return x*x+y*y;}
	double abs(){return sqrt(abs2());}
	double alpha(){return atan2(y,x);}
}p[55],b[55];
bool cmp(Point a,Point b)
{
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
bool cmp2(Point a,Point b)
{
	if(a.x==0)return 1;
	return a.alpha()>b.alpha();
}
int n,f[55][55][55],w[55][55][55],ans[55];
int main()
{
	freopen("but.in","r",stdin);
	freopen("but.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)ans[i]=1000000000;
	for(int i=1;i<=n;i++)scanf("%lld%lld%d",&p[i].x,&p[i].y,&p[i].w);
	sort(p+1,p+n+1,cmp);
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
	for(int k=j+1;k<=n;k++)
	{
		for(int l=1;l<=n;l++)
		{
			if(l==i||l==j||l==k)continue;
			ll v1=(p[i]-p[l]).det(p[j]-p[l]);
			ll v2=(p[j]-p[l]).det(p[k]-p[l]);
			ll v3=(p[k]-p[l]).det(p[i]-p[l]);
			if((v1>0&&v2>0&&v3>0)||(v1<0&&v2<0&&v3<0))w[i][j][k]+=p[l].w;
		}
		w[i][k][j]=w[j][i][k]=w[j][k][i]=w[k][i][j]=w[k][j][i]=w[i][j][k];
	}
	for(int st=1;st<=n;st++)
	{
		for(int i=1;i<=n-st+1;i++)
		  for(int last=st;last<=n;last++)
		    for(int now=last+1;now<=n;now++)
		      f[i][last][now]=1000000000;
		for(int i=st;i<=n;i++)
		{
			b[i]=p[i]-p[st];
			b[i].id=i;
			b[i].w=p[i].w;
		}
		sort(b+st+1,b+n+1,cmp2);
		for(int i=st+1;i<=n;i++)
		  f[2][st][i]=b[st].w+b[i].w;
		for(int i=2;i<=n-st;i++)
		{
			for(int last=st;last<=n;last++)
			for(int now=last+1;now<=n;now++)
			{
				if(f[i][last][now]==1000000000)continue;
				for(int nxt=now+1;nxt<=n;nxt++)
				{
					if((b[nxt]-b[now]).det(b[now]-b[last])>0)
					  f[i+1][now][nxt]=min(f[i+1][now][nxt],f[i][last][now]+b[nxt].w+w[b[st].id][b[now].id][b[nxt].id]);
				}
			}
		}
		for(int i=3;i<=n-st+1;i++)
		  for(int last=st;last<=n;last++)
		    for(int now=last+1;now<=n;now++)
		      ans[i]=min(ans[i],f[i][last][now]);
	}
	for(int i=3;i<=n;i++)
	{
		if(ans[i]==1000000000)printf("-1 ");
		else printf("%d ",ans[i]);
	}
	printf("\n");
	return 0;
}
