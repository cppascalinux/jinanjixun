#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<iostream>
using namespace std;
#define N 52
#define ll long long
#define INF 0x3f3f3f3f
struct Point{
	int x,y;
	Point (int _x=0,int _y=0) : x(_x),y(_y) {}
	Point operator - (const Point &B) const {return Point(x-B.x,y-B.y);}
	ll operator ^ (const Point &B) const {return 1ll*x*B.y-1ll*y*B.x;}
	Point operator - () const {return Point(-x,-y);}
};
struct node{
	Point a;int v;
	bool operator < (const node &B) const {return a.x==B.a.x?a.y<B.a.y:a.x<B.a.x;}
}P[N];
int V[N],f[N][N][N],ans[N],tri[N][N];
int main()
{
	freopen("but.in","r",stdin);
	freopen("but.out","w",stdout);
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;++i) scanf("%d%d%d",&P[i].a.x,&P[i].a.y,&P[i].v);
	sort(P+1,P+1+n);
	memset(ans,0x3f,sizeof(ans));
	for (int O=1;O<=n;++O)
	{
		memset(f,0x3f,sizeof(f));
		for (int i=O+1;i<=n;++i)
			for (int j=i+1;j<=n;++j)
			{
				Point A=P[i].a-P[O].a,B=P[j].a-P[O].a,C,BA=P[i].a-P[j].a,CC;ll S=0;
				if ((B^A)<0) swap(A,B),BA=-BA,CC=P[i].a;else CC=P[j].a;
				for (int k=O+1;k<=n;++k)
				{
					if (k==i||k==j) continue;
					C=P[k].a-P[O].a;
					if ((B^C)>=0&&(C^A)>=0&&((P[k].a-CC)^BA)<=0) S+=P[k].v;
				}
				tri[i][j]=tri[j][i]=S;
			}
		for (int i=O+1;i<=n;++i) f[2][O][i]=P[O].v+P[i].v;
		for (int k=2;k<=n;++k)
			for (int i=O;i<=n;++i)
				for (int j=O+1;j<=n;++j)
				{
					int x=f[k][i][j];
					if (j==i||x==INF||((P[j].a-P[i].a)^(P[O].a-P[j].a))<0) continue;
					ans[k]=min(ans[k],x);
					for (int t=O+1;t<=n;++t)
					{
						if (((P[j].a-P[i].a)^(P[t].a-P[j].a))<0) continue;
						f[k+1][j][t]=min(f[k+1][j][t],x+P[t].v+tri[j][t]);
					}
				}
	}
	for (int k=3;k<=n;++k) printf("%d ",ans[k]==INF?-1:ans[k]);
	return 0;
}

//by qlwpc
