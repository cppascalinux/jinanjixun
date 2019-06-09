#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n,k,m,stk;
int s[100009];
int st[100009],vis[100009];
int tmp[100009];
int solve1()
{
	if(k==1)
		return printf("0\n"),1;
	int bit=0;
	while((1<<bit)<k)
		bit++;
	if((1<<bit)==k)
	{
		printf("%d\n",k-1);
		for(int l=1;l<=k-1;l<<=1)
		{
			for(int i=1;i<=k-1;i+=l*2)
				printf("%d %d\n",i+l,i);
		}
		return 1;
	}
	return 0;
}
int dfs(int p1,int sm1,int p2)
{
	vis[p1]=vis[p2]=1;
	int nsm=sm1+1;
	int bit=0;
	while(1<<bit<nsm)
		bit++;
	bit--;
	int len=1<<bit;
	if(nsm-len==1)
		return printf("%d %d\n",p1,p2),p2;
	int nt=nsm-len;
	int np=st[stk--];
	int tsm1=sm1,tsm2=nt;
	while(1)
	{
		if(sm1==len)
		{
			
		}
	}
}
void getans()
{

}
void solve2()
{
	if(k&1)
	{
		if(n<k+2)
			return printf("-1"),void();
		m=k+2;
		getans();
	}
	else
	{
		if(n<k+1)
			return printf("-1"),void();
		m=k+1;
		getans();
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("chemistry.in","r",stdin);
	freopen("chemistry.out","w",stdout);
#endif
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		s[i]=1;
	for(int i=n;i>=2;i--)
		st[++stk]=i;
	if(!solve1())
		solve2();
	return 0;
}