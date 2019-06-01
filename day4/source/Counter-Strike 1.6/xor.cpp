#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;
const int N=110;
template <class nmsl> inline void read(nmsl &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}
set <ll> t; 

int m, q;
ll b[N];
ll ans=1;
inline int insrt(ll x)
{
	for(R int i=m-1; i>=0; i--)
	{
		if((x>>i)&1)
		{
			if(b[i])x^=b[i];
			else 
			{
				b[i]=x;
				for(R int j=i-1; j>=0; j--)if((b[i]>>j)&1)b[i]^=b[j];
				for(R int j=i+1; j<=30; j++)if((b[j]>>i)&1)b[j]^=b[i];
				return 1;
			}
		}
	}
	return 0;
}
set <ll> :: iterator it;
int main()
{
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	read(m), read(q);
	for(R int i=1, qa; i<=q; i++)
	{
		ll qb;
		read(qa), read(qb);
		if(qb>=(1<<m)){t.insert(qb);printf("%lld\n", ans);continue;}
		if(qa==1)
		{
			t.insert(qb);
			if(insrt(qb))ans*=2;
		}
		else
		{
			ans=1;
			for(R int i=0; i<=m; i++)b[i]=0;
			t.erase(qb);
			for(it = t.begin(); it!=t.end(); it++)
				if(insrt(*it))ans*=2;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
