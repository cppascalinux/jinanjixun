#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define Mod 1000000007
using namespace std;
int n,m;
int b[11];
int f[32][1<<10][1<<10];
inline void add(int& x,int y)
{
	x+=y;
	if(x>=Mod)x-=Mod;
	return ;
}
int x[11],y[11];
inline void trans(int o,int s1,int s2,int t)
{
	for(int i=1;i<=n;i++)
		x[i]=((b[i]>>(o-1))&1)&((t>>(i-1))&1),
		y[i]=((b[i]>>(o-1))&1)|((t>>(i-1))&1);
	int t1=s1,t2=s2;
	for(int i=1;i<n;i++)
	{
		if(!((s1>>(i-1))&1))
		{
			if(x[i]>x[i+1])return ;
			t1|=(x[i]<x[i+1])<<(i-1);
		}
		if(!((s2>>(i-1))&1))
		{
			if(y[i]<y[i+1])return ;
			t2|=(y[i]>y[i+1])<<(i-1);
		}
	}
	add(f[o-1][t1][t2],f[o][s1][s2]);
	return ;
}
int main()
{
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	f[m][0][0]=1;
	for(int i=m;i>0;i--)
		for(int s1=0;s1<(1<<(n-1));s1++)
			for(int s2=0;s2<(1<<(n-1));s2++)
				if(f[i][s1][s2])
				{
//					printf("%d ",i);ot(s1);ot(s2);printf(":%d\n",f[i][s1][s2]);
					for(int t=0;t<(1<<n);t++)
						trans(i,s1,s2,t);
				}
	int ans=0;
	for(register int i=0;i<(1<<(n-1));i++)
		for(int j=0;j<(1<<(n-1));j++)
			add(ans,f[0][i][j]);
	printf("%d\n",ans);
	fclose(stdin);fclose(stdout);
	return 0;
}
