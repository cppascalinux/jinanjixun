#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>

#define UL long long 
#define LL long long 
#define Re register
using namespace std;
const int  M=500101;
const int  T=10;

struct io
{
	char ibuf[10<<22] , * s , obuf[10<<22] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen("shinku.in","r",stdin);
		freopen("shinku.out","w",stdout);
		fread( s = ibuf , 1 , 10<<22 , stdin );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
	}
	inline int read()
	{
		register int u = 0;
		while( * s < 48 ) s++;
		while( * s > 32 )
			u = u * 10 + * s++ - 48;
		return u;
	}
	template < class T >
	inline void print( register T u )
	{
		static int * q = a;
		if( !u ) * t++ = 48;
		else
		{
			while( u ) * q++ = u % 10 + 48 , u /= 10;
			while( q != a )
				* t++ = * --q;
		}
		//
	}
	inline void endll()
	{
		* t++ = '\n';
	}
} ip;


int n,m,a[M],qs,c[M],L,R,k,w[M],e[M],SZ;
LL s[20],res,ans[M];
UL j;
struct vv
{
    int l,r,id;
} d[M],u[M];
LL f[M];
inline bool cmp(vv x,vv y)
{
    return x.l/SZ==y.l/SZ ? ((x.l/SZ)&1 ? x.r<y.r : x.r>y.r) : x.l<y.l;
}

inline void jian(const int k)
{
    if(res/s[T-k]%T==0) res+=9*s[T-k];
    else res-=s[T-k];	
}

inline void add(const int k)
{
    if(res/s[T-k]%T==9) res-=9*s[T-k];
    else res+=s[T-k];
}


inline void del(const int x)
{
    c[a[x]]--;
    if(c[a[x]]) return ;
    int k=a[x]/T, y=a[x]%T, t, r;
    UL u=f[k]<<(T-y); u&=j;
    if(e[u]==y && k)
    {
        t=e[f[k-1]]+e[u];
        if(!y&&(k-2)>=0&&t==T) t+=f[k-2]&(1<<9);
    }
    else t=e[u];
    u=(f[k]>>y+1);
    if(w[u]==(9-y)) 
    {
        r=w[f[k+1]]+w[u];
        if(!(9-y)&&r==T) r+=f[k+2]&1;
    }
    else r=w[u];
    if(t+r<=9)jian(t+r+1);
    if(t<=T && t) add(t);
    if(r<=T && r) add(r);
    f[k]^=(1<<y);
}

inline void ba(const int x)
{
    c[a[x]]++;
    if(c[a[x]]!=1) return ;
    int k=a[x]/T, y=a[x]%T, t, r;
    LL u=f[k]<<(T-y); u&=j;
    if(e[u]==y && k)
    {
        t=e[f[k-1]]+e[u];
        if(!y&&(k-2)>=0&&t==T) t+=f[k-2]&(1<<9);
    }
    else t=e[u];
    u=(f[k]>>y+1);
    if(w[u]==(9-y)) 
    {
        r=w[f[k+1]]+w[u];
        if(!(9-y)&&r==T) r+=f[k+2]&1;
    }
    else r=w[u];
    if(t+r<=9) add(t+r+1);
    if(t<=T && t) jian(t);
    if(r<=T && r) jian(r);
    f[k]^=1<<y;
}

inline void pt(const LL x)
{
    for(Re int i=9;i>=0;i--) ip.print(x/s[i]%T);
    ip.endll();
}

int main()
{
    n=ip.read(), m=ip.read(); SZ=sqrt(m);
    for(Re int i=1;i<=n;i++) a[i]=ip.read();
    for(Re int i=1;i<=m;i++) d[i].l=ip.read(), d[i].r=ip.read(), d[i].id=i;
    sort(d+1,d+1+m,cmp); k=1;
    for(Re int i=1,k=1<<9;i<(1<<T);i++)
    {
        if(i&k) e[i]=e[(i^k)<<1]+1;
        if(i&1) w[i]=w[i>>1]+1;
    }
    s[0]=1;
    for(Re int i=1;i<=T;i++) s[i]=s[i-1]*T;
    j=(1<<T)-1;
    for(Re int i=1;i<=m;i++)
    {
        while(L<d[i].l) del(L++);
        while(R>d[i].r) del(R--);
        while(L>d[i].l) ba(--L);
        while(R<d[i].r) ba(++R);
        ans[d[i].id]=res;
    }
    for(Re int i=1;i<=m;i++) pt(ans[i]);
    return 0;
}
