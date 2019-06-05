#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2002018;
int n,m,tot,dfn,now,a[N],fa[N],du[N],son[N],dep[N],stk[N],v[N],id[N];
struct Edge{int to,next;}e[N<<1];
struct Tr{int l,r,f;}tr[N<<2];
void add(int x,int y){
	e[++tot].to=y;
	e[tot].next=v[x]; v[x]=tot;
}
void dfs(int x,int ff){
	id[x]=++dfn;
	for(int p=v[x];p;p=e[p].next){
		int kp=e[p].to;
		if(kp!=ff){
			fa[kp]=x; son[x]=kp;
			dep[kp]=dep[x]+1;
			dfs(kp,x);
		}
	}
}
void add(int x,int y,int z){
	if(dep[x]<dep[y])swap(x,y);
	while(dep[x]>dep[y])a[x]+=z,x=fa[x];
	while(x!=y)a[x]+=z,a[y]+=z,x=fa[x],y=fa[y];
	a[x]+=z;
}
void getans(int x,int y){
	int top=1; stk[1]=a[x];
	for(int p=v[x];p;p=e[p].next)
		stk[++top]=a[e[p].to];
	sort(stk+1,stk+top+1);
	printf("%lld\n",stk[y]);
}
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void build(int k,int l,int r){
	tr[k].l=l; tr[k].r=r;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(k<<1,l,mid); build(k<<1|1,mid+1,r);
}
void change(int k,int ql,int qr,int dt){
	if(ql<=tr[k].l && qr>=tr[k].r)return tr[k].f+=dt,void();
	int mid=(tr[k].l+tr[k].r)>>1;
	if(ql<=mid)change(k<<1,ql,qr,dt);
	if(qr>mid)change(k<<1|1,ql,qr,dt);
}
void query(int k,int dt){
	now+=tr[k].f;
	if(tr[k].l==tr[k].r)return;
	int mid=(tr[k].l+tr[k].r)>>1;
	if(dt<=mid)return query(k<<1,dt);
	if(dt>mid)return query(k<<1|1,dt);
}
void work1(){
	int mx=1e9,loc;
	for(int i=1;i<=n;i++){
		if(du[i]==1)fa[i]=son[i]=n+1;
		if(du[i]<mx)mx=du[i],loc=i;
	}
	dfs(loc,0);
	build(1,0,n+1);
	for(int i=1;i<=m;i++){
		int opt=read(),x=read(),y=read(),z;
		if(opt==1)change(1,id[x],id[y],read());
		else{
			now=0,query(1,id[fa[x]]);stk[1]=now+a[fa[x]];
			now=0,query(1,id[x]),stk[2]=now+a[x];
			now=0,query(1,id[son[x]]),stk[3]=now+a[son[x]];
			sort(stk+1,stk+4);
			printf("%lld\n",stk[y]);
		}
	}
}
int main()
{
	freopen("yuki.in","r",stdin);
	freopen("yuki.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	a[0]=a[n+1]=1e9+7;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v); add(v,u);
		++du[u]; ++du[v];
	}
	if(n<=1000){
		dfs(1,0); fa[1]=dep[1]=0;
		for(int i=1;i<=m;i++){
			int opt=read(),x=read(),y=read(),z;
			if(opt==1)add(x,y,read());
			else getans(x,y);
		}
	}
	else work1();
	fclose(stdin); fclose(stdout);
	return 0;
}
