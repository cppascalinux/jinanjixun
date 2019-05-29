#include<bits/stdc++.h>
#define maxn 200100
using namespace std;
namespace WXHAK{
	struct edge{
		int r,nxt,w,id;
	}e[maxn<<2];
	int head[maxn],S,T,q[maxn],esz,l,r,cur[maxn],dep[maxn];
	void addedge(int u,int v,int w,int id){
//		printf("[%d->%d]",u,v);
		e[++esz].r=v;e[esz].nxt=head[u];head[u]=esz;e[esz].w=w;e[esz].id=id;
		e[++esz].r=u;e[esz].nxt=head[v];head[v]=esz;e[esz].w=0;e[esz].id=-id;
	}
	bool bfs(){
		for(int i=S;i<=T;++i)cur[i]=head[i],dep[i]=0;
		l=r=0,q[r++]=S,dep[S]=1;
		while(l<r){
			int u=q[l++];
			for(int t=head[u];t;t=e[t].nxt)if(e[t].w&&!dep[e[t].r])
				dep[e[t].r]=dep[u]+1,q[r++]=e[t].r;
		}
		return dep[T]!=0;
	}
	int find(int u,int flow){
		if(u==T)return flow;
		int used=0,a=0;
		for(int& t=cur[u];t;t=e[t].nxt)if(e[t].w&&dep[e[t].r]==dep[u]+1){
			a=find(e[t].r,min(flow-used,e[t].w));
			e[t].w-=a,e[t^1].w+=a,used+=a;
			if(used==flow)return used;
		}
		if(!used)dep[u]=-1;
		return used;
	}
	void init(int _S,int _T){
		S=_S,T=_T,esz=1;
		for(int i=S;i<=T;++i)head[i]=0;
	}
	int dinic(){
		int ans=0,a=0;
		while(bfs())
			while(a=find(S,1<<30))ans+=a;
		return ans;
	}
	void cal(int anses[]){
		for(int i=1;i<=esz;++i)if(!e[i].w&&e[i].id)
			anses[abs(e[i].id)]=e[i].id>0?!anses[abs(e[i].id)]:anses[abs(e[i].id)];
	}
}

int mtp,in[maxn],out[maxn],anses[maxn],tg[maxn];
int li[maxn],ri[maxn],lx[maxn],wi[maxn],lsh[maxn<<1],tp,n,m;
int main(){
	freopen("wait.in","r",stdin);
	freopen("wait.out","w",stdout);
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;++i){
		scanf("%d%d%d",&li[i],&ri[i],&wi[i]);
		ri[i]++;
		lsh[++tp]=li[i],lsh[++tp]=ri[i];
		lx[++mtp]=li[i],lx[++mtp]=ri[i];
	}
	sort(lsh+1,lsh+tp+1);
	sort(lx+1,lx+mtp+1);
	tp=unique(lsh+1,lsh+tp+1)-lsh-1;
	for(int i=1;i<=m;++i){
		li[i]=lower_bound(lsh+1,lsh+tp+1,li[i])-lsh;
		ri[i]=lower_bound(lsh+1,lsh+tp+1,ri[i])-lsh;
	}
	for(int i=1;i<=mtp;i+=2){
		int x=lower_bound(lsh+1,lsh+tp+1,lx[i])-lsh;
		int y=lower_bound(lsh+1,lsh+tp+1,lx[i+1])-lsh;
		if(x==y)continue;
		tg[i]=rand()%2;
		if(tg[i]==0)in[y]++,out[x]++;
		else in[x]++,out[y]++;
	}
	for(int i=1;i<=m;++i){
		int r=(wi[i]==-1?rand()%2:wi[i]);
		anses[i]=r;
		if(r==0)out[li[i]]++,in[ri[i]]++;
		else out[ri[i]]++,in[li[i]]++;
	}
	WXHAK::init(0,tp+1);
	int sum=0;
	for(int i=1;i<=tp;++i)if((in[i]-out[i])&1)return puts("-1"),0;
	for(int i=1;i<=tp;++i){
		int d=(in[i]-out[i])/2;
		if(d>0)WXHAK::addedge(WXHAK::S,i,d,0),sum+=d;
		else if(d<0)WXHAK::addedge(i,WXHAK::T,-d,0);
	}
	for(int i=1;i<=m;++i)if(wi[i]==-1){
		if(anses[i]==0)WXHAK::addedge(ri[i],li[i],1,i);
		else WXHAK::addedge(li[i],ri[i],1,i);
	}
	for(int i=1;i<=mtp;i+=2){
		int x=lower_bound(lsh+1,lsh+tp+1,lx[i])-lsh;
		int y=lower_bound(lsh+1,lsh+tp+1,lx[i+1])-lsh;
		if(x==y)continue;
		if(tg[i]==0)WXHAK::addedge(y,x,1,0);
		else WXHAK::addedge(x,y,1,0);
	}
	int wxh=WXHAK::dinic();
	if(wxh!=sum)return puts("-1"),0;
	WXHAK::cal(anses);
	for(int i=1;i<=m;++i){
		if(wi[i]!=-1)printf("%d ",wi[i]);
		else printf("%d ",anses[i]);
	}
} 
