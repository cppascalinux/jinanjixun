#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
struct edge
{
	int v,w,nxt;
}e[500005];
int n,m,h[100005],t=0,fl=1,ct=1;
ll ans=0,a[100005],c[100005];
priority_queue<int> pq;
bool cmp(const int x,const int y)
{
	return x>y;
}
void add(int u,int v,int w)
{
	e[++t].v=v;
	e[t].w=w;
	e[t].nxt=h[u];
	h[u]=t;
}
int main()
{
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		if(u>v) swap(u,v);
		if(u!=1) fl=0;
		else c[v-1]=w;
		add(u,v,w);
		add(v,u,w);
		ans=ans+2ll*w;
	}
	sort(c+1,c+n,cmp);
	for(int i=1;i<=m;i++)
		scanf("%lld",&a[i]);
	//sort(a+1,a+m+1);
	printf("%lld ",ans);
	for(int i=1;i<=m;i++)
	{
		if(ct+1<n&&c[ct]+c[ct+1]>=a[i])
		{
			ans=ans-c[ct]-c[ct+1]+a[i];
			ct+=2;
			pq.push(a[i]);
		}
		else if(!pq.empty()&&pq.top()>a[i])
		{
			ans=ans-pq.top()+a[i];
			pq.pop();
			pq.push(a[i]);
		}
		while(!pq.empty()&&ct>0&&c[ct]+c[ct+1]<=pq.top())
		{
			ans=ans+c[ct]+c[ct+1]-pq.top();
			ct-=2;
			pq.pop();
		}
		printf("%lld ",ans);
	}
	return 0;
}
