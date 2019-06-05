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
const int N=100010;
int a[N];
namespace subtask12{
	const int N=10010;
	int cnt[16384+10],tp[N];
	inline int Mysort(int *a,int n)
	{
		memset(cnt,0,sizeof(int)*16384);
		for(int i=1;i<=n;i++) cnt[a[i]&16383]++;
		for(int i=1;i<16384;i++) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--) tp[cnt[a[i]&16383]--]=a[i];
		
		memset(cnt,0,sizeof(int)*16384);
		for(int i=1;i<=n;i++) cnt[tp[i]>>14]++;
		for(int i=1;i<16384;i++) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--) a[cnt[tp[i]>>14]--]=tp[i];
		return 0;
	}
	inline int brute_force40(int m,int use_std_sort)
	{
		while(m--)
		{
			int tp=inn(),l=inn(),r=inn(),x=0,ans=0;
			if(tp==1) { x=inn();rep(i,l,r) a[i]^=x; }
			else if(tp==2) use_std_sort?sort(a+l,a+r+1),0:Mysort(a+l-1,r-l+1);
			else { rep(i,l,r) ans^=a[i];printf("%d\n",ans); }
		}
		return 0;
	}
}
namespace subtask3{
	struct segment{
		int l,r,s,t;
		segment *ch[2];
	}*rt;
	inline int push_up(segment* &rt) { return rt->s=rt->ch[0]->s^rt->ch[1]->s; }
	inline int build(segment* &rt,int l,int r)
	{
		rt=new segment,rt->l=l,rt->r=r,rt->t=0;if(l==r) return rt->s=a[l];int mid=(l+r)>>1;
		return build(rt->ch[0],l,mid),build(rt->ch[1],mid+1,r),push_up(rt);
	}
	inline int update_tags(segment* &rt,int v) { return (((rt->r-rt->l+1)&1)?rt->s^=v:0),rt->t^=v; }
	inline int push_down(segment* &rt) { return update_tags(rt->ch[0],rt->t),update_tags(rt->ch[1],rt->t),rt->t=0; }
	inline int update(segment* &rt,int s,int t,int v)
	{
		int l=rt->l,r=rt->r,mid=(l+r)>>1;
		if(s<=l&&r<=t) return update_tags(rt,v);
		if(rt->t) push_down(rt);
		if(s<=mid) update(rt->ch[0],s,t,v);
		if(mid<t) update(rt->ch[1],s,t,v);
		return push_up(rt);
	}
	inline int query(segment* &rt,int s,int t)
	{
		int l=rt->l,r=rt->r,mid=(l+r)>>1;
		if(s<=l&&r<=t) return rt->s;
		if(rt->t) push_down(rt);int ans=0;
		if(s<=mid) ans^=query(rt->ch[0],s,t);
		if(mid<t) ans^=query(rt->ch[1],s,t);
		return ans;
	}
	inline int brute_force20(int n,int m)
	{
		build(rt,1,n);
		while(m--)
		{
			int tp=inn(),l=inn(),r=inn(),x=0;
			if(tp==1) x=inn();assert(tp==1||tp==3);
			if(tp==1) update(rt,l,r,x);
			else printf("%d\n",query(rt,l,r));
		}
		return 0;
	}
}
int main()
{
	freopen("save.in","r",stdin),freopen("save.out","w",stdout);
	int n=inn(),m=inn();rep(i,1,n) a[i]=inn();
	if(max(n,m)<=10000) return subtask12::brute_force40(m,max(n,m)<=1000);
	return subtask3::brute_force20(n,m);
}
