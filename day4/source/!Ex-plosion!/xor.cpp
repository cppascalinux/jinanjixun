#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
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
	const int BS=(1<<24)+5;char S[BS],*h,*t;inline int gc() { if(h==t) t=(h=S)+fread(S,1,BS,stdin);return h==t?EOF:(*h++); }
	inline int inn() { int x,ch;while((ch=gc())<'0'||ch>'9');x=ch^'0';while((ch=gc())>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^'0');return x; }
}using INPUT_SPACE::inn;
namespace OUTPUT_SPACE{
	char ss[100000*15],tt[20];int ssl,ttl;inline int Flush() { return fwrite(ss+1,1,ssl,stdout),ssl=0; }
	inline int print(int x) { if(!x) ss[++ssl]='0';for(ttl=0;x;x/=10) tt[++ttl]=char(x%10+'0');for(;ttl;ttl--) ss[++ssl]=tt[ttl];return ss[++ssl]='\n'; }
}using OUTPUT_SPACE::print;using OUTPUT_SPACE::Flush;
const int N=100010;
map<int,int> t;int tp[N],x[N],del[N];
struct LB{
	int p[100],d[100],sz,n;
	inline int ins(int x,int _d)
	{
		for(int i=n;i>=0;i--) if((x>>i)&1)
		{
			if(_d>d[i]) (p[i]?swap(p[i],x),0:(p[i]=x,sz++)),swap(_d,d[i]);
			x^=p[i];if(!x) return 0;
		}
		return 0;
	}
	inline int del(int x) { rep(i,0,n) if(d[i]==x) return sz--,p[i]=d[i]=0;return 0; }
}lb;
int main()
{
	freopen("xor.in","r",stdin),freopen("xor.out","w",stdout);
	lb.n=inn();int q=inn();
	rep(i,1,q)
	{
		tp[i]=inn(),x[i]=inn();
		if(tp[i]==1) t[x[i]]=i,del[i]=q+1;
		else del[t[x[i]]]=i;
	}
	rep(i,1,q)
	{
		if(tp[i]==1) lb.ins(x[i],del[i]);else lb.del(i);
		print(1<<lb.sz);
	}
	return Flush(),0;
}
