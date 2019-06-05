#include<bits/stdc++.h>
#define ll long long
#define R register
#define File ffffile
using namespace std;
const int N=1100;
template <class swktqlaknoi> inline void read(swktqlaknoi &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}

int n, m, color[N], dep[N], fa[N], hd[N], st[N], bianshu, visited[N];
inline int max(int a, int b){return a>b? a:b;}
inline int min(int a, int b){return a<b? a:b;}
queue <int> q;
struct abc{
	int nxt, to;
}qwq[N*2];
inline void addedg(int lai, int qu)
{
	qwq[++bianshu].nxt=hd[lai];
	qwq[bianshu].to=qu;
	hd[lai]=bianshu;
}
inline void modify(int x, int y)
{
	memset(visited, 0, sizeof(visited));
	int tp=color[x];
	while(q.size())q.pop();
	q.push(x);
	color[x]=y;
	visited[x]=1;
	while(q.size())
	{
		int u=q.front(); q.pop();
		if(color[fa[u]]==tp && !visited[fa[u]])
		{
			color[fa[u]]=y;
			visited[fa[u]]=1;
			q.push(fa[u]);
		}
		for(R int i=hd[u]; i; i=qwq[i].nxt)
		{
			int v=qwq[i].to;
			if(color[v]==tp && !visited[v])
			{
				visited[v]=1;
				color[v]=y;
				q.push(v);
			}
		}
	}
}
inline void dfs(int u, int f)
{
	dep[u]=dep[f]+1;
	for(R int i=hd[u]; i; i=qwq[i].nxt)
	{
		int v=qwq[i].to;
		dfs(v, u);
	}
}
inline void faq(int x)
{
	memset(visited, 0, sizeof(visited));
	int tp=color[x], tot=0, maxdep=0, mindep=11451419;
	while(q.size())q.pop();
	q.push(x);
	tot++;
	visited[x]=1;
	maxdep=max(maxdep, dep[x]);
	mindep=min(mindep, dep[x]);
	while(q.size())
	{
		int u=q.front(); q.pop();
		if(color[fa[u]]==tp && !visited[fa[u]])
		{
			q.push(fa[u]);
			visited[fa[u]]=1;
			tot++;
			maxdep=max(maxdep, dep[fa[u]]);
			mindep=min(mindep, dep[fa[u]]);
		}
		for(R int i=hd[u]; i; i=qwq[i].nxt)
		{
			int v=qwq[i].to;
			if(color[v]==tp && !visited[v])
			{
				tot++;
				maxdep=max(maxdep, dep[v]);
				mindep=min(mindep, dep[v]);
				visited[v]=1;
				q.push(v);
			}
		}
	}
	printf("%d %d\n", tot, maxdep-mindep+1);
}
inline void File()
{
	freopen("su.in", "r", stdin);
	freopen("su.out", "w", stdout);
}
int main()
{
	File();
//	freopen("su.out", "w", stdout);
	read(n);
	for(R int i=1; i<=n; i++)read(fa[i]), addedg(fa[i], i);
	dep[0]=-1;
	dfs(1, 0);
	for(R int i=1; i<=n; i++)read(color[i]);
	read(m);
	for(R int o=1, qa, qb, qc; o<=m; o++)
	{
		read(qa), read(qb);
		if(qa==1)
		{
			read(qc);
			color[qb]=qc;
		}
		if(qa==2)
		{
			read(qc);
			modify(qb, qc);
		}
		if(qa==3)
		{
			printf("%d ", color[qb]);
			faq(qb);
		}
	}
	return 0;
}

