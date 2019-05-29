#include<set>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
namespace abc
{
	struct pt
	{
		int l,r,c,id;
		bool operator <(pt x) const
		{
			return l==x.l?r<x.r:l<x.l;
		}
		bool operator ==(pt x) const
		{
			return l==x.l&&r==x.r;
		}
		pt(int l=0,int r=0,int c=0,int id=0):l(l),r(r),c(c),id(id){}
	}a[100005];
	struct edge
	{
		int v,nxt;
	}e[500005];
	int n,m,fl=0,sum[100005],vis[100005],b[100005],len,bt=0,t=0,h[100005],tt=0;
	pt tid[100005];
	int qans[100005];
	multiset<pt> st[100005];
	void add(int u,int v)
	{
		//printf("<%d,%d>\n",u,v);
		e[++t].v=v;
		e[t].nxt=h[u];
		h[u]=t;
	}
	int check()
	{
		for(int i=0;i<=len;i++)
			vis[i]=0;
		for(int i=1;i<=tt;i++)
		{
			pt u=tid[i];
			if(u.c==0)
			{
				vis[u.l]++;
				vis[u.r+1]--;
			}
			else
			{
				vis[u.l]--;
				vis[u.r+1]++;
			}
		}
		/*printf("c=");
		for(int i=1;i<=tt;i++)
			printf("%d ",tid[i].c);
		printf("\nvis=");
		for(int i=1;i<=len;i++)
			printf("%d ",vis[i]);
		printf("\n");*/
		for(int i=1;i<=len;i++)
		{
			vis[i]+=vis[i-1];
			if(vis[i]>1||vis[i]<-1) return 0;
		}
		return 1;
	}
	void dfs(int dep)
	{
		if(fl==1) return;
		if(dep==tt+1)
		{
			if(check()) fl=1;
			return;
		}
		if(tid[dep].c!=-1)
		{
			dfs(dep+1);
			return;
		}
		tid[dep].c=1;
		dfs(dep+1);
		if(fl) return;
		tid[dep].c=0;
		dfs(dep+1);
		if(fl) return;
		//printf("---");
		tid[dep].c=-1;
	}
	void change(int nw)
	{
		while(st[nw].size()>1u)
		{
			pt x=(*st[nw].begin()),y;
			st[nw].erase(st[nw].begin());
			y=(*st[nw].begin());
			st[nw].erase(st[nw].begin());
			if(x.r==y.r) 
			{
				add(x.id,y.id);
				add(y.id,x.id);
				continue;
			}
			if(x.r>y.r) swap(x,y);
			y.l=x.r+1;
			add(x.id,y.id);
			add(y.id,x.id);
			st[y.l].insert(y);
		}
	}
	void getans(int u,int fa)
	{
		for(int i=h[u];i;i=e[i].nxt)
		{
			int v=e[i].v;
			if(v==fa) continue;
			qans[v]=qans[u]^1;
			getans(v,u);
		}
	}
	void soe()
	{
		freopen("wait.in","r",stdin);
		freopen("wait.out","w",stdout);
		scanf("%d%d",&m,&n);
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].c),a[i].id=i;
			b[++bt]=a[i].l;
			b[++bt]=a[i].r;
		}
		if(m<=20)
		{
			sort(b+1,b+bt+1);
			len=unique(b+1,b+bt+1)-b-1;
			for(int i=1;i<=m;i++)
			{
				a[i].l=lower_bound(b+1,b+len+1,a[i].l)-b;
				a[i].r=lower_bound(b+1,b+len+1,a[i].r)-b;
			}
			tt=m;
			for(int i=1;i<=m;i++)
				tid[i]=a[i];
			dfs(1);
			if(fl)
			{
				for(int i=1;i<=m;i++)
					printf("%d ",tid[i].c);
			}
			else printf("-1");
			return;
		}
		len=20;
		for(int i=1;i<=m;i++)
			st[a[i].l].insert(a[i]);
		//printf("-----");
		for(int i=1;i<=len;i++)
		{
			change(i);
			/*change(i+1);
			if((!st[i].empty())&&(!st[i+1].empty()))
			{
				pt x=*st[i].begin(),y=*st[i+1].begin();
				if(x.r>=y.r)
				{
					st[i].erase(st[i].begin());
					st[i].insert(pt())
				}
			}*/
			if(!st[i].empty()) 
			{
				tid[++tt]=(*st[i].begin());
				//printf("tt=%d,l=%d,r=%d,c=%d,id=%d\n",tt,tid[tt].l,tid[tt].r,tid[tt].c,tid[tt].id);
			}
		}
		dfs(1);
		if(!fl)
		{
			printf("-1");
			return;
		}
		memset(qans,-1,sizeof(qans));
		for(int i=1;i<=tt;i++)
		{
			qans[tid[i].id]=tid[i].c;
			getans(tid[i].id,0);
		}
		for(int i=1;i<=m;i++)
		{
			if(qans[i]==-1)
			{
				qans[i]=0;
				getans(i,0);
			}
		}
		//for(int i=1;i<=m;i++)
		//	qans[a[i].id]=a[i].c;
		for(int i=1;i<=m;i++)
			printf("%d ",qans[i]);
	}
}
int main()
{
	abc::soe();
	return 0;
}
