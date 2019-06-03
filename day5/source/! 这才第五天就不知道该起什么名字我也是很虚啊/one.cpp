#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define mod 1000000007
#define ull unsigned lint
#define db long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define gc getchar()
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
inline int inn()
{
	int x,ch;while((ch=gc)<'0'||ch>'9');
	x=ch^'0';while((ch=gc)>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch^'0');return x;
}
const int N=700;
int a[N][N],b[N],sz[N][30],len[N],tot,tp[30];
inline void P(int &x) { x>=mod?x-=mod:0; }
inline void Q(int &x) { x<0?x+=mod:0; }
inline int fast_pow(int x,int k,int ans=1) { for(;k;k>>=1,x=(lint)x*x%mod) (k&1)?ans=(lint)ans*x%mod:0;return ans; }
inline int dfs(int x,int s,int n,int las)
{
	if(s==n) { len[++tot]=x;rep(i,1,x) sz[tot][i]=tp[i];return 0; }
	rep(i,las,n-s) tp[x+1]=i,dfs(x+1,s+i,n,i);return 0;
}
inline int all1(int *sz,int l) { rep(i,1,l) if(sz[i]^1) return 0;return 1; }
inline int gauss(int (*a)[N],int *b,int n)
{
	rep(i,1,n)
	{
		int x=i;rep(j,i,n) if(a[j][i]) { x=j;break; }
		swap(a[x],a[i]),swap(b[x],b[i]),assert(a[i][i]);
		int v=fast_pow(a[i][i],mod-2);b[i]=(lint)b[i]*v%mod;
		rep(j,i,n) a[i][j]=(lint)a[i][j]*v%mod;
		rep(j,1,n) if(i^j)
		{
			int v=a[j][i];Q(b[j]-=(lint)b[i]*v%mod);
			rep(k,i,n) Q(a[j][k]-=(lint)a[i][k]*v%mod);
		}
	}
	return 0;
}
namespace TRS_space{
	int p[30],q[30],s[30],vis[30];
	inline int is_same(int *a,int n,int *b,int m) { if(n^m) return 0;rep(i,1,n) if(a[i]^b[i]) return 0;return 1; }
	inline int getid(int *p,int n)
	{
		rep(i,1,n) q[i]=p[i],vis[i]=0;int l=0;
		rep(x,1,n) if(!vis[x])
		{
			s[++l]=0;
			for(int y=x;!vis[y];y=q[y]) vis[y]=1,s[l]++;
		}
		sort(s+1,s+l+1);
		rep(i,1,tot) if(is_same(sz[i],len[i],s,l)) return i;
		return assert(0),0;
	}
	inline int get_trs(int x,int *sz,int l,int n)
	{
		a[x][x]=1;if(all1(sz,l)) return 0;b[x]=1;
		int cnt=0,iv=(mod-fast_pow(n*(n-1)/2,mod-2))%mod;
		rep(i,1,l)
		{
			int t=cnt+1;
			rep(j,1,sz[i]) cnt++,p[cnt]=cnt+1;
			p[cnt]=t;
		}
		rep(i,1,cnt) rep(j,i+1,cnt)
			swap(p[i],p[j]),P(a[x][getid(p,cnt)]+=iv),swap(p[i],p[j]);
		return 0;
	}
}using TRS_space::get_trs;
int p[30];
int main()
{
	freopen("one.in","r",stdin),freopen("one.out","w",stdout);
	int n=inn();rep(i,1,n) p[i]=inn();
	dfs(0,0,n,1);rep(i,1,tot) get_trs(i,sz[i],len[i],n);
	return gauss(a,b,tot),!printf("%d\n",b[TRS_space::getid(p,n)]);
}
