#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
#define LL long long
#define fgx cerr<<" ---------------------------------------------- "<<endl
inline int read(){
	int nm=0; bool fh=true; char cw=getchar();
	for(;!isdigit(cw);cw=getchar()) fh^=(cw=='-');
	for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
	return fh?nm:-nm;
}
#define M 630
#define mod 1000000007
inline int add(int x,int y){x+=y;return (x>=mod)?(x-mod):x;}
inline int mns(int x,int y){x-=y;return (x<0)?(x+mod):x;}
inline int mul(int x,int y){return (LL)x*(LL)y%mod;}
inline void upd(int &x,int y){x+=y;(x>=mod)?(x-=mod):0;}
inline void dec(int &x,int y){x-=y;(x<0)?x+=mod:x;}
inline int qpow(int x,int sq){int res=1;for(x%=mod;sq;sq>>=1,x=mul(x,x))if(sq&1)res=mul(res,x);return res;}
int n,m,p[M][22],ps[M][22],sz[M],t[22],F[M][M],tk[22],_sz;
int f[M],w[M];
int fd(int x){return x==f[x]?x:f[x]=fd(f[x]);}
inline int gt(int tt){
	sort(tk+1,tk+tt+1),reverse(tk+1,tk+tt+1);
	for(int i=1,ok=1;i<=m;i++,ok=1) if(sz[i]==tt){
		for(int j=1;ok==1&&j<=sz[i];j++) ok&=(tk[j]==p[i][j]);
		if(ok) return i;
	} assert(false); return -1;
}
inline void dfs(int x,int lim,int rem){
	if(!rem){
		sz[++m]=x-1;
		for(int i=1;i<x;i++) p[m][i]=t[i];
		for(int i=1,k1=1,k2=1;i<=n;i++){
			if(k2==p[m][k1]+1) k1++,k2=1;
			ps[m][i]=k1*100+k2,k2++;
		} return;
	}
	for(int i=min(lim,rem);i>0;--i) t[x]=i,dfs(x+1,i,rem-i);
}
inline void Guass(int tt){
	for(int i=1,k;i<tt;i++){
		for(k=i;k<tt&&!F[k][i];++k); assert(k<tt);
 		if(k^i){for(int j=i;j<=tt;j++) swap(F[i][j],F[k][j]);}
		int tmp=qpow(F[i][i],mod-2);
		for(int j=i;j<=tt;j++) F[i][j]=mul(F[i][j],tmp);
		for(int j=1;j<=tt;j++) if(F[j][i]&&j^i)
			for(int k=tt,tmp=F[j][i];k>=i;--k) dec(F[j][k],mul(tmp,F[i][k]));
	}
}
int main(){
	freopen("one.in","r",stdin); 
	freopen("one.out","w",stdout);
	n=read(),dfs(1,n,n);
	int _p=qpow((n*(n-1)/2),mod-2);
	for(int i=1;i<=m;i++){
		F[i][i]=1; if(i==m) break;
		for(int k1=1;k1<=n;k1++) for(int k2=k1+1;k2<=n;k2++){
			int b1=ps[i][k1]/100,p1=ps[i][k1]%100;
			int b2=ps[i][k2]/100,p2=ps[i][k2]%100;
			memcpy(tk,p[i],sizeof(tk));
			if(b1==b2){
				tk[b1]=k2-k1,tk[sz[i]+1]=p[i][b1]-(k2-k1);
				int tar=gt(sz[i]+1); dec(F[i][tar],_p);
			}
			else{
				swap(tk[b2],tk[sz[i]]),tk[b1]+=p[i][b2];
				int tar=gt(sz[i]-1); dec(F[i][tar],_p);
			}
		} F[i][m+1]=1;
	} Guass(m+1); //return 0;
	for(int i=1;i<=n;i++) w[i]=read(),f[i]=i;
	for(int i=1;i<=n;i++) f[fd(i)]=fd(w[i]); _sz=0;
	for(int i=1;i<=n;i++) if(fd(i)==i){
		tk[++_sz]=0;
		for(int j=1;j<=n;j++) if(fd(j)==i) tk[_sz]++;
	} int x=gt(_sz); printf("%d\n",F[x][m+1]); return 0;
}
