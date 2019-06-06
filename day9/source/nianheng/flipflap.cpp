#include<map>
#include<cmath>
#include<ctime>
#include<queue>
#include<vector>
#include<cstdio>
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
const int maxn=1e5+100,maxc=20,maxd=330;
int n,m,a[maxn],lim,f[maxn][maxc],*tmp,Lz;
int ql[maxn][maxc],qr[maxn][maxc];
bool cmp1(pii x,pii y){
	return x.second<y.second;
}
bool cmp2(pii x,pii y){
	return (tmp[x.second]*Lz+x.first)<(tmp[y.second]*Lz+y.first);
}
struct fk{
	int n,bl[maxd],br[maxd],siz[maxd],cnt[maxd],blk,M;
	int ld[maxn],rd[maxn],bc[maxn],lz[maxn],sum[maxn],cc[maxn];
	pii a[maxn];
	inline void prepare(){
		M=sqrt(n),blk=(n-1)/M+1;
		memset(bl,0x3f,sizeof(bl));
		for(int i=1;i<=n;i++){
			int d=bc[i]=(i-1)/M+1;
			int z=cc[i]=rd[d]-ld[d]+1;
			a[i]=mp(0,i),sum[i]=sum[i-1]+z;
			siz[d]++,cnt[d]+=z;
			qmin(bl[d],i),qmax(br[d],i);
		}
	}
	inline void revise1(int x,int z){
		int d=bc[x];
		sort(a+bl[d],a+br[d]+1,cmp1);
		a[x].first+=z;
	}
	inline void revise2(int l,int r,int z){
		int L=bc[l],R=bc[r];
		for(int i=L+1;i<R;i++) lz[i]+=z*cnt[i];
		if(L==R) {
			revise1(l,sum[r]-sum[l-1]);
			return;
		}
		revise1(l,sum[bl[L+1]]-sum[l-1]);
		revise1(r,sum[r]-sum[br[R-1]]);
	}
	inline int query1(int d,int z){
		tmp=cc,Lz=lz[d];
		sort(a+bl[d],a+br[d]+1,cmp2);
		int l=bl[d],r=br[d]+1,Ans=bl[d]-1;
		while(l<r){
			int mid=l+r>>1;
			if((cc[mid]*lz[d]+a[mid].first)<=z)
				Ans=mid,l=mid+1;
			else r=mid;
		}
		return Ans-bl[d]+1;
	}
	inline int query2(int l,int r,int z){
		int L=bc[l],R=bc[r],Ans=0;
		for(int i=L+1;i<R;i++) Ans+=query1(i,z);
		if(L==R){
			sort(a+bl[L],a+br[L]+1,cmp1);
			for(int i=l;i<=r;i++)
				Ans+=(cc[i]*lz[L]+a[i].first)<=z;
			return Ans;
		}
		sort(a+bl[L],a+br[L]+1,cmp1);
		sort(a+bl[R],a+br[R]+1,cmp1);
		for(int i=l;i<=br[L];i++) Ans+=(cc[i]*lz[L]+a[i].first)<=z;
		for(int i=r;i>=bl[R];i--) Ans+=(cc[i]*lz[R]+a[i].first)<=z;
		return Ans;
	}
}p[maxc];
void build(int d,int l,int r){
	qmax(lim,d);int x=++p[d].n;
	p[d].ld[x]=l,p[d].rd[x]=r;
	for(int i=l;i<=r;i++)
		f[i][d]=x;
	if(l==r) return;
	int mid=l+r>>1;
	build(d+1,l,mid);
	build(d+1,mid+1,r);
}
inline void revise(int l,int r,int z){
	for(int d=1;d<=lim;d++){
		int L=f[l][d],R=f[r][d];
		if(L&&R){
			if(L==R){
				p[d].revise1(L,(r-l+1)*z);
				continue;
			}
			if(R-L>1) p[d].revise2(L+1,R-1,z);
			p[d].revise1(L,(p[d].rd[L]-l+1)*z);
			p[d].revise1(R,(r-p[d].rd[R]+1)*z);
		}
		else
		if(L==0&&R){
			L=qr[l][d];
			if(L==R){
				p[d].revise1(L,(r-p[d].ld[R]+1)*z);
				continue;
			} 
			if(R-L) p[d].revise2(L,R-1,z);
			p[d].revise1(R,(r-p[d].rd[R]+1)*z);
		}
		else
		if(L&&R==0){
			R=ql[r][d];
			if(L==R){
				p[d].revise1(L,(p[d].rd[L]-l+1)*z);
				continue;
			} 
			if(R-L) p[d].revise2(L+1,R,z);
			p[d].revise1(L,(p[d].rd[L]-l+1)*z);
		}
		else{
			L=qr[l][d],R=ql[r][d];
			if(!L) continue;
			p[d].revise2(L,R,z);
		}
	}
}
inline int query(int l,int r,int z){
	int Ans=0;
	for(int d=1;d<=lim;d++){
		int L=f[l][d],R=f[r][d];
		if(L&&R){
			if(R-L>1) Ans+=p[d].query2(L+1,R-1,z);
			if(L==R){
				if(!L) continue;
				if(p[d].ld[L]==l&&p[d].rd[R]==r)
					Ans+=p[d].query2(L,R,z);
				continue;
			}
			if(p[d].ld[L]==l) Ans+=p[d].query2(L,L,z);
			if(p[d].rd[R]==r) Ans+=p[d].query2(R,R,z);
		}
		else
		if(L==0&&R){
			L=qr[l][d];
			if(R-L) Ans+=p[d].query2(L,R-1,z);
			if(p[d].rd[R]==r) Ans+=p[d].query2(R,R,z);
		}
		else
		if(L&&R==0){
			R=ql[r][d];
			if(R-L) Ans+=p[d].query2(L+1,R,z);
			if(p[d].ld[L]==l) Ans+=p[d].query2(L,L,z);
		}
		else{
			L=qr[l][d],R=ql[r][d];
			if(L==0) continue;
			Ans+=p[d].query2(L,R,z);
		}
	}
	return Ans;
}
int main(){
	freopen("flipflap.in","r",stdin);
	freopen("flipflap.out","w",stdout);
	n=read(),m=read();
	build(1,1,n);
	for(int d=1;d<=lim;d++)
		p[d].prepare();
	for(int d=1;d<=lim;d++){
		for(int i=1,qq=0;i<=n;i++){
			if(f[i][d]) qq=f[i][d];
			else ql[i][d]=qq;
		}
		for(int i=n,hj=0;i>=1;i--){
			if(f[i][d]) hj=f[i][d];
			else qr[i][d]=hj;
		}
	}
	while(m--){
		int ms=read(),l=read(),r=read(),z=read();
		if(ms==1) revise(l,r,z);
		else printf("%d\n",query(l,r,z));
	}
	return 0;
}












