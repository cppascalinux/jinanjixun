#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int N=1002018;
int n,m,zong,tot;
int mxb[N],dis[N],id[N],mxid[N],mxp[N],secp[N],seb[N],dt[N],secid[N],aa[N],v[N],b[N];
struct Edge{int to,next,data;}e[N<<1];
void add_edge(int x,int y,int z){
	e[++tot].to=y; e[tot].data=z;
	e[tot].next=v[x]; v[x]=tot;
}
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void dfs(int x,int fa){
	for(int p=v[x];p;p=e[p].next){
		int kp=e[p].to;
		if(kp!=fa){
			dis[kp]=e[p].data; id[kp]=p;
			dfs(kp,x);
			if(mxb[x]<=mxb[kp]+dis[kp]){
				seb[x]=mxb[x],secp[x]=mxp[x],secid[x]=mxid[x];
				mxb[x]=mxb[kp]+dis[kp],mxp[x]=kp,mxid[x]=id[kp];
			}
			else if(seb[x]<mxb[kp]+dis[kp])
				seb[x]=mxb[kp]+dis[kp],secp[x]=kp,secid[x]=id[kp];
		}
	}
}
void solve(int th){
	int mx=-1e15,f;
	for(int i=1;i<=n;i++)
		if(mx<seb[i]+mxb[i])
			mx=seb[i]+mxb[i],f=i;
	for(int i=f;mxp[i];i=mxp[i])dt[th]+=dis[mxp[i]],e[mxid[i]].data*=-1;
	dt[th]+=dis[secp[f]],e[secid[f]].data*=-1;
	for(int i=secid[f];mxp[i];i=mxp[i])dt[th]+=dis[mxp[i]],e[mxid[i]].data*=-1;
	for(int i=1;i<=n;i++)mxb[i]=mxp[i]=mxid[i]=seb[i]=secp[i]=secid[i]=0;
}
#undef int
int main()
{
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
	#define int long long
	n=read(),m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read(); zong+=w*2;
		add_edge(u,v,w); add_edge(v,u,w);
	}
	for(int i=1;i<=m;i++){
		dfs(1,0); solve(i);
	}
	for(int i=1;i<=m;i++)cin>>aa[i];
	printf("%lld ",zong); int ans;
	for(int i=1;i<=m;i++){
		b[i]=aa[i];
		sort(b+1,b+i+1); ans=zong;
		for(int j=1;j<=i;j++)
			ans-=max(0ll,dt[j]-b[j]);
		printf("%lld ",ans);
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
