#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int f[55][55][55];
int sum[55][55][55],ans[55];
struct Node
{
	double x,y;
	int w,i,vis;
}a[55];
double operator *(Node x,Node y)
{
	return x.x*y.y-y.x*x.y;
}
Node operator -(Node x,Node y)
{
	return (Node){x.x-y.x,x.y-y.y};
}
Node operator +(Node x,Node y)
{
	return (Node){x.x+y.x,x.y+y.y};
}
double xj(Node x,Node y,Node z)
{
	return (y-x)*(z-x);
}
bool cmp(Node x,Node y)
{
	if(x.vis==1)
		return 0;
	if(y.vis==1)
		return 1;
	return x.x<y.x||x.x==y.x&&x.y<y.y;
}
int in(Node x,Node y,Node z,Node w)
{
	double w1,w2,w3;
	w1=xj(x,y,w);
	w2=xj(y,z,w);
	w3=xj(z,x,w);
	if(w1>0&&w2>0&&w3>0) return 1;
	if(w1<0&&w2<0&&w3<0) return 1;
	return 0;
}
bool cmp2(Node x,Node y)
{
	if(x.vis==1)
		return 0;
	if(y.vis==1)
		return 1;
	return xj(a[1],x,y)<0;
}
int main()
{
	freopen("but.in","r",stdin);
	freopen("but.out","w",stdout);
	int n,i,j,k,l,num;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%lf%lf%d",&a[i].x,&a[i].y,&a[i].w);
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;i++)
		a[i].i=i;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			for(k=1;k<=n;k++)
				for(l=1;l<=n;l++)
				{
					if(i==j||j==k||i==k||l==i||l==j||l==k)
						continue;
					if(in(a[i],a[j],a[k],a[l]))
						sum[i][j][k]+=a[l].w;
				}
	for(i=3;i<=n;i++)
		ans[i]=1000000000;
	for(i=1;i<=n;i++)
	{
		sort(a+1,a+n+1,cmp);//ºá×Ý×ø±êÅÅÐò 
		for(num=1;num<=n;num++)
			for(j=1;j<=n;j++)
				for(k=1;k<=n;k++)
					f[num][k][j]=1000000000;
		for(j=2;j<=n;j++)
		{
			if(a[j].vis)
				break;
		}
		sort(a+1+1,a+n+1,cmp2);//¼«¡ÏÅÅÐò
		for(j=2;j<=n;j++)
			f[2][1][j]=a[j].w;
		for(num=2;num<=n;num++)
		{
			for(j=2;j<=n;j++)
			{
				if(a[j].vis)
					break;
				for(k=1;k<j;k++)
				{
					if(xj(a[k],a[j],a[1])<=0)
						ans[num]=min(ans[num],f[num][k][j]+sum[a[k].i][a[j].i][a[1].i]+a[1].w);
					for(l=j+1;l<=n;l++)
					{
						if(a[l].vis)
							break;
						if(xj(a[k],a[j],a[l])<=0)
							f[num+1][j][l]=min(f[num+1][j][l],f[num][k][j]+sum[a[1].i][a[j].i][a[l].i]+a[l].w);
					}
				}
			}
		}
		a[1].vis=1;
	}
	for(i=3;i<=n;i++)
	{
		if(ans[i]>=1000000000)
			ans[i]=-1;
		printf("%d ",ans[i]);
	}
	return 0;
}

