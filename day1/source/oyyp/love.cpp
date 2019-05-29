#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
#define fgx cerr<<" -------------------------------------- "<<endl
inline int read(){
	int nm=0; bool fh=true; char cw=getchar();
	for(;!isdigit(cw);cw=getchar()) fh^=(cw=='-');
	for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
	return fh?nm:-nm;
}
#define M 200020
int n,m,sz[M],fs[M],to[M],nt[M],len[M],tmp,t[M]; LL now,G[M][2],H[M];
inline void link(int x,int y,int k){nt[tmp]=fs[x],fs[x]=tmp,len[tmp]=k,to[tmp++]=y;}
inline void upd(LL &x,LL y){x<y?(x=y):0ll;}
priority_queue<int>Q;
namespace n2{
	LL F[3002][3002][2];
	inline void DP(int x,int last){
//		debug(x)sp,debug(last)el;
		sz[x]=1,F[x][0][0]=F[x][0][1]=0;
		for(int i=fs[x],v;i!=-1;i=nt[i]) if((v=to[i])^last){
			DP(v,x); for(int k=0;k<=sz[x]+sz[v]&&k<=m;k++) G[k][0]=G[k][1]=0;
			for(int k1=0;k1<sz[x]&&k1<=m;k1++) for(int k2=0;k2<sz[v]&&k2+k1<=m;k2++){
				upd(G[k1+k2][0],F[x][k1][0]+F[v][k2][0]);
				upd(G[k1+k2][1],max(F[x][k1][1]+F[v][k2][0],F[x][k1][0]+F[v][k2][1]+len[i]));
				if(k1+k2<m) upd(G[k1+k2+1][0],F[x][k1][1]+F[v][k2][1]+len[i]);
			} sz[x]+=sz[v];
			for(int k=0;k<sz[x]&&k<=m;k++) F[x][k][0]=G[k][0],F[x][k][1]=G[k][1];
		}
//		debug(x)el;
//		for(int i=0;i<sz[x];i++) debug(F[x][i][0])sp,debug(F[x][i][1])el;fgx;
		for(int i=1;i<sz[x]&&i<=m;i++){
			upd(F[x][i][0],max(F[x][i-1][0],F[x][i-1][1]));
			upd(F[x][i][1],F[x][i][0]);
		}
	}
}
namespace m2{
	LL F[M][4][2];
	inline void DP(int x,int last){
		sz[x]=1,F[x][0][0]=F[x][0][1]=0;
		for(int i=fs[x],v;i!=-1;i=nt[i]) if((v=to[i])^last){
			DP(v,x); for(int k=0;k<=sz[x]+sz[v]&&k<=m;k++) G[k][0]=G[k][1]=0;
			for(int k1=0;k1<sz[x]&&k1<=m;k1++) for(int k2=0;k2<sz[v]&&k2+k1<=m;k2++){
				upd(G[k1+k2][0],F[x][k1][0]+F[v][k2][0]);
				upd(G[k1+k2][1],max(F[x][k1][1]+F[v][k2][0],F[x][k1][0]+F[v][k2][1]+len[i]));
				if(k1+k2<m) upd(G[k1+k2+1][0],F[x][k1][1]+F[v][k2][1]+len[i]);
			}
			for(int k=0;k<sz[x]+sz[v]&&k<=m;k++) F[x][k][0]=G[k][0],F[x][k][1]=G[k][1];
		}
		for(int i=1;i<sz[x]&&i<=m;i++){
			upd(F[x][i][0],max(F[x][i-1][0],F[x][i-1][1]));
			upd(F[x][i][1],F[x][i-1][1]);
		}
	}
}
inline void solve(){
	if(n<=3000){
		n2::DP(1,0);
		for(int i=0;i<=m&&i<=n;i++) upd(H[i+1],n2::F[1][i][1]),upd(H[i],n2::F[1][i][0]);
	}
	else if(m<=2){
		m2::DP(1,0);
		for(int i=0;i<=m&&i<=n;i++) upd(H[i+1],m2::F[1][i][1]),upd(H[i],m2::F[1][i][0]);
	}
	else exit(0); 
//	for(int i=1;i<=min(n,m);i++) debug(i)sp,debug(H[i])el;	
//	debug(n2::F[1][0][0])el;
//	debug(n2::F[1][0][1])el;
//	debug(n2::F[1][1][0])el;
//	debug(n2::F[1][1][1])el;
//	debug(H[1])el;
	for(int i=min(n,m);i>0;i--) H[i]-=H[i-1];
}
int main(){
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
	n=read(),m=read(),memset(fs,-1,sizeof(fs));
	for(int i=1,x,y,k;i<n;i++) x=read(),y=read(),k=read(),link(x,y,k),link(y,x,k),now+=k;
	for(int i=1;i<=m;i++) t[i]=read(); now<<=1;
	solve(); printf("%lld",now);
	for(int i=1,nw=0;i<=m;i++){
		if(!Q.empty()){
			int x=Q.top();
			if(x>t[i]) now+=t[i]-x,swap(t[i],x),Q.pop(),Q.push(x);
		}
		if(t[i]-H[nw+1]<=0) Q.push(t[i]),now+=t[i]-H[++nw];
		printf(" %lld",now);
	} puts(""); return 0;
}

