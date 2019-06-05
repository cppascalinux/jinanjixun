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
const int maxn=11000;
int n,m,a[maxn],p[maxn<<2],lz[maxn<<2];
#define lc (o<<1)
#define rc (o<<1|1)
inline void updata(int o){p[o]=p[lc]^p[rc];}
inline void paint(int o,int l,int r,int z){
	if((r-l+1)%2) p[o]^=z;
	lz[o]^=z;
}
inline void pushdown(int o,int l,int r){
	if(!lz[o]) return;
	int mid=l+r>>1;
	paint(lc,l,mid,lz[o]);
	paint(rc,mid+1,r,lz[o]);
	lz[o]=0;
}
void revise(int o,int l,int r,int ql,int qr,int z){
	if(ql==l&&qr==r){paint(o,l,r,z);return;}
	int mid=l+r>>1;pushdown(o,l,r);
	if(ql<=mid) revise(lc,l,mid,ql,min(qr,mid),z);
	if(qr> mid) revise(rc,mid+1,r,max(ql,mid+1),qr,z);
	updata(o);
}
int query(int o,int l,int r,int ql,int qr){
	if(ql==l&&qr==r) return p[o];
	int mid=l+r>>1,ans=0;pushdown(o,l,r);
	if(ql<=mid) ans^=query(lc,l,mid,ql,min(qr,mid));
	if(qr> mid) ans^=query(rc,mid+1,r,max(ql,mid+1),qr);
	return ans;
}
void build(int o,int l,int r){
	if(l==r){p[o]=a[l];return;}
	int mid=l+r>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	updata(o);
}
int main(){
	freopen("save.in","r",stdin);
	freopen("save.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	if(n<=10000&&m<=10000){
		while(m--){
			int ms=read(),l=read(),r=read();
			if(ms==1){
				int x=read();
				for(int i=l;i<=r;i++) a[i]^=x;
			}
			if(ms==2) sort(a+l,a+r+1);
			if(ms==3){
				int ans=0;
				for(int i=l;i<=r;i++) ans^=a[i];
				printf("%d\n",ans);
			}
		}
		return 0;
	}
	else{
		build(1,1,n);
		while(m--){
			int ms=read(),l=read(),r=read();
			if(ms==1) revise(1,1,n,l,r,read());
			else printf("%d\n",query(1,1,n,l,r));
		}
		return 0;
	}
    return 0;
}













