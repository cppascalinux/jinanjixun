//2019.06.13
//day7t1 五彩斑斓的世界 将询问离线,按右端点从小到大排序,用树状数组维护每一个长度的连续段的答案
//每次右端点+1,将值域左右各10个数拿出来按上一次出现位置排序,再在树状数组上区间修改,询问时单点查询左端点即可
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define gc() (p1==p2&&(p2=(p1=buf1)+fread(buf1,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define flush() (fwrite(buf2,1,p3-buf2,stdout),p4=(p3=buf2)+10000000)
#define pc(x) (p3==p4&&(flush(),0)?EOF:*p3++=x)
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
char buf1[10000009],buf2[10000009],*p1,*p2,*p3=buf2,*p4=buf2;
struct node
{
	int l,r,id;
	node(){}
	node(int a,int b,int c){l=a,r=b,id=c;}
	bool operator <(const node &p){return r<p.r;}
};
int n,m;
int s[1000009];
int lst[1000009];
int c[11][1000009];
node q[1000009];
int ans[1000009][11];
int f[1000009],sz[1000009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void pt(int x)
{
	if(x>=10)
		pt(x/10);
	pc(x%10+'0');
}
void add(int *c,int x,int val)
{
	for(;x;x-=x&-x)
		c[x]+=val;
}
int ask(int *c,int x)
{
	int ans=0;
	for(;x<=1000000;x+=x&-x)
		ans+=c[x];
	return ans;
}
int fnd(int x)
{
	return x==f[x]?x:f[x]=fnd(f[x]);
}
void mrg(int a,int b)
{
	a=fnd(a),b=fnd(b);
	sz[a]+=sz[b];
	f[b]=a;
}
bool cmp(pii a,pii b)
{
	return a.se>b.se;
}
void cal(int x,int sgn)
{
	// if(!lst[x])
	// 	return;
	pii st[30];
	memset(st,0,sizeof(st));
	int tp=0;
	for(int i=max(1,x-11);i<=min(1000000,x+11);i++)
		if(lst[i])
			st[++tp]=pii(i,lst[i]);
	sort(st+1,st+tp+1,cmp);
	// for(int i=1;i<=tp;i++)
	// 	printf("i:%d fi:%d se:%d\n",i,st[i].fi,st[i].se),fflush(stdout);
	for(int i=1;i<=tp;i++)
	{
		int v=st[i].fi;
		sz[v]=1,f[v]=v;
		if(f[v-1])
		{
			int t=fnd(v-1);
			if(sz[t]>=1&&sz[t]<=10)
				add(c[sz[t]],st[i].se,-sgn);
			mrg(v,v-1);
		}
		if(f[v+1])
		{
			int t=fnd(v+1);
			if(sz[t]>=1&&sz[t]<=10)
				add(c[sz[t]],st[i].se,-sgn);
			mrg(v,v+1);
		}
		int fx=fnd(v);
		if(sz[fx]>=1&&sz[fx]<=10)
			add(c[sz[fx]],st[i].se,sgn);/* add(c[sz[fx]],st[i+1].se,-sgn); */
	}
	for(int i=1;i<=tp;i++)
		f[st[i].fi]=sz[st[i].fi]=0;
}
void solve()
{
	sort(q+1,q+m+1);
	int rp=0;
	for(int i=1;i<=m;i++)
	{
		while(rp<q[i].r)
		{
			rp++;
			cal(s[rp],-1);
			lst[s[rp]]=rp;
			cal(s[rp],1);
		}
		for(int j=1;j<=10;j++)
			ans[q[i].id][j]=ask(c[j],q[i].l)%10+'0';
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=10;j++)
			pc(ans[i][j]);
		pc('\n');
	}
}
int main()
{
	freopen("shinku.in","r",stdin);
	freopen("shinku.out","w",stdout);
	rd(n),rd(m);
	for(int i=1;i<=n;i++)
		rd(s[i]);
	for(int i=1;i<=m;i++)
		rd(q[i].l),rd(q[i].r),q[i].id=i;
	solve();
	flush();
	return 0;
}