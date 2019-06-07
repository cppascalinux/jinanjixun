#include<bits/stdc++.h>
#define swkakioi 1
#define ll long long
#define R register
using namespace std;
const int N=60100;
const ll mod=1e9+7;
template <class swkaknoi> inline void read(swkaknoi &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}
int n, hd[N], bianshu, visited[N];
ll ans, dis[N];
struct abc{
	int nxt, to;
	ll val;
}qwq[N*2];
inline void addedg(int lai, int qu, int v)
{
	qwq[++bianshu].nxt=hd[lai];
	qwq[bianshu].to=qu;
	qwq[bianshu].val=v;
	hd[lai]=bianshu;
}
queue <int> q;
inline void bfs(int x)
{
	while(q.size())q.pop();
	dis[x]=0;
	visited[x]=x;
	q.push(x);
	while(q.size())
	{
		int u=q.front(); q.pop();
		for(R int i=hd[u]; i; i=qwq[i].nxt)
		{
			int v=qwq[i].to;
			if(visited[v]!=x)
			{
				visited[v]=x;
				dis[v]=dis[x]+qwq[i].val;
				q.push(v);
			}
		}
	}
}
int main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	read(n);
	for(R int i=1, qa, qb, qc; i<n; i++)read(qa), read(qb), read(qc), addedg(qa, qb, qc), addedg(qb, qa, qc);
	for(R int i=1, qa, qb, qc; i<n; i++)read(qa), read(qb), read(qc), addedg(qa+n, qb+n, qc), addedg(qb+n, qa+n, qc);
	for(R int i=1; i<=n; i++)
	{
		bfs(i);
		bfs(i+n);
		for(R int j=1; j<=n; j++)
			ans=(ans+dis[j]*dis[j+n])%mod;
	}
	cout<<ans;
	return 0;
}
