#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
namespace abc
{
	struct edge
	{
		int v,nxt;
	}e[500005],e1[5000005];
	int n,m,h[100005],h1[100005],t,t1,size[100005],dfn[100005],tp[100005],son[100005];
	int d[100005],udfn[100005],f[100005],cnt=0,head,tail,q[1000005],qn;
	int sum[1000005],lazy[1000005],vis[1000005],a[100005][2];
	void add(int u,int v)
	{
		e[++t].v=v;
		e[t].nxt=h[u];
		h[u]=t;
	}
	void add1(int u,int v)
	{
		//printf("u=%d,v=%d\n",u,v);
		e1[++t1].v=v;
		e1[t1].nxt=h1[u];
		h1[u]=t1;
	}
	void dfs1(int u,int fa,int dep)
	{
		f[u]=fa;
		d[u]=dep;
		size[u]=1;
		son[u]=0;
		for(int i=h[u];i;i=e[i].nxt)
		{
			int v=e[i].v;
			if(v==fa) continue;
			dfs1(v,u,dep+1);
			size[u]+=size[v];
			if(size[son[u]]<size[v]) son[u]=v;
		}
	}
	void dfs2(int u,int ttp)
	{
		dfn[u]=++cnt;
		udfn[cnt]=u;
		tp[u]=ttp;
		if(son[u]) dfs2(son[u],ttp);
		for(int i=h[u];i;i=e[i].nxt)
		{
			int v=e[i].v;
			if(v==f[u]||v==son[u]) continue;
			dfs2(v,v);
		}
	}
	void pushup(int x)
	{
		sum[x]=sum[x*2]+sum[x*2+1];
	}
	void col(int x,int l,int r,int v)
	{
		lazy[x]+=v;
		sum[x]+=(r-l+1)*v;
	}
	void pushdown(int x,int l,int r)
	{
		if(lazy[x])
		{
			int mid=(l+r)/2;
			col(x*2,l,mid,lazy[x]);
			col(x*2+1,mid+1,r,lazy[x]);
			lazy[x]=0;
		}
	}
	void modify(int x,int l,int r,int ql,int qr,int v)
	{
		if(l>qr||r<ql) return;
		if(ql<=l&&r<=qr)
		{
			col(x,l,r,v);
			return;
		}
		int mid=(l+r)/2;
		pushdown(x,l,r);
		modify(x*2,l,mid,ql,qr,v);
		modify(x*2+1,mid+1,r,ql,qr,v);
		pushup(x);
	}
	int query(int x,int l,int r,int ql,int qr)
	{
		if(l>qr||r<ql) return 0;
		if(ql<=l&&r<=qr) return sum[x];
		int mid=(l+r)/2,q1,q2;
		pushdown(x,l,r);
		q1=query(x*2,l,mid,ql,qr);
		q2=query(x*2+1,mid+1,r,ql,qr);
		return q1+q2;
	}
	void tmodify(int u,int v,int w)
	{
		while(tp[u]!=tp[v])
		{
			if(d[tp[u]]<d[tp[v]]) swap(u,v);
			modify(1,1,n,dfn[tp[u]],dfn[u],w);
			u=f[tp[u]];
		}
		if(dfn[u]>dfn[v]) swap(u,v);
		modify(1,1,n,dfn[u],dfn[v],w);
	}
	int tquery(int u,int v)
	{
		int ans=0;
		while(tp[u]!=tp[v])
		{
			if(d[tp[u]]<d[tp[v]]) swap(u,v);
			ans+=query(1,1,n,dfn[tp[u]],dfn[u]);
			u=f[tp[u]];
		}
		if(dfn[u]>dfn[v]) swap(u,v);
		ans=ans+query(1,1,n,dfn[u],dfn[v]);
		return ans;
	}
	void bfs(int s,int l,int r)
	{
		head=0,tail=1;
		q[1]=s;
		vis[s]=1;
		while(head<tail)
		{
			head++;
			int u=q[head];
			for(int i=h1[u];i;i=e1[i].nxt)
			{
				int v=e1[i].v;
				if(vis[v]||v<l||v>r) continue;
				vis[v]=1;
				q[++tail]=v;
			}
		}
	}
	/*void print(int x,int l,int r)
	{
		printf("x=%d,l=%d,r=%d,sum=%d,lazy=%d\n",x,l,r,sum[x],lazy[x]);
		if(l==r) return;
		int mid=(l+r)/2;
		print(x*2,l,mid);
		print(x*2+1,mid+1,r);
	}*/
	void soe()
	{
		freopen("tree.in","r",stdin);
		freopen("tree.out","w",stdout);
		scanf("%d%d%d",&n,&m,&qn);
		for(int i=1;i<n;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			add(u,v);
			add(v,u);
		}
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&a[i][0],&a[i][1]);
		}
		dfs1(1,0,0);
		dfs2(1,1);
		for(int i=1;i<=m;i++)
		{
			tmodify(a[i][0],a[i][1],1);
			//printf("i=%d,u=%d,v=%d\n",i,a[i][0],a[i][1]);
			//print(1,1,n);
			for(int j=i+1;j<=m;j++)
			{
				if(tquery(a[j][0],a[j][1]))
				{
					//printf("----");
					add1(i,j);
					add1(j,i);
				}
			}
			tmodify(a[i][0],a[i][1],-1);
		}
		for(int i=1;i<=qn;i++)
		{
			int l,r,ans=0;
			scanf("%d%d",&l,&r);
			for(int i=1;i<=m;i++)
				vis[i]=0;
			for(int j=l;j<=r;j++)
			{
				if(!vis[j])
				{
					ans++;
					bfs(j,l,r);
				}
			}
			printf("%d\n",ans);
		}
	}
}
int main()
{
	abc::soe();
	return 0;
}
