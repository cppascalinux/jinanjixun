#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define pii pair<int,int>
#define fi first
#define se second
#define ppi pair<pii,int>
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,q,tot,tme;
int hd[200009],eg[400009],nxt[400009];
int f[200009][19];
int dep[200009],sz[200009],son[200009],dfn[200009],id[200009],top[200009];
int psm[200009];
int ct[200009];
int lm[800009],rm[800009],cm[800009],lzl[800009],lzr[800009],lzc[800009];
ppi qry[100009];
pii pe[100009];
int ans[100009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs1(int x,int fa)
{
	f[x][0]=fa;
	for(int i=1;i<=18;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	dep[x]=dep[fa]+1;
	sz[x]=1;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			dfs1(eg[i],x);
			sz[x]+=sz[eg[i]];
			if(sz[eg[i]]>sz[son[x]])
				son[x]=eg[i];
		}
}
void dfs2(int x,int t)
{
	top[x]=t;
	dfn[x]=++tme;
	id[tme]=x;
	if(son[x])
		dfs2(son[x],t);
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=son[x]&&eg[i]!=f[x][0])
			dfs2(eg[i],eg[i]);
}
int getlca(int a,int b)
{
	if(dep[a]<dep[b])
		swap(a,b);
	int l=dep[a]-dep[b];
	for(int i=0;i<=18;i++)
		if((l>>i)&1)
			a=f[a][i];
	if(a==b)
		return a;
	for(int i=18;i>=0;i--)
		if(f[a][i]!=f[b][i])
			a=f[a][i],b=f[b][i];
	return f[a][0];
}
void addc(int x,int val)
{
	for(;x;x-=x&-x)
		ct[x]+=val;
}
int askc(int x)
{
	int ans=0;
	for(;x<=n;x+=x&-x)
		ans+=ct[x];
	return ans;
}
void down(int a)
{
	int la=a<<1,ra=a<<1|1;
	if(lzl[a])
	{
		lm[la]=lm[ra]=lzl[a];
		lzl[la]=lzl[ra]=lzl[a];
		lzl[a]=0;
	}
	if(lzr[a])
	{
		rm[la]=rm[ra]=lzr[a];
		lzr[la]=lzr[ra]=lzr[a];
		lzr[a]=0;
	}
	if(lzc[a])
	{
		cm[la]=cm[ra]=lzc[a];
		lzc[la]=lzc[ra]=lzc[a];
		lzc[a]=0;
	}
}
void add(int a,int l,int r,int ll,int rr,int vl,int vr,int vc)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
	{
		if(vl)
			lm[a]=lzl[a]=vl;
		if(vr)
			rm[a]=lzr[a]=vr;
		if(vc)
			cm[a]=lzc[a]=vc;
		return;
	}
	down(a);
	int mid=(l+r)>>1;
	add(a<<1,l,mid,ll,rr,vl,vr,vc);
	add(a<<1|1,mid+1,r,ll,rr,vl,vr,vc);
}
int ask(int a,int l,int r,int pos)
{
	if(l==r)
		return a;
	down(a);
	int mid=(l+r)>>1;
	if(pos<=mid)
		return ask(a<<1,l,mid,pos);
	return ask(a<<1|1,mid+1,r,pos);
}
void chg(int l,int r,int cl)
{
	if(l-1>=1)
	{
		int lp=lm[ask(1,1,n,l-1)];
		add(1,1,n,lp,l-1,0,l-1,0);
	}
	if(r+1<=n)
	{
		int rp=rm[ask(1,1,n,r+1)];
		add(1,1,n,r+1,rp,r+1,0,0);
	}
	int a=ask(1,1,n,l),lp=l,rp=min(r,rm[a]);
	while(lp<=r)
	{
		addc(cm[a],-(psm[rp]-psm[lp-1]));
		addc(cl,psm[rp]-psm[lp-1]);
		lp=rp+1;
		a=ask(1,1,n,lp);
		rp=min(r,rm[a]);
	}
	add(1,1,n,l,r,l,r,cl);
}
void modify(int u,int v,int cl)
{
	int fu=top[u],fv=top[v];
	while(fu!=fv)
	{
		if(dep[fu]>dep[fv])
		{
			chg(dfn[fu],dfn[u],cl);
			u=f[fu][0],fu=top[u];
		}
		else
		{
			chg(dfn[fv],dfn[v],cl);
			v=f[fv][0],fv=top[v];
		}
	}
	if(dfn[u]<=dfn[v])
		chg(dfn[u],dfn[v],cl);
	else
		chg(dfn[v],dfn[u],cl);
}
bool cmp(ppi a,ppi b)
{
	return a.fi.se<b.fi.se;
}
void solve()
{
	for(int i=1;i<=4*n;i++)
		lm[i]=1,rm[i]=n;
	sort(qry+1,qry+q+1,cmp);
	int cur=0;
	for(int i=1;i<=q;i++)
	{
		while(cur<qry[i].fi.se)
			++cur,modify(pe[cur].fi,pe[cur].se,cur);
		ans[qry[i].se]=askc(qry[i].fi.fi);
	}
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
}
void dbg()
{
	for(int i=1;i<=n;i++)
		printf("i:%d sz:%d top:%d f0:%d son:%d\n",i,sz[i],top[i],f[i][0],son[i]);
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	rd(n),rd(m),rd(q);
	for(int i=1,a,b;i<=n-1;i++)
	{
		rd(a),rd(b);
		ins(a,i+n),ins(i+n,a);
		ins(b,i+n),ins(i+n,b);
	}
	n=2*n-1;
	dfs1(1,0);
	dfs2(1,1);
	// dbg();
	for(int i=1;i<=n;i++)
	{
		psm[i]=psm[i-1];
		if(id[i]<=n/2+1)
			psm[i]++;
		else
			psm[i]--;
	}
	for(int i=1;i<=m;i++)
		rd(pe[i].fi),rd(pe[i].se);
	for(int i=1;i<=q;i++)
		rd(qry[i].fi.fi),rd(qry[i].fi.se),qry[i].se=i;
	solve();
	return 0;
}