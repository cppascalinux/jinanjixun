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
	const int BS=(1<<24)+5;char S[BS],*h,*t;inline char gc() { if(h==t) t=(h=S)+fread(S,1,BS,stdin);return h==t?EOF:(*h++); }
	inline int inn()
	{
		int z=1,x=0,ch;while(((ch=gc())<'0'||ch>'9')&&ch!='-');
		if(ch^'-') x=ch^'0';else z=0;
		while((ch=gc())>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^'0');
		return z?x:-x;
	}
}using INPUT_SPACE::inn;
namespace OUTPUT_SPACE{
	char ss[100010*15],tt[20];int ssl,ttl;
	inline int Flush() { return fwrite(ss+1,1,ssl,stdout),ssl=0; }
	inline int print(int x)
	{
		if(!x) ss[++ssl]='0';for(ttl=0;x;x/=10) tt[++ttl]=char(x%10+'0');
		for(;ttl;ttl--) ss[++ssl]=tt[ttl];return ss[++ssl]='\n';
	}
}using OUTPUT_SPACE::print;using OUTPUT_SPACE::Flush;
const int N=100010,LOG=35;const lint INF=LLONG_MAX;
int tmp[N],Lt[N],Rt[N],A[N],B[N],C[N];
inline int *newInt(int n) { int *p=new int[n+1];memset(p,0,sizeof(int)*(n+1));return p; }
struct BLOCK{
	int n,sz,bc,ndc;lint *a,*tg,*tgs,val;int pre[N],nxt[N],*bel,*L,*R,*ps;
	inline int build(int m)
	{
		rep(i,1,m) if(!pre[i]) pre[i]=pre[i-1];
		for(int i=m;i;i--) if(!nxt[i]) nxt[i]=nxt[i+1];
		sz=int(sqrt(n*(log(n)/log(2))/30+1)),bc=(n-1)/sz+1;
		bel=newInt(n),L=newInt(bc),R=newInt(bc),ps=newInt(n);
		rep(i,1,bc)
		{
			L[i]=(i-1)*sz+1,R[i]=min(i*sz,n);
			rep(j,L[i],R[i]) bel[j]=i,ps[j]=j;
		}
		a=new lint[n+1];rep(i,1,n) a[i]=0;
		tg=new lint[bc+1];rep(i,0,bc) tg[i]=0;
		tgs=new lint[bc+1];rep(i,0,bc) tgs[i]=0;
		return 0;
	}
	inline int _merge(int l,int p,int r)
	{
		if(l>p||p>=r) return 0;int b=bel[p],Lc=0,Rc=0;
		rep(i,L[b],R[b]) if(ps[i]>=l)
		{
			if(ps[i]<=p) Lt[++Lc]=ps[i],ps[i]=0;
			else if(ps[i]<=r) Rt[++Rc]=ps[i],ps[i]=0;
		}
		int i=1,j=1,cnt=0;
		while(i<=Lc&&j<=Rc)
			if(a[Lt[i]]<=a[Rt[j]]) tmp[++cnt]=Lt[i++];
			else tmp[++cnt]=Rt[j++];
		while(i<=Lc) tmp[++cnt]=Lt[i++];
		while(j<=Rc) tmp[++cnt]=Rt[j++];cnt=0;
		rep(i,L[b],R[b]) if(!ps[i]) ps[i]=tmp[++cnt];
		return 0;
	}
	inline int _merge(int L,int p1,int p2,int R)
	{
		int Ac=0,Bc=0,Cc=0;
		rep(i,L,R)
			if(ps[i]<p1) A[++Ac]=ps[i];
			else if(ps[i]<p2) B[++Bc]=ps[i];
			else C[++Cc]=ps[i];
		int i=1,j=1,k=1,cnt=L-1;
		while(i<=Ac||j<=Bc||k<=Cc)
		{
			lint vA=(i<=Ac?a[A[i]]:INF),vB=(j<=Bc?a[B[j]]:INF),vC=(k<=Cc?a[C[k]]:INF);
			if(vA<=vB&&vA<=vC) tmp[++cnt]=A[i++];
			else if(vB<=vA&&vB<=vC) tmp[++cnt]=B[j++];
			else tmp[++cnt]=C[k++];
		}
		rep(i,L,R) ps[i]=tmp[i];return 0;
	}
	inline int update(int p,lint v) { p=nxt[p],a[p]+=v;int bp=bel[p];return _merge(L[bp],p,p+1,R[bp]); }
	inline int update(int s,int t,lint v)
	{
		if(!nxt[s]||!pre[t]) return 0;
		s=nxt[s],t=pre[t];if(s>t) return 0;v*=val;
		int bs=bel[s],bt=bel[t];
		if(bs==bt) { rep(i,s,t) a[i]+=v;_merge(L[bs],s,t+1,R[bs]); }
		else{
			tgs[bs+1]+=v,tgs[bt]-=v,ndc=1;
			rep(i,s,R[bs]) a[i]+=v;_merge(L[bs],s-1,R[bs]);
			rep(i,L[bt],t) a[i]+=v;_merge(L[bt],t,R[bt]);
		}
		return 0;
	}
	inline int query(int b,int v)
	{
		int l=L[b],r=R[b];
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(a[ps[mid]]+tg[b]<=v) l=mid+1;
			else r=mid-1;
		}
		return r-L[b]+1;
	}
	inline int query(int s,int t,int v)
	{
		if(!nxt[s]||!pre[t]) return 0;
		s=nxt[s],t=pre[t];if(s>t) return 0;
		int bs=bel[s],bt=bel[t];int ans=0;
		if(ndc)
		{
			rep(i,1,bc) tgs[i]+=tgs[i-1];
			rep(i,1,bc) tg[i]+=tgs[i],tgs[i]=0;
			ndc=0;
		}
		if(bs==bt) rep(i,s,t) ans+=(a[i]+tg[bs]<=v);
		else{
			rep(i,s,R[bs]) ans+=(a[i]+tg[bs]<=v);
			rep(i,L[bt],t) ans+=(a[i]+tg[bt]<=v);
			rep(i,bs+1,bt-1) ans+=query(i,v);
		}
		return ans;
	}
}b[LOG];
namespace SEG{
	int id[N],idc,n,bid[N<<2];
	inline int build(int x,int l,int r)
	{
		if(!id[r-l+1]) id[r-l+1]=++idc,b[idc].val=r-l+1;
		bid[x]=id[r-l+1],b[bid[x]].nxt[l]=b[bid[x]].pre[r]=++b[bid[x]].n;
		if(l==r) return 0;int mid=(l+r)>>1;
		return build(x<<1,l,mid),build(x<<1|1,mid+1,r);
	}
	inline int prelude(int _n) { n=_n,build(1,1,n);rep(i,1,idc) b[i].build(n);return 0; }
	inline int update(int x,int l,int r,int s,int t,int v)
	{
		if(s<=l&&r<=t) return 0;
		int L=max(l,s),R=min(r,t),mid=(l+r)>>1;
		if(L<=R) b[bid[x]].update(l,(R-L+1ll)*v);
		if(s<=mid) update(x<<1,l,mid,s,t,v);
		if(mid<t) update(x<<1|1,mid+1,r,s,t,v);
		return 0;
	}
	inline int update(int l,int r,int v) { rep(i,1,idc) b[i].update(l,r,v);return update(1,1,n,l,r,v); }
	inline int query(int l,int r,int v) { int ans=0;rep(i,1,idc) ans+=b[i].query(l,r,v);return ans; }
}
int main()
{
	freopen("flipflap.in","r",stdin),freopen("flipflap.out","w",stdout);
	int n=inn(),m=inn();SEG::prelude(n);
	while(m--)
	{
		int tp=inn(),l=inn(),r=inn(),v=inn();
		if(tp==1) SEG::update(l,r,v);
		else print(SEG::query(l,r,v));
	}
	return Flush(),0;
}
