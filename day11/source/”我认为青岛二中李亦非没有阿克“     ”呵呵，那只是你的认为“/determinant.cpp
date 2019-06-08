#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
#define to edge[i].v
#define mp make_pair
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
#define N 100010
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
namespace IO
{   const int __S=1e7;char __buf[__S],*__H,*__T;
    inline char getc()
    {   if(__H==__T) __T=(__H=__buf)+fread(__buf,1,__S,stdin);
        if(__H==__T) return -1;return *__H++;
    }
    template <class __I>inline void read(__I &__x)
	{	char __c=getc(); while(!isdigit(__c)) __c=getc();
		for(__x=0;isdigit(__c);__c=getc()) __x=__x*10+(__c^'0');
    }
}using namespace IO;
const int mod=1e9+7; int n,top,go[N],pos[N];
inline int qpow(int x,int y){int A=1;for(;y;y>>=1,x=(ll)x*x%mod)if(y&1)A=(ll)A*x%mod;return A;}
__gnu_pbds::priority_queue<pii,greater<pii>> q[N];
inline int gao(pii *a)
{   int ans=1; top=0; for(rint i=1;i<=n+1;i++) go[i]=i,pos[i]=i,q[i].clear();
    for(rint i=1;i<=n;i++) q[a[i].first].push(mp(a[i].second,i)),ans=(ll)ans*(a[i].second-a[i].first+1)%mod;
	ans=qpow(ans,mod-2);
    for(rint i=1;i<=n;i++)
    {   
        if(q[i].empty()) return 0;
		pii cur=q[i].top(); q[i].pop();
        if(cur.first<i) return 0;
		if(pos[cur.second]!=i)
        {   int qaq=go[i],qwq=pos[cur.second];
            ans=-ans,swap(pos[go[i]],pos[cur.second]),go[i]=go[qwq],go[qwq]=qaq;
        }
		q[cur.first+1].join(q[i]);
    }
    return (ans+mod)%mod;
}
pii a[N],b[N];
int main()
{	freopen("determinant.in","r",stdin);
	freopen("determinant.out","w",stdout);
	int t; cin>>t;
    while(t--)
    {   read(n);
        for(rint i=1;i<=n;i++) read(a[i].first),read(a[i].second),read(b[i].first),read(b[i].second);
        printf("%lld\n",(ll)gao(a)*gao(b)%mod);
    }
    return 0;
}
