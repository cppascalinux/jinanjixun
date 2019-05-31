#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
ll n,m,a,b;
int t;
ll ask(ll b,ll m,ll l,ll r)
{
//	printf("(%lld,%lld,%lld,%lld)\n",b,m,l,r);
	if(r==0)r=m;
	if(l>=r||l==0)return 0;
	if(r-l>=b)return (l-1)/b+1;
	ll k=(m-1)/b+1;
	ll v=k*b-m;
	ll x=ask(v,b,l%b,r%b);
//	printf("%lld,%lld,%lld,%lld\n",v,b,l%b,r%b);
//	printf("%lld %lld\n",x,x*v%b);
	ll a=v*x;
//	printf("After %lld turns,a=%lld,k=%lld\n",x,a,k);
	if(a<l)
	{
//		printf("type=1\n");
		return x*k+(l-a-1)/b+1;
	}
	else if(a<r)
	{
//		printf("type=2\n");
		return x*k;
	}
	else
	{
//		printf("type=3\n");
		return x*k-(a-l)/b;
	}
}
int main()
{
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
//	ll x=ask(19,445,423,426);
//	printf("19,445,423,426\n");
//	printf("%lld %lld\n",x,x*19%445);
//	return 0;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%lld%lld%lld%lld",&a,&b,&m,&n);
		a%=m,b%=m;
		ll nowl=0,nowr=m,tl=0,tr=0,v=(a+n%m*b)%m,dep=0;
		ll last=a,tot=0;
		while(nowl<nowr)
		{
//			if(tot>n)return 0;
//			printf("%lld\n",tot);
//			printf("st=%lld,[%lld,%lld),l=%lld,r=%lld:\n",last,nowl,nowr,tl,tr);
			ll p=ask(b,m,(nowl-last-b+m+m)%m,(nowr-last-b+m+m)%m);
			p++;
			tot+=p;
			if(tot==n)break;
			ll now=(last+p%m*b)%m;
//			printf("%lld %lld %lld\n",tot,(a+tot%m*b)%m,now);
			dep++;
			if(now<=v)
			{
				ll x=now-nowl;
				if(tl==0||n-tot-1<=0);
				else if(x==0)
				{
					dep+=(n-tot-1)/(tot-tl);
					tot+=(n-tot-1)/(tot-tl)*(tot-tl);
				}
				else
				{
					if(now+(__int128)(n-tot-1)/(tot-tl)*x<v)
					{
						now+=(n-tot-1)/(tot-tl)*x;
						dep+=(n-tot-1)/(tot-tl);
						tot+=(n-tot-1)/(tot-tl)*(tot-tl);
					}
					else if(v-now-1>=0)
					{
						tot+=(v-now-1)/x*(tot-tl);
						dep+=(v-now-1)/x;
						now+=(v-now-1)/x*x;
					}
				}
				last=now;
				nowl=last;
				tl=tot;
			}
			else
			{
				ll x=nowr-now;
				if(tr==0||n-tot-1<=0);
				else if(x==0)
				{
					dep+=(n-tot-1)/(tot-tr);
					tot+=(n-tot-1)/(tot-tr)*(tot-tr);
				}
				else
				{
					if(now-(__int128)(n-tot-1)/(tot-tr)*x>v)
					{
						now-=(n-tot-1)/(tot-tr)*x;
						dep+=(n-tot-1)/(tot-tr);
						tot+=(n-tot-1)/(tot-tr)*(tot-tr);
					}
					else if(now-v-1>=0)
					{
						dep+=(now-v-1)/x;
						tot+=(now-v-1)/x*(tot-tr);
						now-=(now-v-1)/x*x;
					}
				}
				last=now;
				nowr=last;
				tr=tot;
			}
		}
		printf("%lld\n",dep);
	}
	return 0;
}
