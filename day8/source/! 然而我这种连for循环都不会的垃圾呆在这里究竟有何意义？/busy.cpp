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
int c[N];vector<int> v[N];
namespace subtask1{
	int l[N],r[N];
	inline int brute_force20(int n,int m)
	{
		for(int las_ans=0;m;m--)
		{
			int tp=inn(),x=inn()^las_ans,y=inn()^las_ans,ans=n+1;
			if(tp==1) { rep(i,1,n) if(c[i]==x) c[i]=y; }
			else{
				int lc=0;rep(i,1,n) if(c[i]==x) l[++lc]=i;
				int rc=0;rep(i,1,n) if(c[i]==y) r[++rc]=i;
				if(!lc||!rc) { printf("Chtholly\n"),las_ans=0;continue; }
				if(x==y) { printf("0\n"),las_ans=0;continue; }
				for(int i=1,j=0;i<=lc;i++)
				{
					while(j<rc&&r[j+1]<l[i]) j++;
					if(j>=1) ans=min(ans,l[i]-r[j]);
					if(j<rc) ans=min(ans,r[j+1]-l[i]);
				}
				printf("%d\n",las_ans=ans);
			}
		}
		return 0;
	}
}
namespace subtask2{
	inline int calc(vector<int> &x,int v)
	{
		int L=0,R=(int)x.size()-1,ans=INT_MAX;
		while(L<=R)
		{
			int mid=(L+R)>>1;
			if(x[mid]<v) L=mid+1;
			else R=mid-1;
		}
		if(R>=0) ans=min(ans,v-x[R]);
		if(R+1<(int)x.size()) ans=min(ans,x[R+1]-v);
		return ans;
	}
	inline int calc(vector<int> &x,vector<int> &y)
	{
		if(x.size()>y.size()) return calc(y,x);int ans=INT_MAX;
		Rep(i,x) { ans=min(ans,calc(y,x[i]));if(ans==1) return ans; }
		return ans;
	}
	map<pii,int> sav;
	inline int brute_force30(int m)
	{
		for(int las_ans=0;m;m--)
		{
			int tp=inn(),x=inn()^las_ans,y=inn()^las_ans;assert(tp==2);
			if(!v[x].size()||!v[y].size()) printf("Chtholly\n"),las_ans=0;
			else if(x==y) printf("0\n"),las_ans=0;
			else if(sav.count(mp(x,y))) printf("%d\n",las_ans=sav[mp(x,y)]);
			else printf("%d\n",las_ans=sav[mp(x,y)]=sav[mp(y,x)]=calc(v[x],v[y]));
		}
		return 0;
	}
}
int main()
{
	freopen("busy.in","r",stdin),freopen("busy.out","w",stdout);
	int n=inn(),m=inn();rep(i,1,n) v[c[i]=inn()].pb(i);
	if(max(n,m)<=1000) return subtask1::brute_force20(n,m);
	return subtask2::brute_force30(m);
}
