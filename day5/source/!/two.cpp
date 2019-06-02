#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
#define rand() (rand()*32768+rand())
using namespace std;
const int INF=2147483647;
int delv[1000005],insv[1000005],top1,top2;
ll ans;
struct Treap
{
	#define lson tree[o].child[0]
	#define rson tree[o].child[1]
	struct Node
	{
		int child[2];
		int size;
		int val,key;
	}tree[1000005];
	int tot,root[1000005];
	int st[1000005],top;
	void debug(int o)
	{
		if(!o)return;
		debug(lson);
		printf("%d ",tree[o].val);
		debug(rson);
	}
	void pushup(int o)
	{
		tree[o].size=tree[lson].size+tree[rson].size+1;
	}
	pair<int,int>split(int o,int v)
	{
		if(!o)return make_pair(0,0);
		pair<int,int>x;
		if(tree[o].val>v)
		{
			x=split(lson,v);
			lson=x.second;
			pushup(o);
			x.second=o;
		}
		else
		{
			x=split(rson,v);
			rson=x.first;
			pushup(o);
			x.first=o;
		}
		return x;
	}
	int merge(int x,int y)
	{
		if(!x||!y)return x+y;
		if(tree[x].key<tree[y].key)
		{
			tree[x].child[1]=merge(tree[x].child[1],y);
			pushup(x);
			return x;
		}
		else
		{
			tree[y].child[0]=merge(x,tree[y].child[0]);
			pushup(y);
			return y;
		}
	}
	void del2(int t,int v)
	{
		pair<int,int>x=split(root[t],v-1),y=split(x.second,v);
		root[t]=merge(merge(x.first,tree[y.first].child[0]),merge(tree[y.first].child[1],y.second));
		st[++top]=y.first;
	}
	void ins2(int t,int v)
	{
		int o=(top?st[top--]:++tot);
		tree[o].val=v;
		tree[o].size=1;
		tree[o].child[0]=tree[o].child[1]=0;
		tree[o].key=rand();
		pair<int,int>x=split(root[t],v);
		root[t]=merge(merge(x.first,o),x.second);
	}
	pair<int,int>ins(int t,int o)
	{
		pair<int,int>x=split(root[t],tree[o].val),res;
		int node=x.first;
		while(tree[node].child[1])node=tree[node].child[1];
		res.first=node;
		node=x.second;
		while(tree[node].child[0])node=tree[node].child[0];
		res.second=node;
		root[t]=merge(merge(x.first,o),x.second);
		return res;
	}
	void dfs(int node,int t)
	{
		if(!node)return;
		dfs(tree[node].child[0],t);
		dfs(tree[node].child[1],t);
		tree[node].child[0]=tree[node].child[1]=0;
		tree[node].size=1;
		pair<int,int>x=ins(t,node);
		if(x.first&&x.second)delv[++top1]=tree[x.second].val-tree[x.first].val;
		if(x.first)insv[++top2]=tree[node].val-tree[x.first].val;
		if(x.second)insv[++top2]=tree[x.second].val-tree[node].val;
	}
	void merge2(int x,int y)
	{
		top1=top2=0;
		if(tree[root[x]].size<tree[root[y]].size)
		{
			dfs(root[x],y);
			root[x]=root[y],root[y]=0;
		}
		else dfs(root[y],x);
	}
	void recycle(int o)
	{
		if(!o)return;
		recycle(lson);
		recycle(rson);
		st[++top]=o;
	}
	void merge3(int x,int y)
	{
		if(tree[root[x]].size<tree[root[y]].size)
		{
			recycle(root[x]);
			root[x]=root[y],root[y]=0;
		}
	}
	int findkth(int o,int k)
	{
		if(k==0)return INF;
		if(k>tree[o].size)return 0;
		if(tree[rson].size==k-1)return tree[o].val;
		if(tree[rson].size>=k)return findkth(rson,k);
		else return findkth(lson,k-tree[rson].size-1);
	}
	#undef lson
	#undef rson
}T1,T2;
struct SAM
{
	int child[26];
	int len;
	int fail;
}tree[500005];
struct Edge
{
	int to;
	int nxt;
}e[500005];
char s[500005];
int n,m,edgenum,tot,last,k,pos[500005],head[500005];
void ins(int i)
{
	char c=s[i];
	int now=++tot;
	pos[i]=now;
	int node=last;
	tree[now].len=tree[node].len+1;
	while(node!=-1&&!tree[node].child[c-'a'])
	{
		tree[node].child[c-'a']=now;
		node=tree[node].fail;
	}
	if(node==-1)tree[now].fail=0;
	else
	{
		int cur=tree[node].child[c-'a'];
		if(tree[cur].len==tree[node].len+1)tree[now].fail=cur;
		else
		{
			int clone=++tot;
			tree[clone]=tree[cur];
			tree[clone].len=tree[node].len+1;
			while(node!=-1&&tree[node].child[c-'a']==cur)
			{
				tree[node].child[c-'a']=clone;
				node=tree[node].fail;
			}
			tree[now].fail=tree[cur].fail=clone;
		}
	}
	last=now;
}
void add(int u,int v)
{
	e[++edgenum].to=v;
	e[edgenum].nxt=head[u];
	head[u]=edgenum;
}
void dfs(int node)
{
//	printf("dfs %d:\n",node);
	for(int hd=head[node];hd;hd=e[hd].nxt)
	{
		int to=e[hd].to;
		dfs(to);
//		printf("back %d,merge(%d,%d)\n",node,node,to);
		T1.merge2(node,to);
		T2.merge3(node,to);
//		printf("delv:");
//		for(int i=1;i<=top1;i++)printf("%d ",delv[i]);
//		printf("\n");
//		printf("insv:");
//		for(int i=1;i<=top2;i++)printf("%d ",insv[i]);
//		printf("\n");
		for(int i=1;i<=top2;i++)T2.ins2(node,insv[i]);
		for(int i=1;i<=top1;i++)T2.del2(node,delv[i]);
	}
//	printf("  s:");
//	T1.debug(T1.root[node]);
//	printf("\n");
//	printf("  dis:");
//	T2.debug(T2.root[node]);
//	printf("\n");
	if(T1.tree[T1.root[node]].size>=k)
	{
		int l=T2.findkth(T2.root[node],k);
		int r=T2.findkth(T2.root[node],k-1)-1;
		int L=tree[tree[node].fail].len+1;
		int R=tree[node].len;
//		printf("  [%d,%d],[%d,%d]\n",l,r,L,R);
		ans+=max(0,min(r,R)-max(l,L)+1);
	}
}
int main()
{
	freopen("two.in","r",stdin);
	freopen("two.out","w",stdout);
	tree[0].fail=-1;
	scanf("%s",s+1);
	n=(int)strlen(s+1);
	for(int i=1;i<=n/2;i++)
	  swap(s[i],s[n-i+1]);
	scanf("%d",&k);
	for(int i=1;i<=n;i++)ins(i);
	for(int i=1;i<=n/2;i++)swap(pos[i],pos[n-i+1]);
	for(int i=1;i<=tot;i++)add(tree[i].fail,i);
	for(int i=1;i<=n;i++)
	{
		T1.tree[i].val=i;
		T1.tree[i].size=1;
		T1.tree[i].key=rand();
		T1.root[pos[i]]=i;
//		printf("pos[%d]=%d\n",i,pos[i]);
	}
//	for(int i=1;i<=tot;i++)
//	{
//		printf("%d:",i);
//		T1.debug(T1.root[i]);
//		printf("\n");
//	}
	dfs(0);
	printf("%lld\n",ans);
	return 0;
}
