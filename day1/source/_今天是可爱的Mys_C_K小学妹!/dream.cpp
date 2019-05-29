#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define mod 998244353
#define ull unsigned lint
#define db long double
#define mp make_pair
#define fir first
#define sec second
#define gc getchar()
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
inline int inn()
{
	int x,ch;while((ch=gc)<'0'||ch>'9');
	x=ch^'0';while((ch=gc)>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch^'0');return x;
}
const int N=62;
int v[N][N][N],val[N][N][N];
inline int fast_pow(int x,int k,int ans=1) { for(x<0?x+=mod:0;k;k>>=1,x=(lint)x*x%mod) (k&1)?ans=(lint)ans*x%mod:0;return ans; }
namespace subtask12{
	int s[N][N][N];lint t[N][N][N];
	inline int S(int a,int b,int c,int d,int e,int f)
	{
		return s[b][d][f]-s[a-1][d][f]-s[b][c-1][f]-s[b][d][e-1]+s[a-1][c-1][f]+s[a-1][d][e-1]+s[b][c-1][e-1]-s[a-1][c-1][e-1];
	}
	inline int U(int a,int b,int c,int d,int e,int f)
	{
		return t[a][c][e]++,t[b+1][c][e]--,t[a][d+1][e]--,t[a][c][f+1]--,
		t[b+1][d+1][e]++,t[b+1][c][f+1]++,t[a][d+1][f+1]++,t[b+1][d+1][f+1]--,0;
	}
	inline int brute_force40(int n,int m,int k,int w)
	{
		int tot=0,ans=0;
		rep(a,1,n) rep(b,1,m) rep(c,1,k)
			s[a][b][c]=s[a-1][b][c]+s[a][b-1][c]+s[a][b][c-1]-s[a-1][b-1][c]-s[a-1][b][c-1]-s[a][b-1][c-1]+s[a-1][b-1][c-1]+v[a][b][c];
		rep(a,1,n) rep(b,a,n) rep(c,1,m) rep(d,c,m) rep(e,1,k) rep(f,e,k) if(!S(a,b,c,d,e,f)) U(a,b,c,d,e,f),tot++;
		rep(a,1,n) rep(b,1,m) rep(c,1,k)
			t[a][b][c]=t[a-1][b][c]+t[a][b-1][c]+t[a][b][c-1]-t[a-1][b-1][c]-t[a-1][b][c-1]-t[a][b-1][c-1]+t[a-1][b-1][c-1]+t[a][b][c];
		rep(a,1,n) rep(b,1,m) rep(c,1,k)
		{
			int tms=fast_pow(tot,w)-fast_pow(tot-t[a][b][c]%mod,w);
			if(tms<0) tms+=mod;ans=(ans+(lint)tms*val[a][b][c])%mod;
		}
		ans=(lint)ans*fast_pow(fast_pow((lint)n*(n+1)*m*(m+1)*k*(k+1)/8%mod,w),mod-2)%mod;
		return !printf("%d\n",ans);
	}
}
namespace subtask3{
	int s[N][N][N],A[N],L[N],R[N];lint t[N][N][N];
	inline int S(int a,int b,int c,int d,int e,int f)
	{
		return s[b][d][f]-s[a-1][d][f]-s[b][c-1][f]-s[b][d][e-1]+s[a-1][c-1][f]+s[a-1][d][e-1]+s[b][c-1][e-1]-s[a-1][c-1][e-1];
	}
	inline int U(int a,int b,int c,int d,int e,int f,int g)
	{
		return t[a][c][e]+=g,t[b+1][c][e]-=g,t[a][d+1][e]-=g,t[a][c][f+1]-=g,
		t[b+1][d+1][e]+=g,t[b+1][c][f+1]+=g,t[a][d+1][f+1]+=g,t[b+1][d+1][f+1]-=g,0;
	}
	inline int brute_force60(int n,int m,int k,int w)
	{
		int tot=0,ans=0;
		rep(a,1,n) rep(b,1,m) rep(c,1,k)
			s[a][b][c]=s[a-1][b][c]+s[a][b-1][c]+s[a][b][c-1]-s[a-1][b-1][c]-s[a-1][b][c-1]-s[a][b-1][c-1]+s[a-1][b-1][c-1]+v[a][b][c];
		rep(a,1,n) rep(b,a,n) rep(c,1,m) rep(d,c,m)
		{
			rep(e,1,k) A[e]=S(a,b,c,d,e,e);
			L[0]=1;rep(e,1,k) if(!A[e]) L[e]=L[e-1];else L[e]=e+1;
			R[k+1]=k;for(int e=k;e;e--) if(!A[e]) R[e]=R[e+1];else R[e]=e-1;
			rep(e,1,k) if(!A[e]) U(a,b,c,d,e,e,(e-L[e]+1)*(R[e]-e+1)),(e==L[e]?tot+=(R[e]-L[e]+1)*(R[e]-L[e]+2)/2:0);
		}
		rep(a,1,n) rep(b,1,m) rep(c,1,k)
			t[a][b][c]=t[a-1][b][c]+t[a][b-1][c]+t[a][b][c-1]-t[a-1][b-1][c]-t[a-1][b][c-1]-t[a][b-1][c-1]+t[a-1][b-1][c-1]+t[a][b][c];
		rep(a,1,n) rep(b,1,m) rep(c,1,k)
		{
			int tms=fast_pow(tot,w)-fast_pow(tot-t[a][b][c]%mod,w);
			if(tms<0) tms+=mod;ans=(ans+(lint)tms*val[a][b][c])%mod;
		}
		ans=(lint)ans*fast_pow(fast_pow((lint)n*(n+1)*m*(m+1)*k*(k+1)/8%mod,w),mod-2)%mod;
		return !printf("%d\n",ans);
	}
}
int main()
{
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	int n=inn(),m=inn(),k=inn(),w=inn();
	rep(a,1,n) rep(b,1,m) rep(c,1,k) v[a][b][c]=!inn();
	rep(a,1,n) rep(b,1,m) rep(c,1,k) val[a][b][c]=inn();
	if(max(max(n,m),k)<=20) return subtask12::brute_force40(n,m,k,w);
	return subtask3::brute_force60(n,m,k,w);
}
