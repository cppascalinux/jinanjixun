//2019.06.11
//D10T3 tree 点分治+虚树dp 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
#define li long long
#define mod 1000000007
#define inf 0x7F7F7F7F
#define cal(a,b) (dep[a]<dep[b]?a:b)
using namespace std;
int n,tot1,tot2,tme,cnt,mn,rt,ans;
int hd1[100009],eg1[200009],nxt1[200009],len1[200009];
int hd2[100009],eg2[200009],nxt2[200009],len2[200009];
int pos[100009],dis[100009];
int f[19][200009],lg[200009];
int dfn[100009],dep[100009];
int sz[100009],vis[100009];
int ld1[100009],ont[100009],st[100009];
int smd[100009],nsz[100009];
vector<pii> qry;
vector<int> g[100009];
void ins1(int a,int b,int c)
{
	eg1[++tot1]=b;
	len1[tot1]=c;
	nxt1[tot1]=hd1[a];
	hd1[a]=tot1;
}
void ins2(int a,int b,int c)
{
	eg2[++tot2]=b;
	len2[tot2]=c;
	nxt2[tot2]=hd2[a];
	hd2[a]=tot2;
}
void dfs2(int x,int fa)
{
	dfn[x]=++tme;
	f[0][++cnt]=x,pos[x]=cnt;
	dep[x]=dep[fa]+1;
	for(int i=hd2[x];i;i=nxt2[i])
		if(eg2[i]!=fa)
		{
			dis[eg2[i]]=(dis[x]+len2[i])%mod;
			dfs2(eg2[i],x);
			f[0][++cnt]=x;
		}
}
void initlca()
{
	for(int k=1;k<=18;k++)
		for(int i=1;i<=cnt-(1<<k)+1;i++)
			f[k][i]=cal(f[k-1][i],f[k-1][i+(1<<(k-1))]);
	for(int i=2;i<=cnt;i++)
		lg[i]=lg[i>>1]+1;
}
int getlca(int a,int b)
{
	a=pos[a],b=pos[b];
	if(a>b)
		swap(a,b);
	int k=lg[b-a+1];
	return cal(f[k][a],f[k][b-(1<<k)+1]);
}
void getrt(int x,int fa,int siz)
{
	sz[x]=1;
	int mx=0;
	for(int i=hd1[x];i;i=nxt1[i])
		if(!vis[eg1[i]]&&eg1[i]!=fa)
		{
			getrt(eg1[i],x,siz);
			mx=max(mx,sz[eg1[i]]);
			sz[x]+=sz[eg1[i]];
		}
	mx=max(mx,siz-sz[x]);
	if(mx<mn)
		mn=mx,rt=x;
}
void dfs1(int x,int fa,int l)
{
	ld1[x]=l;
	// ont[x]=1;
	qry.push_back(pii(dfn[x],x));
	for(int i=hd1[x];i;i=nxt1[i])
		if(!vis[eg1[i]]&&eg1[i]!=fa)
			dfs1(eg1[i],x,(l+len1[i])%mod);
}
void dfs3(int x,int fa,int nrt)
{
	nsz[x]=ont[x];
	// printf("nrt:%d x:%d ont:%d\n",nrt,x,ont[x]);
	if(ont[x])
		smd[nrt]=((li)smd[nrt]+dis[x]-dis[nrt]+mod)%mod;
	for(int i=0;i<(int)g[x].size();i++)
		if(g[x][i]!=fa)
		{
			dfs3(g[x][i],x,nrt);
			nsz[x]+=nsz[g[x][i]];
		}
}
void dfs4(int x,int fa,int siz)
{
	for(int i=0;i<(int)g[x].size();i++)
		if(g[x][i]!=fa)
		{
			smd[g[x][i]]=(smd[x]+(li)(dis[g[x][i]]-dis[x]+mod)*(siz-2*nsz[g[x][i]]+mod))%mod;
			dfs4(g[x][i],x,siz);
		}
	g[x].clear();
	ont[x]=0;
}
int getans(int x,int l)
{
	qry.clear();
	dfs1(x,0,l);
	if((int)qry.size()<=1)
		return 0;
	sort(qry.begin(),qry.end());
	int tp=0,nrt=0;
	for(int i=0;i<(int)qry.size();i++)
	{
		int p=qry[i].se,lca=getlca(p,st[tp]);
		while(tp>1&&dfn[lca]<=dfn[st[tp-1]])
		{
			nrt=st[tp-1];
			g[st[tp-1]].push_back(st[tp]);
			tp--;
		}
		if(st[tp]!=lca)
		{
			nrt=lca;
			g[lca].push_back(st[tp]);
			st[tp]=lca;
		}
		st[++tp]=p;
	}
	while(tp>1)
	{
		nrt=st[tp-1];
		g[st[tp-1]].push_back(st[tp]);
		tp--;
	}
	// printf("x:%d qry.size:%d nrt:%d\n",x,(int)qry.size(),nrt);
	smd[nrt]=0;
	for(int i=0;i<(int)qry.size();i++)
		ont[qry[i].se]=1;
	dfs3(nrt,0,nrt);
	dfs4(nrt,0,qry.size());
	int ret=0;
	for(int i=0;i<(int)qry.size();i++)
	{
		int p=qry[i].se;
		// printf("p:%d ld1:%d smd:%d\n",p,ld1[p],smd[p]);
		ret=(ret+(li)ld1[p]*smd[p])%mod;
	}
	// for(int i=0;i<(int)qry.size();i++)
	// 	ont[qry[i].se]=0;
	return ret*2%mod;
} 
void solve(int x,int siz)
{
	vis[x]=1;
	int t=getans(x,0);
	// printf("x:%d siz:%d t:%d\n",x,siz,t);
	ans=(ans+t)%mod;
	for(int i=hd1[x];i;i=nxt1[i])
		if(!vis[eg1[i]])
		{
			ans=(mod+ans-getans(eg1[i],len1[i]))%mod;
			mn=inf;
			int nsz=sz[eg1[i]]>sz[x]?siz-sz[x]:sz[eg1[i]];
			getrt(eg1[i],0,nsz);
			solve(rt,nsz);
		}
}
void dbg()
{
	for(int i=1;i<=n;i++)
		printf("i:%d dfn:%d pos:%d dep:%d dis:%d\n",i,dfn[i],pos[i],dep[i],dis[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			printf("i:%d j:%d lca:%d\n",i,j,getlca(i,j));
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,a,b,c;i<=n-1;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		ins1(a,b,c),ins1(b,a,c);
	}
	for(int i=1,a,b,c;i<=n-1;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		ins2(a,b,c),ins2(b,a,c);
	}
	dfs2(1,0);
	initlca();
	// dbg();
	mn=inf;
	getrt(1,0,n);
	solve(rt,n);
	printf("%d",ans);
	return 0;
}