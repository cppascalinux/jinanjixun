#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
struct edge
{
	int v,nxt;
}e[2000005];
int ch[300005][26],len[300005],f[300005],maxn[300005],minn[300005],las=1;
int cnt=1,h[300005],t=0,n,m;
ll ans=0;
vector<int> g[300005];
void add(int u,int v)
{
	e[++t].v=v;
	e[t].nxt=h[u];
	h[u]=t;
}
void ins(char c)
{
	int v=c-'a';
	int p=las,np=++cnt;
	las=cnt;
	len[np]=len[p]+1;
	//maxn[np]=minn[np]=len[np];
	g[np].push_back(len[np]);
	while(p&&!ch[p][v]) ch[p][v]=np,p=f[p];
	if(!p) f[np]=1;
	else
	{
		int q=ch[p][v];
		if(len[q]==len[p]+1) f[np]=q;
		else
		{
			int nq=++cnt;
			for(int i=0;i<26;i++)
				ch[nq][i]=ch[q][i];
			len[nq]=len[p]+1;
			f[nq]=f[q];
			f[q]=f[np]=nq;
			while(p&&ch[p][v]==q) ch[p][v]=nq,p=f[p];
		}
	}
}
int check(int x,int l)
{
	int ans=1;
	for(int i=1;i<g[x].size();i++)
		if(g[x][i]-g[x][i-1]>l) ans++;
	//printf("check:x=%d,l=%d,ans=%d\n",x,l,ans);
	return ans;
}
void dfs(int u,int fa)
{
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,u);
		for(int i=0;i<(int)(g[v].size());i++)
			g[u].push_back(g[v][i]);
		//minn[u]=min(minn[u],minn[v]);
		//maxn[u]=max(maxn[u],maxn[v]);
	}
	if(u==1) return;
	sort(g[u].begin(),g[u].end());
	int l=len[fa]+1,r=len[u];
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(u,mid)<m) r=mid-1; 
		else l=mid+1;
	}
	int tr=r,tl;
	l=len[fa]+1,r=len[u];
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(u,mid)<=m) r=mid-1; 
		else l=mid+1;
	}
	tl=l;
	/*printf("u=%d,tl=%d,tr=%d,g=",u,tl,tr);
	for(int i=0;i<g[u].size();i++)
		printf("%d ",g[u][i]);
	printf("\n");*/
	if(tl>tr) return;
	ans=ans+tr-tl+1;
	
	//int tlen=maxn[u]-minn[u];
	//if(len[u]<tlen) return;
	//ans=ans+len[u]-max(len[fa]+1,tlen)+1;
	//printf("u=%d,maxn=%d,minn=%d,len=%d,%d,ans=%lld\n",u,maxn[u],minn[u],len[u],len[f[u]],ans);
}
char s[1000005];
int main()
{
	freopen("two.in","r",stdin);
	freopen("two.out","w",stdout);
	memset(minn,0x3f,sizeof(minn));
	memset(maxn,0xcf,sizeof(maxn));
	scanf("%s%d",s+1,&m);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		ins(s[i]);
	/*for(int i=1;i<=cnt;i++)
	{
		printf("i=%d,len=%d,f=%d,ch=",i,len[i],f[i]);
		for(int j=0;j<26;j++)
			if(ch[i][j]!=0)
				printf("<%c,%d> ",j+'a',ch[i][j]);
		printf("\n");
	}*/
	for(int i=2;i<=cnt;i++)
		add(f[i],i),add(i,f[i]);
	dfs(1,0);
	printf("%lld",ans);
	return 0;
}
