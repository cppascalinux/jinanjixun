#include <stdlib.h>
#include <string.h>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100010,BUF=22000000,P=1000000007;
int Log[N<<1];
int Case,n,i,j,x,y,z;
int g[N],nxt[N<<1],v[N<<1],w[N<<1],ok[N<<1],ed,son[N],f[N],all,now;
int val[N];
int ans;
char Buf[BUF],*buf=Buf;
inline void read(int&a){for(a=0;*buf<48;buf++);while(*buf>47)a=a*10+*buf++-48;}
inline void up(int&a,int b){a=a+b<P?a+b:a+b-P;}
namespace T2{
int g[N],nxt[N<<1],v[N<<1],w[N<<1],st[N],en[N],dfn,ed,d[N],dep[N];
int pool[N<<1],pos[N],cur,f[18][N<<1];
int m,i,j,x,a[N],q[N],t,tot;bool vip[N],vis[N];
int ALL,SUM,RET;
int cnt[N],sum[N];
inline bool cmp(int x,int y){return st[x]<st[y];}
inline void add(int x,int y,int z){v[++ed]=y;w[ed]=z;nxt[ed]=g[x];g[x]=ed;}
void dfs(int x,int y){
  st[x]=++dfn;
  pool[++cur]=x;
  pos[x]=cur;
  for(int i=g[x];i;i=nxt[i])if(v[i]!=y){
    d[v[i]]=(d[x]+w[i])%P;
    dep[v[i]]=dep[x]+1;
    dfs(v[i],x);
    pool[++cur]=x;
  }
  en[x]=dfn;
}
inline int merge(int x,int y){
  return dep[x]<dep[y]?x:y;
}
inline int lca(int x,int y){
  x=pos[x];
  y=pos[y];
  if(x>y)swap(x,y);
  int k=Log[y-x+1];
  return merge(f[k][x],f[k][y-(1<<k)+1]);
}
void init(){
  for(i=1;i<n;i++)read(x),read(y),read(z),add(x,y,z),add(y,x,z);
  dfs(1,0);
  for(i=1;i<=cur;i++)f[0][i]=pool[i];
  for(j=1;j<18;j++)for(i=1;i+(1<<j)-1<=cur;i++)f[j][i]=merge(f[j-1][i],f[j-1][i+(1<<(j-1))]);
}
void clear(){
  for(i=0;i<=n;i++)g[i]=st[i]=en[i]=d[i]=dep[i]=0;
  cur=dfn=ed=0;
}
inline void append(int x){
  a[++m]=x;
  vis[x]=vip[x]=1;
}
void dp(int x){
  if(vip[x])cnt[x]=1,sum[x]=val[x];
  else cnt[x]=sum[x]=0;
  for(int i=g[x];i;i=nxt[i]){
    int y=v[i];
    dp(y);
    RET=((1LL*sum[y]*(ALL-cnt[y])+1LL*(SUM-sum[y])*cnt[y])%P*(d[y]-d[x])+RET)%P;
    cnt[x]+=cnt[y];
    up(sum[x],sum[y]);
  }
}
inline int solve(){
  RET=0;
  if(m<=5){
    for(i=1;i<=m;i++)for(j=1;j<i;j++)
      RET=(1LL*(val[a[i]]+val[a[j]])*(d[a[i]]+d[a[j]]-2*d[lca(a[i],a[j])])+RET)%P;
    for(i=1;i<=m;i++)vis[a[i]]=vip[a[i]]=0;
    return RET;
  }
  ALL=m;
  SUM=0;
  for(i=1;i<=m;i++)up(SUM,val[a[i]]);
  if(!vis[1])a[++m]=vis[1]=1;
  tot=m;
  sort(a+1,a+m+1,cmp);
  for(i=1;i<m;i++)if(!vis[x=lca(a[i],a[i+1])])vis[a[++tot]=x]=1;
  m=tot;
  sort(a+1,a+m+1,cmp);
  for(ed=0,i=1;i<=m;i++)g[a[i]]=0;
  for(q[t=1]=1,i=2;i<=m;q[++t]=a[i++]){
    while(st[a[i]]<st[q[t]]||en[a[i]]>en[q[t]])t--;
    add(q[t],a[i],0);
  }
  dp(1);
  for(i=1;i<=m;i++)vis[a[i]]=vip[a[i]]=0;
  return RET;
}
}
inline void add(int x,int y,int z){v[++ed]=y;w[ed]=z;ok[ed]=1;nxt[ed]=g[x];g[x]=ed;}
void findroot(int x,int y){
  son[x]=1;f[x]=0;
  for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=y){
    findroot(v[i],x);
    son[x]+=son[v[i]];
    if(son[v[i]]>f[x])f[x]=son[v[i]];
  }
  if(all-son[x]>f[x])f[x]=all-son[x];
  if(f[x]<f[now])now=x;
}
inline void ext(int x,int y){
  val[x]=y;
  T2::append(x);
}
void dfs(int x,int y,int len){
  ext(x,len);
  for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=y)dfs(v[i],x,(len+w[i])%P);
}
void solve(int x){
  int i;
  T2::m=0;
  dfs(x,0,0);
  ans=(ans+T2::solve())%P;
  for(i=g[x];i;i=nxt[i])if(ok[i]){
    T2::m=0;
    dfs(v[i],x,w[i]);
    ans=(ans-T2::solve())%P;
  }
  for(i=g[x];i;i=nxt[i])if(ok[i]){
    ok[i^1]=0;
    f[0]=all=son[v[i]];
    findroot(v[i],now=0);
    solve(now);
  }
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);

  for(i=2;i<N*2;i++)Log[i]=Log[i>>1]+1;
  fread(Buf,1,BUF,stdin);
    read(n);
    for(ed=i=1;i<n;i++)read(x),read(y),read(z),add(x,y,z),add(y,x,z);
    T2::init();
    f[0]=all=n;findroot(1,now=0);solve(now);
    ans=ans*2%P;
    printf("%d\n",(ans%P+P)%P);
    for(i=0;i<=n;i++)g[i]=0;
    ans=0;
    T2::clear();
}
