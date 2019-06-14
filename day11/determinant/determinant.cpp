//2019.06.14
//day11 t1 Determinant 行列式的期望=期望的行列式,将矩阵差分,每个矩形变成4个元素,对于行列分别消元
//对于行和列分别建一棵树,(若有环,则一定能消出空行/列,行列式为0),在树上类似dfs的过程消元,
//对于n个矩形,每一个都只能取一种(xi,yi),答案的绝对值为所有概率的乘积
//正负号则是置换xi->yi的符号,等价于xi->i的符号*i->yi的符号,因此行列的符号相互独立,这样计算是对的
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define mod 1000000007
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,tot;
int hd[100009],eg[200009],nxt[200009],id[200009];
pii ex[100009],ey[100009];
int f[100009],v[100009];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
int fnd(int x)
{
	return x==f[x]?x:f[x]=fnd(f[x]);
}
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	id[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs(int x,int fa)
{
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			v[id[i]]=eg[i];
			dfs(eg[i],x);
		}
}
int solve(pii *e)
{
	tot=0;
	memset(hd,0,sizeof(hd));
	for(int i=1;i<=n+1;i++)
		f[i]=i;
	for(int i=1;i<=n;i++)
	{
		int fa=fnd(e[i].fi),fb=fnd(e[i].se);
		if(fa==fb)
			return 0;
		ins(e[i].fi,e[i].se,i),ins(e[i].se,e[i].fi,i);
		f[fa]=fb;
	}
	dfs(n+1,0);
	int sgn=1;
	for(int i=1;i<=n;i++)
		if(v[i]==e[i].se)
			sgn=mod-sgn;
	for(int i=1;i<=n;i++)
		f[i]=i;
	for(int i=1;i<=n;i++)
	{
		int fa=fnd(i),fb=fnd(v[i]);
		if(fa!=fb)
			sgn=mod-sgn;
		f[fa]=fb;
	}
	return sgn;
}
int main()
{
	freopen("determinant.in","r",stdin);
	freopen("determinant.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		int s=1;
		for(int i=1,a,b,c,d;i<=n;i++)
		{
			scanf("%d%d%d%d",&a,&b,&c,&d);
			s=(li)s*(b-a+1)%mod*(d-c+1)%mod;
			ex[i]=pii(a,b+1);
			ey[i]=pii(c,d+1);
		}
		// printf("s:%d\n",s);
		s=(li)qpow(s,mod-2)*solve(ex)%mod*solve(ey)%mod;
		printf("%d\n",s);
	}
	return 0;
}