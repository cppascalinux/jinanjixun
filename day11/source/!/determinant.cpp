#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define ll long long
using namespace std;
const ll MOD=1000000007;
int t,n,p[100005],l[100005],r[100005],l1[100005],r1[100005],ans,c[100005],sa[100005];
vector<int>s[100005];
ll quick_pow(ll x,ll a)
{
	ll ans=1;
	while(a)
	{
		if(a&1)ans=ans*x%MOD;
		x=x*x%MOD;
		a>>=1;
	}
	return ans;
}
bool cmp(int x,int y)
{
	return r[x]<r[y];
}
bool cmp2(int x,int y)
{
	return l1[x]<l1[y];
}
void add(int x)
{
	while(x<=n)
	{
		c[x]++;
		x+=x^(x&(x-1));
	}
}
int sum(int x)
{
	int ans=0;
	while(x)
	{
		ans+=c[x];
		x&=x-1;
	}
	return ans&1;
}
int main()
{
	freopen("determinant.in","r",stdin);
	freopen("determinant.out","w",stdout);
	scanf("%d",&t);
	while(t--)
	{
		bool flag=1;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)s[i].clear();
		ll res=1;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&l1[i],&r1[i]);
			scanf("%d%d",&l[i],&r[i]);
			s[l1[i]].push_back(i);
			res=res*quick_pow(r1[i]-l1[i]+1,MOD-2)%MOD*quick_pow(r[i]-l[i]+1,MOD-2)%MOD;
		}
		for(int i=1;i<=n;i++)
		{
			sort(s[i].begin(),s[i].end(),cmp);
			int x=(int)s[i].size();
			if(x==0)
			{
				flag=0;
				break;
			}
			p[s[i][0]]=i;
			for(int j=1;j<x;j++)
			{
				if(r1[s[i][j]]==r1[s[i][j-1]])
				{
					flag=0;
					break;
				}
				s[r1[s[i][j-1]]+1].push_back(s[i][j]);
				l1[s[i][j]]=r1[s[i][j-1]]+1;
			}
			if(flag==0)break;
		}
		if(flag==0)
		{
			printf("0\n");
			continue;
		}
		for(int i=1;i<=n;i++)s[i].clear();
		for(int i=1;i<=n;i++)
		{
			s[l[i]].push_back(i);
		}
		for(int i=1;i<=n;i++)
		{
			sort(s[i].begin(),s[i].end(),cmp);
			int x=(int)s[i].size();
			if(x==0)
			{
				flag=0;
				break;
			}
			p[s[i][0]]=l1[i];
			for(int j=1;j<x;j++)
			{
				if(r[s[i][j]]==r[s[i][j-1]])
				{
					flag=0;
					break;
				}
				s[r[s[i][j-1]]+1].push_back(s[i][j]);
			}
			if(flag==0)break;
		}
		if(flag==0)
		{
			printf("0\n");
			continue;
		}
		ans=0;
		for(int i=1;i<=n;i++)c[i]=0;
		for(int i=n;i>=1;i--)
		{
			ans^=sum(p[i]);
			add(p[i]);
		}
		if(ans)printf("%lld\n",1000000006*res%MOD);
		else printf("%lld\n",res);
	}
	return 0;
}
