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
#define gc getchar()
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
inline int inn() { int x;scanf("%d",&x);return x; } vector<int> v;
inline int getid(int x) { return int(lower_bound(v.begin(),v.end(),x)-v.begin()+1); }
const int N=30010;int L[N],R[N],w[N];
namespace subtask2{
	const int M=1000;
	int s[M],v[N],has_ans;
	inline int check(int n,int m)
	{
		memset(s,0,sizeof(int)*(m+1));
		rep(i,1,n) if(v[i]) s[L[i]]++,s[R[i]+1]--;else s[L[i]]--,s[R[i]+1]++;
		rep(i,1,m) s[i]+=s[i-1];rep(i,1,m) if(s[i]>1||s[i]<-1) return 0;
		rep(i,1,n) printf("%d ",v[i]);return printf("\n"),1;
	}
	inline int dfs(int x,int n,int m)
	{
		if(has_ans) return 0;if(x>n) return has_ans|=check(n,m);
		if(w[x]>=0) return v[x]=w[x],dfs(x+1,n,m);
		return v[x]=0,dfs(x+1,n,m),v[x]=1,dfs(x+1,n,m);
	}
	inline int brute_force15(int n,int m)
	{
		return has_ans=0,dfs(1,n,m),(has_ans?0:!printf("-1\n"));
	}
}
int main()
{
	freopen("wait.in","r",stdin);
	freopen("wait.out","w",stdout);
	int n=inn();inn();
	rep(i,1,n) L[i]=inn(),R[i]=inn(),w[i]=inn(),v.pb(L[i]),v.pb(R[i]);//,v.pb(R[i]+1);
	sort(v.begin(),v.end()),v.erase(unique(v.begin(),v.end()),v.end());
	rep(i,1,n) L[i]=getid(L[i]),R[i]=getid(R[i]);int m=(int)v.size();
	if(m<=20) return subtask2::brute_force15(n,m);
}
