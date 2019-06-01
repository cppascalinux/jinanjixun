#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m;
int s[100009];
int f[21][1050000];
int dfs(int l,int s)
{
	if(f[l][s]!=-1)
		return f[l][s];
	if(l==1)
		return f[l][s]=s;
	if(l&1)//A walk
	{
		for(int i=1;i<=l-1;i++)
		{
			int ns=s&((1<<(i-1))-1);
			int np=s&(~((1<<(i+1))-1));
			ns+=np>>1;
			if(!dfs(l-1,ns))
				return f[l][s]=0;
		}
		return f[l][s]=1;
	}
	for(int i=1;i<=l-1;i++)
	{
		int ns=s&((1<<(i-1))-1);
		int np=s&(~((1<<(i+1))-1));
		if(!(s&(1<<i))&&!(s&(1<<(i-1))))
			ns+=np>>1;
		else
			ns+=(np>>1)+(1<<(i-1));
		if(dfs(l-1,ns))
			return f[l][s]=1;
	}
	return f[l][s]=0;
}
int main()
{
	freopen("game.in","r",stdin);
	freopen("game1.out","w",stdout);
	int t;
	scanf("%d",&t);
	memset(f,-1,sizeof(f));
	while(t--)
	{
		scanf("%d%d",&n,&m);
		int st=0;
		for(int i=1;i<=n;i++)
			scanf("%d",s+i),s[i]&=1,st+=s[i]*(1<<(i-1));
		if(n==1)
		{
			if(s[1]==1)
				printf("B\n");
			else
				printf("A\n");
			continue;
		}
		if(((n&1)^m)==0)
		{
			printf("A\n");
			continue;
		}
		if(dfs(n,st))
			printf("B\n");
		else
			printf("A\n");
	}
	return 0;
}