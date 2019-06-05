#include<map>
#include<cmath>
#include<ctime>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define qmin(x,y) (x=min(x,y))
#define qmax(x,y) (x=max(x,y))
#define mp(x,y) make_pair(x,y)
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
int tim;
struct io
{
	char ibuf[51000000] , * s , obuf[51000000] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "yuki.in" , "r" , stdin );
		freopen( "yuki.out" , "w" , stdout );
		fread( s = ibuf , 1 ,  51000000  , stdin );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
	}
	inline int read()
	{
		tim++;
		register int u = 0;
		while( * s < 48 ) s++;
		while( * s > 32 )
			u = u * 10 + * s++ - 48;
		return u;
	}
	template < class T >
	inline void print( register T u )
	{
		static int * q = a;
		if( !u ) * t++ = 48;
		else
		{
			while( u ) * q++ = u % 10 + 48 , u /= 10;
			while( q != a )
				* t++ = * --q;
		}
		* t++ = '\n';
	}
} ip;

#define read ip.read
#define print ip.print
const int maxn=1e6+100;
int n,m,head[maxn],nex[maxn<<1],v[maxn<<1],num=1;
int f[maxn][21],dep[maxn],b[maxn],du[maxn];
int Fr,bh[maxn];
ll a[maxn],p[maxn<<2],lz[maxn<<2];
#define lc (o<<1)
#define rc (o<<1|1)
inline void add(int x,int y){
	du[x]++,du[y]++;
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
void getbh(int x,int Fa,int Bh){
	bh[x]=Bh;
	for(int i=head[x];i;i=nex[i])
		if(v[i]!=Fa) getbh(v[i],x,Bh+1); 
}
inline void paint(int o,int l,int r,int z){
	p[o]+=z,lz[o]+=z;
}
inline void pushdown(int o,int l,int r){
	if(!lz[o]) return;
	int mid=l+r>>1;
	paint(lc,l,mid,lz[o]);
	paint(rc,mid+1,r,lz[o]);
	lz[o]=0;
}
inline void updata(int o){p[o]=max(p[lc],p[rc]);}
void revise(int o,int l,int r,int ql,int qr,int qz){
	if(ql==l&&qr==r){paint(o,l,r,qz);return;}
	int mid=l+r>>1;pushdown(o,l,r);
	if(ql<=mid) revise(lc,l,mid,ql,min(qr,mid),qz);
	if(qr> mid) revise(rc,mid+1,r,max(ql,mid+1),qr,qz);
}
int query(int o,int l,int r,int qd){
	if(l==r) return p[o];
	int mid=l+r>>1;pushdown(o,l,r);
	if(qd<=mid) return query(lc,l,mid,qd);
	else return query(rc,mid+1,r,qd);
}
void build(int o,int l,int r){
	if(l==r){p[o]=a[bh[l]];return;}
	int mid=l+r>>1;
	build(lc,l,mid),build(rc,mid+1,r);
}
int main(){
//	freopen("nh.in","r",stdin);
//	freopen("zhy.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=2;i<=n;i++) add(read(),read());
	if(n<=1000&&m<=1000){
		dfs(1,0);
		while(m--){
			int ms=read(),x=read(),y=read();
			if(ms==1){
				int z=read(),la=Lca(x,y);
				while(x!=la) a[x]+=z,x=f[x][0];
				while(y!=la) a[y]+=z,y=f[y][0];
				a[la]+=z;
			}
			else{
				int cnt=0;
				for(int i=head[x];i;i=nex[i])
					b[++cnt]=a[v[i]];
				b[++cnt]=a[x],sort(b+1,b+cnt+1);
				print(b[y]);
			}
		}
		return 0;
	}
	else{
		for(int i=1;i<=n;i++)
			if(du[i]==1) Fr=i;
		getbh(Fr,0,1);
		build(1,1,n);
		while(m--){
			int ms=read(),x=read(),y=read();
			if(ms==1){
				int z=read();x=bh[x],y=bh[y];
				if(x>y) swap(x,y);
				revise(1,1,n,x,y,z);
			}
			else{
				int cnt=0;
				for(int i=head[x];i;i=nex[i])
					b[++cnt]=query(1,1,n,bh[v[i]]);
				b[++cnt]=query(1,1,n,bh[x]);
				sort(b+1,b+cnt+1);
				print(b[y]);
			}
		}
	}
	return 0;
}












