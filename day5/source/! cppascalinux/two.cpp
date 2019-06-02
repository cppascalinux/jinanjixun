#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cstdlib>
#include<vector>
#include<cassert>
#include<ctime>
#define li long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,m,tot,cnt=1,lst=1,sme;
li ans;
char s[100009];
int o[200009][27],len[200009],lnk[200009],endp[200009],sum[200009];
int rt[200009],rnd[5000009],ch[5000009][2],v[5000009],sz[5000009],rep[5000009];
int hd[200009],eg[200009],nxt[200009];
int son[200009];
set<int> sb[200009];
vector<int> vb[200009];
void add(int c,int pos)
{
	int cur=++cnt,p;
	len[cur]=len[lst]+1;
	sum[cur]=1;
	endp[cur]=pos;
	for(p=lst;p&&!o[p][c];p=lnk[p])
		o[p][c]=cur;
	if(!p)
		lnk[cur]=1;
	else
	{
		int q=o[p][c];
		if(len[q]==len[p]+1)
			lnk[cur]=q;
		else
		{
			int cln=++cnt;
			len[cln]=len[p]+1;
			lnk[cln]=lnk[q];
			memcpy(o[cln],o[q],27<<2);
			for(;p&&o[p][c]==q;p=lnk[p])
				o[p][c]=cln;
			lnk[q]=lnk[cur]=cln;
		}
	}
	lst=cur;
}
void upd(int p)
{
	sz[p]=sz[ch[p][0]]+sz[ch[p][1]]+rep[p];
}
void rot(int &p,int d)
{
	int q=ch[p][d];
	ch[p][d]=ch[q][d^1];
	ch[q][d^1]=p;
	upd(p);
	upd(p=q);
}
void ins(int &p,int val)
{
	if(!p)
	{
		p=++tot;
		rnd[p]=rand();
		v[p]=val;
		rep[p]=sz[p]=1;
	}
	else if(v[p]==val)
		rep[p]++,sz[p]++;
	else
	{
		int d=val>v[p];
		ins(ch[p][d],val);
		if(rnd[ch[p][d]]>rnd[p])
			rot(p,d);
	}
	upd(p);
}
void del(int &p,int val)
{
	if(v[p]==val)
	{
		if(rep[p]>1)
			rep[p]--;
		else if(!ch[p][0]||!ch[p][1])
			p=ch[p][0]+ch[p][1];
		else
		{
			int d=rnd[ch[p][1]]>rnd[ch[p][0]];
			rot(p,d);
			del(ch[p][d^1],val);
		}
	}
	else
	{
		int d=val>v[p];
		del(ch[p][d],val);
	}
	upd(p);
}
int rnk(int p,int val)
{
	if(!p||v[p]==val)
		return sz[ch[p][0]]+1;
	if(val<v[p])
		return rnk(ch[p][0],val);
	return rnk(ch[p][1],val)+sz[ch[p][0]]+rep[p];
}
int kth(int p,int k)
{
	assert(k>=1&&k<=sz[p]);
	int lsz=sz[ch[p][0]];
	if(k>=lsz+1&&k<=lsz+rep[p])
		return p;
	if(k<=lsz)
		return kth(ch[p][0],k);
	return kth(ch[p][1],k-lsz-rep[p]);
}
void adde(int a,int b)
{
	eg[++sme]=b;
	nxt[sme]=hd[a];
	hd[a]=sme;
}
void dfs1(int x)
{
	for(int i=hd[x];i;i=nxt[i])
	{
		dfs1(eg[i]);
		sum[x]+=sum[eg[i]];
		if(sum[eg[i]]>sum[son[x]])
			son[x]=eg[i];
	}
}
void dbg(int p)
{
	printf("p:%d v:%d rep:%d sz:%d\n",p,v[p],rep[p],sz[p]);
	if(ch[p][0])
		dbg(ch[p][0]);
	if(ch[p][1])
		dbg(ch[p][1]);
}
int dfs2(int x)
{
	int cur=x;
	if(son[x])
		cur=dfs2(son[x]);
	set<int>::iterator it1,it2,it3;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=son[x])
		{
			int t=dfs2(eg[i]);
			for(int j=0;j<(int)vb[t].size();j++)
			{
				vb[cur].push_back(vb[t][j]);
				it1=it2=it3=sb[cur].insert(vb[t][j]).fi;
				int n1=0,n3=0;
				if(it1!=sb[cur].begin())
					it1--,n1=1;
				it3++;
				if(it3!=sb[cur].end())
					n3=1;
				if(n1&&n3)
					del(rt[cur],*it3-*it1);
				if(n1)
					ins(rt[cur],*it2-*it1);
				if(n3)
					ins(rt[cur],*it3-*it2);
			}
		}
	if(endp[x])
	{
		vb[cur].push_back(endp[x]);
		it1=it2=it3=sb[cur].insert(endp[x]).fi;
		int n1=0,n3=0;
		if(it1!=sb[cur].begin())
			it1--,n1=1;
		it3++;
		if(it3!=sb[cur].end())
			n3=1;
		if(n1&&n3)
			del(rt[cur],*it3-*it1);
		if(n1)
			ins(rt[cur],*it2-*it1);
		if(n3)
			ins(rt[cur],*it3-*it2);
	}
	if(x>1)
	{
		int ml=len[lnk[x]]+1,mr=len[x]+1;
		if(m>sum[x])
			ml=mr=0;
		else
		{
			int dt=sum[x]-m;
			if(dt>=1)
				ml=max(ml,v[kth(rt[cur],dt)]);
			if(dt+1<=sum[x]-1)
				mr=min(mr,v[kth(rt[cur],dt+1)]);
		}
		// printf("x:%d ml:%d mr:%d sum:%d----------------------------\n",x,ml,mr,sum[x]);
		// for(it1=sb[cur].begin();it1!=sb[cur].end();it1++)
		// 	printf("%d ",*it1);
		// printf("\n");
		// dbg(rt[cur]);
		ans+=max(mr-ml,0);
	}
	return cur;
}
int main()
{
	freopen("two.in","r",stdin);
	freopen("two.out","w",stdout);
	scanf("%s%d",s+1,&m);
	if(m==0)
		return printf("0"),0;
	// printf("m:%d\n",m);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		add(s[i]-'a'+1,i);
	for(int i=2;i<=cnt;i++)
		adde(lnk[i],i);
	dfs1(1);
	// for(int i=1;i<=cnt;i++)
	// 	printf("i:%d len:%d lnk:%d endp:%d sum:%d\n",i,len[i],lnk[i],endp[i],sum[i]);
	dfs2(1);
	printf("%lld",ans);
	cerr<<clock();
	return 0;
}
