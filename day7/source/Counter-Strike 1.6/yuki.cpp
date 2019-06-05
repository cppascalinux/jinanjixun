#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;
const int N=1000010;
template <class swktqlaknoi> inline void read(swktqlaknoi &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}
int hd[N], n, m, fa[N], bianshu, dep[N];
ll val[N], st[N];
inline void swap(int &a, int &b){int t=a;a=b;b=t;}
struct abc{
	int nxt, to;
}qwq[N*2];
bool cmp(ll a, ll b){return a<b;}
inline void addedg(int lai, int qu)
{
	qwq[++bianshu].nxt=hd[lai];
	qwq[bianshu].to=qu;
	hd[lai]=bianshu;
}
inline void dfs(int u, int f)
{
	dep[u]=dep[f]+1;
	for(R int i=hd[u]; i; i=qwq[i].nxt)
	{
		int v=qwq[i].to;
		if(v==f)continue;
		dfs(v, u);
	}
}
inline void modify(int x, int y, int v)
{
	while(x!=y)
	{
		if(dep[x]<dep[y])swap(x, y);
		val[x]+=v;
		x=fa[x];
	}
	val[x]+=v;
	return;
}
int main()
{
	freopen("yuki.in", "r", stdin);
	freopen("yuki.out", "w", stdout);
	read(n), read(m);
	for(R int i=1; i<=n; i++)read(val[i]);
	for(R int i=1, qa, qb; i<n; i++)read(qa), read(qb), addedg(qa, qb), addedg(qb, qa);
	dfs(1, 0);
	for(R int o=1, qa, qb, qc, qd; o<=m; o++)
	{
		read(qa), read(qb), read(qc);
		if(qa==1)
		{
			read(qd);	
			modify(qb, qc, qd);
		}	
		else 
		{
			int tp=0;
			if(fa[qb])st[++tp]=val[fa[qb]];
			st[++tp]=val[qb];
			for(R int i=hd[qb]; i; i=qwq[i].nxt)
			{
				int v=qwq[i].to;
				if(v==fa[qb])continue;
				st[++tp]=val[v];
			}
			sort(st+1, st+tp+1, cmp);		
			printf("%lld\n", st[qc]);
		}
	}	
	return 0;
}
