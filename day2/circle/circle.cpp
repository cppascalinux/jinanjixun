#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
using namespace std;
int n;
li k;
li cb[40][40];
int h[40];
int e[40][40];
void init()
{
	for(int i=0;i<=n;i++)
		cb[i][0]=cb[i][i]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=i-1;j++)
			cb[i][j]=cb[i-1][j]+cb[i-1][j-1];
}
void solve()
{
	li sm=k;
	for(int i=n-1;i>=0;i--)
		for(int j=0;j<=i;j++)
		{
			if(sm>=cb[i][j])
			{
				sm-=cb[i][j];
				h[n-i]=j+1;
			}
			else
				break;
		}
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d h:%d\n",i,h[i]);
	// for(int i=0;i<=n;i++)
	// 	for(int j=0;j<=n;j++)
	// 		printf("i:%d j:%d cb:%lld\n",i,j,cb[i][j]);
}
void output()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			if(j<=h[i])
				printf("1 ");
			else
				printf("0 ");
		printf("\n");
	}
}
int main()
{
	freopen("circle.in","r",stdin);
	freopen("circle.out","w",stdout);
	scanf("%d%lld",&n,&k);
	if(k>(1LL<<n)-1)
		return printf("-1"),0;
	k=(1LL<<n)-1-k;
	// printf("k:%lld\n",k);
	init();
	solve();
	output();
	return 0;
}