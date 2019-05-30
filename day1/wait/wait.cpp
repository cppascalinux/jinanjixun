//2019.05.29
//有若干个区间,进行黑白染色,使得每个点被黑区间和白区间覆盖次数差绝对值<=1
//从区间左端点向右端点连边,转化成混合图欧拉回路,用网络流解决
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define inf 0x7F7F7F7F
using namespace std;
int n,m,tot=1;
int l[30009],r[30009],w[30009];
int v[60009];
int deg[60009];
int hd[60009],eg[300009],nxt[300009],cap[300009],id[300009];
int dep[60009],cur[60009];
void ins(int a,int b,int c,int d)
{
	eg[++tot]=b;
	cap[tot]=c;
	id[tot]=d;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void init()
{
	n=0;
	for(int i=1;i<=m;i++)
		v[++n]=l[i],v[++n]=r[i];
	sort(v+1,v+n+1);
	n=unique(v+1,v+n+1)-v-1;
	for(int i=1;i<=m;i++)
	{
		l[i]=lower_bound(v+1,v+n+1,l[i])-v;
		r[i]=lower_bound(v+1,v+n+1,r[i])-v;
	}
	n++;
}
int bfs(int s,int t)
{
	memset(dep,0,sizeof(dep));
	dep[s]=1;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=hd[x];i;i=nxt[i])
			if(!dep[eg[i]]&&cap[i])
			{
				dep[eg[i]]=dep[x]+1;
				q.push(eg[i]);
			}
	}
	return dep[t];
}
int dfs(int x,int t,int a)
{
	if(x==t||!a)
		return a;
	int f,totf=0;
	for(int &i=cur[x];i;i=nxt[i])
		if(cap[i]&&dep[eg[i]]==dep[x]+1&&(f=dfs(eg[i],t,min(cap[i],a))))
		{
			cap[i]-=f;
			cap[i^1]+=f;
			a-=f;
			totf+=f;
			if(!a)
				break;
		}
	return totf;
}
int flow(int s,int t)
{
	int totf=0;
	while(bfs(s,t))
	{
		for(int i=1;i<=n+2;i++)
			cur[i]=hd[i];
		totf+=dfs(s,t,inf);
	}
	return totf;
}
int adde()
{
	for(int i=1;i<=m;i++)
		if(w[i]!=1)
			deg[l[i]]++,deg[r[i]+1]--;
		else
			deg[r[i]+1]++,deg[l[i]]--;
	for(int i=1;i<=m;i++)
		if(w[i]==-1)
			ins(l[i],r[i]+1,1,i),ins(r[i]+1,l[i],0,i);
	int lst=0;
	for(int i=1;i<=n;i++)
		if(deg[i]%2!=0)
		{
			if(!lst)
				lst=i;
			else
			{
				ins(lst,i,1,0),ins(i,lst,0,0);
				deg[lst]++,deg[i]--;
				lst=0;
			}
		}
	if(lst)
		return printf("-1"),0;
	int s=n+1,t=n+2;
	for(int i=1;i<=n;i++)
		if(deg[i]>0)
			ins(s,i,deg[i]/2,0);
		else
			ins(i,t,-deg[i]/2,0);
	return 1;
}
void solve()
{
	int s=n+1,t=n+2;
	int f=flow(n+1,n+2);
	for(int i=hd[s];i;i=nxt[i])
		if(cap[i])
			return printf("-1"),void();
	for(int i=1;i<=n;i++)
		for(int j=hd[i];j;j=nxt[j])
			if(cap[j])
			{
				if(eg[j]>i)
					w[id[j]]=0;
				else
					w[id[j]]=1;
			}
	for(int i=1;i<=m;i++)
		printf("%d ",w[i]);
}
int main()
{
	freopen("wait.in","r",stdin);
	freopen("wait.out","w",stdout);
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",l+i,r+i,w+i);
	init();
	if(adde())
		solve();
	return 0;
}