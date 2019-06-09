#include<set>
#include<map>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct pt
{
	int val[105],maxn;
	pt(){maxn=0;memset(val,0,sizeof(val));}
	inline bool operator <(const pt &x) const
	{
		if(maxn!=x.maxn) return maxn<x.maxn;
		for(int i=1;i<=maxn;i++)
			if(val[i]!=x.val[i])
				return val[i]<x.val[i];
		return 0;
	}
};
map<pt,int> mp;
pt st;
int mod,n;
inline int fpow(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1) ans=1ll*ans*x%mod;
		x=1ll*x*x%mod;
		y/=2;
	}
	return ans;
}
inline int dfs()
{
	if(st.maxn==1u) return 0;
	if(mp.count(st)) return mp[st];
	int nw=st.maxn,sum=0,ans=0;
	for(int i=1;i<=nw;i++)
		for(int j=1;j<=nw;j++)
		{
			if(i==j)
			{
				sum=sum+st.val[i]*st.val[i];
				continue;
			}
			pt nst=st;
			int nww=st.val[i]*st.val[j];
			st.val[i]+=st.val[j];
			st.val[j]=st.val[nw];
			st.maxn--;
			sort(st.val+1,st.val+st.maxn+1);
			ans=(ans+1ll*dfs()*nww%mod)%mod;
			st=nst;
		}
	ans=(1ll*(ans+n*n)*fpow(n*n-sum,mod-2)%mod)%mod;
	mp[st]=ans;
	/*printf("ans=%d,sum=%d,st=",ans,sum);
	for(int i=1;i<=st.maxn;i++)
		printf("%d ",st.val[i]);
	printf("\n");*/
	return ans;
}
int main()
{
	freopen("random.in","r",stdin);
	freopen("random.out","w",stdout);
	scanf("%d%d",&n,&mod);
	st.maxn=n;
	for(int i=1;i<=st.maxn;i++)
		st.val[i]=1;
	printf("%d",dfs());
	return 0;
}
