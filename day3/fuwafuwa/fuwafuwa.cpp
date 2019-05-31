#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
using namespace std;
int n,m,a,b;
int gcd(int a,int b)
{
	return !a||!b?a+b:gcd(b,a%b);
}
namespace p1
{
	int rt,dep[509],l[509],r[509],v[509];
	void ins(int &p,int x)
	{
		if(!p)
			return p=x,void();
		if(v[x]<v[p])
			ins(l[p],x);
		else
			ins(r[p],x);
	}
	void solve()
	{
		for(int i=1;i<=n;i++)
		{
			v[i]=(a+(li)b*i)%m;
			ins(rt,i);
		}
		for(int i=1;i<=n;i++)
		{
			if(l[i])
				dep[l[i]]=dep[i]+1;
			if(r[i])
				dep[r[i]]=dep[i]+1;
		}
		printf("%d\n",dep[n]);
		memset(dep,0,sizeof(dep));
		memset(l,0,sizeof(l));
		memset(r,0,sizeof(r));
		memset(v,0,sizeof(v));
		rt=0;
	}
}
namespace p2
{
	int rt,dep[1000009],l[1000009],r[1000009],v[1000009];
	void ins(int &p,int x)
	{
		if(!p)
			return p=x,void();
		if(v[x]<v[p])
			ins(l[p],x);
		else
			ins(r[p],x);
	}
	void solve()
	{
		int g=gcd(b,m);
		
	}
}
int main()
{
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d%d",&a,&b,&m,&n);
		if(n<=500)
			p1::solve();
		else
			p2::solve();
	}
	return 0;
}