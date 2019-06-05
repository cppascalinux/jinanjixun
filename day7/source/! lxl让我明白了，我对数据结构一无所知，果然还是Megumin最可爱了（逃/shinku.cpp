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
const int N=1000010;
struct Q{
	int l,r,id;
	inline bool operator<(const Q &q)const { return r<q.r; }
}q[N];
struct BIT{
	int b[N],n;
	inline int update(int p,int v) { for(;p<=n;p+=p&-p) b[p]+=v;return 0; }
	inline int update(int s,int t,int v) { return update(s,v),update(t+1,-v); }
	inline int query(int p) { int ans=0;for(;p;p^=p&-p) ans+=b[p];return ans; }
}b[12];int pre[N],a[N],val[N];
inline int update(int s,int t,int x,int v) { return b[x].update(s,t,v); }
inline int upd(int s,int t,int l,int r,int x)
{
	if(x-l>0&&x-l<=10) update(s,t,x-l,-1);
	if(r-x>0&&r-x<=10) update(s,t,r-x,-1);
	if(r-l+1<=10) update(s,t,r-l+1,1);
	return 0;
}
inline int add(int R,int n)
{
	int x=a[R],las=pre[x],l=x,r=x;pre[x]=R,val[x]=R+1;
	while(l>1&&x-l+1<=11&&pre[l-1]>las) l--,val[l]=min(val[l+1],pre[l]);
	while(r<n&&r-x+1<=11&&pre[r+1]>las) r++,val[r]=min(val[r-1],pre[r]);
	int i=x-1,j=x+1,cur=R;
	while(i>=l&&j<=r)
		if(val[i]>val[j])
		{
			int k=i;
			while(k>l&&val[k-1]==val[i]) k--;
			upd(val[i]+1,cur,i+1,j-1,x);
			i=k,cur=val[i],i--;
		}
		else{
			int k=j;
			while(k<r&&val[k+1]==val[j]) k++;
			upd(val[j]+1,cur,i+1,j-1,x);
			j=k,cur=val[j],j++;
		}
	while(i>=l)
	{
		int k=i;
		while(k>l&&val[k-1]==val[i]) k--;
		upd(val[i]+1,cur,i+1,j-1,x);
		i=k,cur=val[i],i--;
	}
	while(j<=r)
	{
		int k=j;
		while(k<r&&val[k+1]==val[j]) k++;
		upd(val[j]+1,cur,i+1,j-1,x);
		j=k,cur=val[j],j++;
	}
	upd(las+1,cur,l,r,x);
	return 0;
}
char ss[N*13],ans[N][12];int ssl;
int main()
{
	freopen("shinku.in","r",stdin);
	freopen("shinku.out","w",stdout);
	int n=inn(),m=inn(),mx=0;
	rep(i,1,n) a[i]=inn(),mx=max(mx,a[i]);
	rep(i,1,m) q[i].l=inn(),q[i].r=inn(),q[i].id=i;
	sort(q+1,q+m+1);rep(i,1,10) b[i].n=n;
	for(int i=1,j=0;i<=m;i++)
	{
		while(j<q[i].r) add(++j,mx);
		rep(j,1,10)
			ans[q[i].id][j]=char(b[j].query(q[i].l)%10+'0');
	}
	rep(i,1,m) { rep(j,1,10) ss[++ssl]=ans[i][j];ss[++ssl]='\n'; }
	return fwrite(ss+1,1,ssl,stdout),0;
}
