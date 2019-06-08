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
	const int BS=(1<<24)+5;char Buffer[BS],*HD,*TL;char gc() { if(HD==TL) TL=(HD=Buffer)+fread(Buffer,1,BS,stdin);return (HD==TL)?EOF:*HD++; }
	inline int inn() { int x,ch;while((ch=gc())<'0'||ch>'9');x=ch^'0';while((ch=gc())>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^'0');return x; }
}using INPUT_SPACE::inn;
inline int fast_pow(int x,int k,int ans=1) { for(;k;k>>=1,x=(lint)x*x%mod) (k&1)?ans=(lint)ans*x%mod:0;return ans; }
const int N=100003;
namespace QwQ{
	int id[N],p[N],node_cnt,val[N],lef[N],rig[N],dis[N];
	inline int new_node(int v,int d)
	{
		int x=++node_cnt;dis[x]=0;
		val[x]=v,p[id[x]=d]=x;
		return lef[x]=rig[x]=0,x;
	}
	int merge_lst(int x,int y)
	{
		if(!x||!y) return x+y;
		if(val[x]>val[y]) swap(x,y);
		rig[x]=merge_lst(rig[x],y);
		if(dis[rig[x]]>dis[lef[x]]) swap(lef[x],rig[x]);
		if(rig[x]) dis[x]=dis[rig[x]]+1;else dis[x]=0;
		return x;
	}
	struct lst{
		int rt;
		inline int init() { return rt=0; }
		inline int merge(const lst &t) { return rt=merge_lst(rt,t.rt); }
		inline int pop() { return rt=merge_lst(lef[rt],rig[rt]); }
		inline int topv() { return val[rt]; }
		inline int topid() { return id[rt]; }
		inline int empty() { return !rt; }
		inline int insert(int v,int id) { return rt=merge_lst(rt,new_node(v,id)); }
	}t[N];
	inline int solve(pii *ps,int n)
	{
		node_cnt=0;rep(i,1,n) t[i].init();int ans=1,xs=1,l,r,v,d;
		rep(i,1,n) t[l=ps[i].fir].insert(r=ps[i].sec,i),xs=xs*(r-l+1ll)%mod;
		rep(i,1,n)
		{
			while(!t[i].empty()&&t[i].topv()<i) t[i].pop();
			if(t[i].empty()) return 0;
			v=t[i].topv(),d=t[i].topid(),t[i].pop();
			if(v<n) t[v+1].merge(t[i]);
			if(d^i) ans*=-1,p[id[p[i]]=d]=p[i];
		}
		if(ans<0) ans+=mod;
		return (lint)ans*fast_pow(xs,mod-2)%mod;
	}
}using QwQ::solve;
pii p1[N],p2[N];
int main()
{
	freopen("determinant.in","r",stdin);
	freopen("determinant.out","w",stdout);
	for(int T=inn(),n;T;T--)
	{
		n=inn();
		rep(i,1,n) p1[i].fir=inn(),p1[i].sec=inn(),p2[i].fir=inn(),p2[i].sec=inn();
		printf("%lld\n",(lint)solve(p1,n)*solve(p2,n)%mod);
	}
	return 0;
}
