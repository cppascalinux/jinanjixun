#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>
#include<queue>
#define ll long long
using namespace std;
ll MOD;
const ll MOD2=100000000007;
struct Edge
{
	int to;
	int nxt;
	ll p;
}e[12000005];
int n,edgenum,tot,res[1000005][55],a[55],top[1000005],head[1000005],b[55],d[1000005];
ll p[1000005],pos[1000005],f[1000005],g[1000005];
queue<int>q;
map<ll,int>s;
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
void dfs(int step,int last,int rest,ll ha)
{
	if(rest==0)
	{
		step--;
		tot++;
		s[ha]=tot;
		top[tot]=step;
		p[tot]=ha;
		for(int i=1;i<=step;i++)res[tot][i]=a[i];
		return;
	}
	for(int i=1;i<=min(last,rest);i++)
	{
		a[step]=i;
		dfs(step+1,i,rest-i,(ha*(n+1)+i)%100000000007);
	}
}
void add(int u,int v,ll p)
{
	e[++edgenum].p=p;
	e[edgenum].to=v;
	e[edgenum].nxt=head[u];
	head[u]=edgenum;
}
bool cmp(int a,int b)
{
	return a>b;
}
int main()
{
	freopen("random.in","r",stdin);
	freopen("random.out","w",stdout);
	scanf("%d%lld",&n,&MOD);
	dfs(1,n,n,0);
//	printf("%d\n",tot);
	for(int i=1;i<=tot;i++)
	{
		for(int j=1;j<=top[i];j++)a[j]=res[i][j];
		int num=0;
		for(int x=1;x<=top[i];x++)
		{
			num+=a[x]*a[x];
			for(int y=x+1;y<=top[i];y++)
			{
				for(int j=1;j<y;j++)b[j]=a[j];
				for(int j=y;j<top[i];j++)b[j]=a[j+1];
				b[x]+=a[y];
				sort(b+1,b+top[i],cmp);
				ll ha=0;
				for(int j=1;j<top[i];j++)ha=(ha*(n+1)+b[j])%MOD2;
				int j=s[ha];
				add(i,j,2*a[x]*a[y]);
				add(j,i,2*a[x]*a[y]);
//				printf("(");
//				for(int j=1;j<=top[i];j++)printf("%d ",a[j]);
//				printf(")->(");
//				for(int j=1;j<top[i];j++)printf("%d ",b[j]);
//				printf("),%d\n",2*a[x]*a[y]);
				d[i]++;
			}
		}
		p[i]=num;
	}
	q.push(tot);
	f[tot]=0;
	while(!q.empty())
	{
		int node=q.front();
		q.pop();
		ll pp=quick_pow(n*n-p[node],MOD-2);
		for(int hd=head[node];hd;hd=e[hd].nxt)
		{
			int to=e[hd].to;
			if(d[to]==0)f[node]+=e[hd].p*pp%MOD*(f[to]+n*n*pp%MOD)%MOD;
			else
			{
				d[to]--;
				if(d[to]==0)q.push(to);
			}
		}
		f[node]%=MOD;
	}
	printf("%lld\n",f[1]%MOD);
	return 0;
}
