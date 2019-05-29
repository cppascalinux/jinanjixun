#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;
#define MAXN 111111
#define ll long long

int read()
{
	int ret=0,neg=1;
	char c=getchar();
	while (c<'0' || c>'9'){
		if (c=='-') neg=-1;
		c=getchar();
	}
	while (c>='0' && c<='9'){
		ret=ret*10+c-'0';
		c=getchar();
	}
	return ret*neg;
}

struct Edge{
	int to,val,next;
};
Edge edge[MAXN<<1];
int toedge[MAXN],ecnt=1;

void eadd(int from,int to,int val)
{
	edge[++ecnt]=(Edge){to,val,toedge[from]};
	toedge[from]=ecnt;
	edge[++ecnt]=(Edge){from,val,toedge[to]};
	toedge[to]=ecnt;
}

int n,m;
int a[MAXN];
ll dis[MAXN];
ll ans;
ll dp[MAXN],pre[MAXN];
ll mid,bgn;
int fa[MAXN];

void dfs(int x)
{
	ll fir=0,sec=0,pos=0;
	for (int i=toedge[x];i;i=edge[i].next){
		int to=edge[i].to;
		if (to==fa[x])continue;
		fa[to]=x;
		dfs(to);
		if (dp[to]+edge[i].val>fir)sec=fir,fir=dp[to]+edge[i].val,pos=i;
		else sec=max(sec,dp[to]+edge[i].val);
	}
	pre[x]=pos;dp[x]=fir;
	if (fir+sec>mid) mid=fir+sec,bgn=x;
}

int sta[MAXN],top;

void neg(int x)
{
	ll fir=0,sec=0,pos=0,pos2=0;
	for (int i=toedge[x];i;i=edge[i].next){
		int to=edge[i].to;
		if (to==fa[x])continue;
		if (dp[to]+edge[i].val>fir)sec=fir,pos2=pos,fir=dp[to]+edge[i].val,pos=i;
		else if (dp[to]+edge[i].val>sec) sec=dp[to]+edge[i].val,pos2=i;
	}
	for (int i=pos;i;i=pre[edge[i].to]) edge[i].val=-edge[i].val;
	for (int i=pos2;i;i=pre[edge[i].to]) edge[i].val=-edge[i].val;
}

priority_queue<int,vector<int>,less<int> > que;

int main()
{
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
	n=read();m=read();
	for (int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		eadd(x,y,z);
		ans+=z;
	}
	ans=ans*2;
	for (int i=1;i<=m;i++) a[i]=read();
	printf("%lld ",ans);
	for (int i=1;i<=m;i++){
		int now=a[i];
		if (!que.empty() && now<que.top()){
			ans-=que.top()-now;
			que.push(now);
			now=que.top();
			que.pop();
		}
		mid=0,bgn=0;
		dfs(1);
		if (mid>now){
			ans-=mid-now;
			neg(bgn);
			que.push(now);
		}
		printf("%lld ",ans);
	}
}
