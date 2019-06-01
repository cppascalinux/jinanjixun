#include<map>
#include<ctime>
#include<cmath>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define qmax(x,y) (x=max(x,y))
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
inline int read(){
	int ans=0,fh=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		ans=ans*10+ch-'0',ch=getchar();
	return ans*fh;
}
const int maxn=5e5+100;
struct road{
	int x,y;
}rd[maxn];
struct quest{
	int l,r,id;
}qq[maxn];
#define lc (o<<1)
#define rc (o<<1|1)
int n,m,q,fa[maxn],f[maxn][21],dep[maxn],tot;
int head[maxn],nex[maxn<<1],v[maxn<<1],num=1,lz[maxn<<2];
int ok[maxn],ans[maxn],p[maxn<<2],pp[maxn],d[maxn];
inline void add(int x,int y){
	v[++num]=y,nex[num]=head[x],head[x]=num;
	v[++num]=x,nex[num]=head[y],head[y]=num;
}
void dfs(int x,int Fa){
	f[x][0]=Fa,dep[x]=dep[Fa]+1;
	for(int i=1;i<=20;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	for(int i=head[x];i;i=nex[i])
		if(v[i]!=Fa) dfs(v[i],x);
}
inline int Lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;~i;i--)
		if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(int i=20;~i;i--)
		if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
int getfa(int x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
inline void merge(int x,int y){
	x=getfa(x),y=getfa(y);
	if(x==y) return;
	tot--,fa[x]=y;
}
inline void paint(int o,int z){qmax(p[o],z),qmax(lz[o],z);}
inline void updata(int o){p[o]=max(p[lc],p[rc]);}
inline void pushdown(int o){
	if(!lz[o]) return;
	paint(lc,lz[o]);
	paint(rc,lz[o]);
	lz[o]=0;
}
int query(int o,int l,int r,int ql,int qr){
	if(ql==l&&qr==r) return p[o];
	int mid=l+r>>1,Ans=0;pushdown(o);
	if(ql<=mid) qmax(Ans,query(lc,l,mid,ql,min(qr,mid)));
	if(qr> mid) qmax(Ans,query(rc,mid+1,r,max(ql,mid+1),qr));
	return Ans;
}
void revise(int o,int l,int r,int ql,int qr,int qz){
	if(ql==l&&qr==r){paint(o,qz);return;}
	int mid=l+r>>1;pushdown(o);
	if(ql<=mid) revise(lc,l,mid,ql,min(qr,mid),qz);
	if(qr> mid) revise(rc,mid+1,r,max(ql,mid+1),qr,qz);
	updata(o);
}
bool cmp(quest x,quest y){return x.r<y.r;}
inline void Revise(int x,int z){
	for(int i=x;i<=n;i+=i&(-i)) pp[i]+=z;
}
inline int Query(int l,int r,int z=0){
	for(int i=r;i;i-=i&(-i)) z+=pp[i];
	for(int i=l-1;i;i-=i&(-i)) z-=pp[i];
	return z;
}
inline int jmp(int x){
	int cl=getfa(x);
	for(int i=20;~i;i--)
		if(getfa(f[x][i])==cl) x=f[x][i];
	return x;
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n=read(),m=read(),q=read();
	if(n<=1000&&m<=1000&&q<=1000){
		for(int i=1;i<n;i++) add(read(),read());
		for(int i=1;i<=m;i++) rd[i]=(road){read(),read()};
		dfs(1,0);
		while(q--){
			int l=read(),r=read();
			tot=0;
			for(int i=1;i<=n;i++)
				fa[i]=i,ok[i]=0;
			for(int i=l;i<=r;i++){
				int x=rd[i].x,y=rd[i].y;
				int la=Lca(x,y);
				x=jmp(x);
				while(dep[x]>dep[la]){
					if(!ok[x]) tot++,ok[x]=1;
					merge(x,la),x=f[x][0];
				}
				y=jmp(y);
				while(dep[x]>dep[la]){
					if(!ok[y]) tot++,ok[y]=1;
					merge(y,la),y=f[y][0];
				}
				if(!ok[la]) tot++,ok[la]=1;
			}
			printf("%d\n",tot);
		}
	}
	else{
		for(int i=1;i<n;i++) read(),read();
		for(int i=1;i<=m;i++){
			int l=read(),r=read();
			if(l>r) swap(l,r);
			rd[i]=(road){l,r};
		}
	 	for(int i=1;i<=m;i++){
			d[i]=query(1,1,n,rd[i].x,rd[i].y);
			revise(1,1,n,rd[i].x,rd[i].y,i);
		}
		for(int i=1;i<=q;i++) qq[i]=(quest){read(),read(),i};
		sort(qq+1,qq+q+1,cmp);
		for(int i=1,nw=0;i<=q;i++){
			while(nw<qq[i].r){
				++nw;
				if(d[nw]) Revise(d[nw],1);
			}
			ans[qq[i].id]=(qq[i].r-qq[i].l+1)-Query(qq[i].l,qq[i].r);
		}
		for(int i=1;i<=q;i++)
			printf("%lld\n",ans[i]);
	}
	return 0;
}












