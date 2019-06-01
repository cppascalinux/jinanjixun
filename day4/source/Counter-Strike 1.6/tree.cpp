#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;
const int N=2e5+10;
template <class nmsl> inline void read(nmsl &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}
int fa[N], dep[N], n, m, q, ans, hd[N], bianshu, xi[N], yi[N], father[N], visited[N], lighted[N];
inline void swap(int &a, int &b){int t=a;a=b;b=t;}
struct abc{
	int nxt, to;
}qwq[N];
inline void addedg(int lai, int qu)
{
	qwq[++bianshu].nxt=hd[lai];
	qwq[bianshu].to=qu;
	hd[lai]=bianshu;
}
inline void re_set()
{
	for(R int i=1; i<=n; i++)fa[i]=i, visited[i]=0, lighted[i]=0;
}
inline void dfs(int u, int f)
{
	dep[u]=dep[f]+1; father[u]=f;
	for(R int i=hd[u]; i; i=qwq[i].nxt)
	{
		int v=qwq[i].to;
		if(v==f)continue;
		dfs(v, u);
	}
}
inline int findfa(int x){if(x==fa[x])return x; fa[x]=findfa(fa[x]); return fa[x];}
inline void modify(int x, int y)
{
	while(x!=y)
	{
		if(dep[y]>dep[x])swap(x, y);
		lighted[x]=1;
		fa[findfa(fa[x])]=findfa(father[x]);
		x=father[x];
	}
	lighted[x]=1;
}
int main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	read(n), read(m), read(q);
	for(R int i=1, qa, qb; i<n; i++)read(qa), read(qb), addedg(qa, qb), addedg(qb, qa);
	dfs(1, 0);
	for(R int i=1; i<=m; i++)read(xi[i]), read(yi[i]);
	for(R int o=1, qa, qb; o<=q; o++)
	{
		read(qa), read(qb); ans=0;
		re_set();
		for(R int i=qa; i<=qb; i++)modify(xi[i], yi[i]);
		for(R int i=1; i<=n; i++)
		{
			if(!visited[findfa(i)] && lighted[findfa(i)])ans++;
			visited[findfa(i)]=1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
