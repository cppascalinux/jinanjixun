#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;
#define MAXN 55
#define ll long long

int read()
{
	int ret=0,neg=1;
	char c=getchar();
	while (c<'0' || c>'9'){
		if (c=='-') neg=-1;
		c=getchar();
	}
	while (c>='0' && c<='9'){
		ret=ret*10+c-'0';
		c=getchar();
	}
	return ret*neg;
}

struct Vec{
	int x,y;
};
ll operator*(Vec a,Vec b)
{
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}

struct Point{
	int x,y,val;
};
Vec operator -(Point a,Point b)
{
	return (Vec){a.x-b.x,a.y-b.y};
}

int n;
Point p[MAXN];
bool cmp(Point x,Point y)
{
	return x.x<y.x;
}
int tri[MAXN][MAXN];

bool in(Point x,Point y,Point z,Point q)
{
	bool ret=1;
	if (((q-x)*(y-x)>0)!=((z-x)*(q-x)>0)) ret=0;
	if (((q-y)*(x-y)>0)!=((z-y)*(q-y)>0)) ret=0;
	if (((q-z)*(y-z)>0)!=((x-z)*(q-z)>0)) ret=0;
	return ret;
}

int ans[MAXN];
int dp[MAXN][MAXN][MAXN];


signed main()
{
	freopen("but.in","r",stdin);
	freopen("but.out","w",stdout);
	memset(ans,0x3f,sizeof(ans));
	n=read();
	for (int i=1;i<=n;i++) p[i].x=read(),p[i].y=read(),p[i].val=read();
	sort(p+1,p+n+1,cmp);
	for (int i=1;i<=n;i++){
		memset(tri,0,sizeof(tri));
		for (int j=i+1;j<=n;j++) for (int k=j+1;k<=n;k++){
			for (int l=i+1;l<=n;l++){
				if (l==j || l==k || l==i) continue;
				if (in(p[i],p[j],p[k],p[l])) tri[j][k]+=p[l].val,tri[k][j]+=p[l].val;
			}
		}
		memset(dp,0x3f,sizeof(dp));
		for (int j=i+1;j<=n;j++) dp[2][i][j]=p[i].val+p[j].val;
		for (int j=2;j<=n;j++){
			for (int k=i;k<=n;k++)
				for (int l=i+1;l<=n;l++){
					int now=dp[j][k][l];
					if (l==k || now==0x3f3f3f3f || (p[l]-p[k])*(p[i]-p[l])<0)continue;
					ans[j]=min(ans[j],now+tri[l][i]);
					for (int neww=i+1;neww<=n;neww++){
						if((p[l]-p[k])*(p[neww]-p[l])<0)continue;
						dp[j+1][l][neww]=min(dp[j+1][l][neww],now+tri[l][neww]+p[neww].val);
					}
				}
		}
	}
	for (int i=3;i<=n;i++) printf("%d ",ans[i]==0x3f3f3f3f ? -1 : ans[i]);
}
