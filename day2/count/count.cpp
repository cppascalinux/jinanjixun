#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define mod 1000000007
using namespace std;
int n,m,op,ans;
int s[39];
li pw[3700009][9];
int p[1009],tp;
int st[1009],vis[1009];
void init()
{
	for(int i=1;i<=op;i++)
	{
		pw[i][0]=1;
		for(int j=1;j<=8;j++)
		{
			pw[i][j]=pw[i][j-1]*i;
			if(pw[i][j]>mod)
				break;
		}
	}
}
void getp()
{
	op=1;
	for(int i=1;i<=n;i++)
		op*=i;
	for(int i=1;i*i<=op;i++)
		if(op%i==0)
		{
			p[++tp]=i;
			if(i*i!=op)
				p[++tp]=op/i;
		}
	sort(p+1,p+tp+1);
}
void dfs(int d,int lsa,int lsi,li sm)
{
	if(d>m)
	{
		// printf("ans:%d\n",ans);
		// for(int i=1;i<=m;i++)
		// 	printf("%d ",st[i]);
		if(sm==op)
			ans++;
		return;
	}
	for(int i=s[d]==lsa?lsi:1;i<=tp;i++)
		if(!vis[i])
		{
			li nsm=pw[p[i]][s[d]];
			if(nsm*sm>op)
				break;
			nsm*=sm;
			if(op%nsm!=0)
				continue;
			st[d]=p[i];
			vis[i]=1;
			dfs(d+1,s[d],i,nsm);
			vis[i]=0;
		}
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d",s+i);
	sort(s+1,s+m+1);
	getp();
	init();
	// printf("tp:%d\n",tp);
	// for(int i=1;i<=tp;i++)
	// 	printf("i:%d p:%d\n",i,p[i]);
	dfs(1,-1,1,1);
	printf("%d",ans);
	return 0;
}