#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
struct Edge
{
	int to;
	int nxt;
}e[200005];
int n,m,q,edgenum,head[100005],dep[100005],pa[100005],anc[26][100005];
int u[100005],v[100005],lca[100005],dfn[100005],sa[100005],cnt1[100005],cnt2[100005];
int size[100005],son[100005],top[100005],ans[100005];
struct Query
{
	int l,r;
	int id;
}a[100005];
struct Segment_Tree
{
	#define lson o<<1
	#define rson o<<1|1
	#define mid (l+r)/2
	struct Node
	{
		int num;
		bool flag;
	}tree[400005];
	void pushup(int o)
	{
		tree[o].num=tree[lson].num+tree[rson].num;
	}
	void pushdown(int o,int l,int r)
	{
		if(tree[o].flag)
		{
			tree[lson].flag=1;
			tree[rson].flag=1;
			tree[lson].num=mid-l+1;
			tree[rson].num=r-mid;
			tree[o].flag=0;
		}
	}
	int ask()
	{
		return tree[1].num;
	}
	void update(int o,int l,int r,int from,int to)
	{
		if(l>=from&&r<=to)
		{
			tree[o].flag=1;
			tree[o].num=r-l+1;
			return;
		}
		pushdown(o,l,r);
		if(from<=mid)update(lson,l,mid,from,to);
		if(to>mid)update(rson,mid+1,r,from,to);
		pushup(o);
	}
	#undef lson
	#undef rson
	#undef mid
}T1,T2;
void add(int u,int v)
{
	e[++edgenum].to=v;
	e[edgenum].nxt=head[u];
	head[u]=edgenum;
}
int ind;
void dfs(int node)
{
	dfn[node]=++ind;
	dep[node]=dep[pa[node]]+1;
	size[node]=1;
	for(int hd=head[node];hd;hd=e[hd].nxt)
	{
		int to=e[hd].to;
		if(to==pa[node])continue;
		pa[to]=node;
		dfs(to);
		size[node]+=size[to];
		if(size[to]>size[son[node]])son[node]=to;
	}
}
void dfs2(int node,int t)
{
	top[node]=t;
	dfn[node]=++ind;
	if(son[node])dfs2(son[node],t);
	for(int hd=head[node];hd;hd=e[hd].nxt)
	{
		int to=e[hd].to;
		if(to==pa[node]||to==son[node])continue;
		dfs2(to,to);
	}
}
void update(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		T1.update(1,1,n,dfn[top[u]],dfn[u]);
		T2.update(1,1,n,dfn[top[u]],dfn[u]);
		u=pa[top[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	T1.update(1,1,n,dfn[v],dfn[u]);
	if(u!=v)T2.update(1,1,n,dfn[v]+1,dfn[u]);
}
void pre()
{
	for(int i=1;i<=n;i++)anc[0][i]=pa[i];
	for(int i=1;i<=20;i++)
	  for(int j=1;j<=n;j++)
	    anc[i][j]=anc[i-1][anc[i-1][j]];
}
int LCA(int u,int v)
{
	if(dep[u]<dep[v])swap(u,v);
	for(int i=0;dep[u]-dep[v];i++)
	  if((1<<i)&(dep[u]-dep[v]))
	    u=anc[i][u];
	if(u==v)return u;
	for(int i=20;i>=0;i--)
	  if(anc[i][u]!=anc[i][v])
	    u=anc[i][u],v=anc[i][v];
	return pa[u];
}
bool cmp(int a,int b)
{
	return dfn[a]>dfn[b];
}
bool cmp2(Query a,Query b)
{
	return a.r<b.r;
}
int subtask1()
{
	dfs(1);
	pre();
	for(int i=1;i<=n;i++)sa[i]=i;
	sort(sa+1,sa+n+1,cmp);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u[i],&v[i]);
		lca[i]=LCA(u[i],v[i]);
	}
	while(q--)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		for(int i=1;i<=n;i++)cnt1[i]=cnt2[i]=0;
		for(int i=l;i<=r;i++)
		{
			cnt1[u[i]]++,cnt1[v[i]]++,cnt1[lca[i]]--,cnt1[pa[lca[i]]]--;
			cnt2[u[i]]++,cnt2[v[i]]++,cnt2[lca[i]]-=2;
		}
		int num1=0,num2=0;
		for(int i=1;i<=n;i++)
		{
			cnt1[pa[sa[i]]]+=cnt1[sa[i]];
			cnt2[pa[sa[i]]]+=cnt2[sa[i]];
			if(cnt1[sa[i]])num1++;
			if(cnt2[sa[i]])num2++;
		}
		printf("%d\n",num1-num2);
	}
	return 0;
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	if(n<=1000&&m<=1000&&q<=1000)return subtask1();
	dfs(1);
	ind=0;
	dfs2(1,1);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u[i],&v[i]);
		lca[i]=LCA(u[i],v[i]);
	}
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&a[i].l,&a[i].r);
		a[i].id=i;
	}
	sort(a+1,a+q+1,cmp2);
	int now=1;
	for(int i=1;i<=q;i++)
	{
		while(now<=a[i].r)
		{
			update(u[now],v[now]);
			now++;
		}
		ans[a[i].id]=T1.ask()-T2.ask();
	}
	for(int i=1;i<=q;i++)
	  printf("%d\n",ans[i]);
	return 0;
}
