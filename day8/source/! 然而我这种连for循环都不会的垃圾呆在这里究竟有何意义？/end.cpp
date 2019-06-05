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
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
namespace INPUT_SPACE{
	const int BS=(1<<24)+5;char S[BS],*h,*t;inline char gc() { if(h==t) t=(h=S)+fread(S,1,BS,stdin);return h==t?EOF:(*h++); }
	inline int inn() { int x,ch;while((ch=gc())<'0'||ch>'9');x=ch^'0';while((ch=gc())>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^'0');return x; }
	inline int instr(char *s) { int n=0;char ch;while((ch=gc())<'0'||ch>'1');s[++n]=ch;while((ch=gc())>='0'&&ch<='1') s[++n]=ch;return n; }
}using INPUT_SPACE::inn;using INPUT_SPACE::instr;
const int N=10010;
int ans[10];char str[N];
inline int fast_pow(int x,int k,int ans=1) { for(;k;k>>=1,x=(lint)x*x%mod) (k&1)?ans=(lint)ans*x%mod:0;return ans; }
namespace MAT{
	int n;lint w[10][10];
	struct mat{
		int v[10][10];
		inline int clear() { rep(i,0,n) rep(j,0,n) v[i][j]=0;return 0; }
		inline mat operator*(const mat &b)const
		{
			const mat &a=*this;static mat c;
			rep(i,0,n) rep(j,0,n) w[i][j]=0;
			rep(i,0,n) rep(k,0,n) rep(j,0,n) w[i][j]+=(lint)a.v[i][k]*b.v[k][j];
			rep(i,0,n) rep(j,0,n) c.v[i][j]=w[i][j]%mod;
			return c;
		}
		inline mat operator*=(const mat &b) { return (*this)=(*this)*b,*this; }
		inline int& operator()(int x,int y) { return v[x][y]; }
	};
}using MAT::mat;mat A,B,C,D;
inline mat fast_pow(mat x,int k)
{
	D.clear();rep(i,0,MAT::n) D(i,i)=1;
	for(;k;k>>=1,x*=x) if(k&1) D*=x;return D;
}
namespace SOLVE_space{
	int sz[1010];
	inline int solve(int n,char *s,int m,int k)
	{
		int all=(1<<n)-1;MAT::n=n;
		rep(i,1,all) sz[i]=sz[i>>1]+(i&1);
		A.clear(),B.clear(),C.clear();
		rep(i,0,n) rep(t,0,all) if(!(sz[t]&1))
		{
			int s=0;rep(j,0,i-1) s|=1<<j;
			if(!(s&t)) A(i,i)++;B(sz[s&t],i)++;
		}
		rep(i,0,n) C(i,i)=1;
		rep(i,1,m) if(s[i]=='0') C=A*C;else C=B*C;
		C=fast_pow(C,k);return C(0,n);
	}
}
int TOT;
namespace DFS_space{
	int res,cnt[10];
	inline int getxs(int m)
	{
		int ans=1;
		rep(i,1,m) rep(j,1,cnt[i]-1) ans=(lint)ans*(mod-j)%mod;
		return ans;
	}
	inline int solve(int m)
	{
		int qwq=0,res=1;
		rep(i,1,m) if(cnt[i]&1) qwq++;else res=(lint)res*TOT%mod;
		return (lint)res*ans[qwq]%mod;
	}
	inline int dfs(int x,int m,int n)
	{
		if(x>n) return res=(res+(lint)getxs(m)*solve(m))%mod,0;
		rep(i,1,m+1) cnt[i]++,dfs(x+1,max(i,m),n),cnt[i]--;return 0;
	}
}
inline int getTOT(char *str,int n,int k)
{
	int a=0,b=0;
	rep(i,1,n) a=(2ll*a+str[i]-'0')%mod;
	rep(i,0,k-1) b=(b+fast_pow(2,i*n))%mod;
	return (lint)a*b%mod;
}
int main()
{
	freopen("end.in","r",stdin),freopen("end.out","w",stdout);
	int n=inn(),k=inn(),l=instr(str);TOT=getTOT(str,l,k);
	ans[0]=1;rep(i,1,n) ans[i]=SOLVE_space::solve(i,str,l,k);
	DFS_space::dfs(1,0,n);int Ans=DFS_space::res;
	rep(i,1,n) Ans=(lint)Ans*fast_pow(i,mod-2)%mod;
	return !printf("%d\n",Ans);
}
