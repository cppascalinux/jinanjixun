#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
#define fgx cerr<<" -------------------------- "<<endl
#define LL long long
inline int read(){
	int nm=0; bool fh=true; char cw=getchar();
	for(;!isdigit(cw);cw=getchar()) fh^=(cw=='-');
	for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
	return fh?nm:-nm;
}
#define M 2040
#define mod 1000000007
inline int add(int x,int y){x+=y;return (x>mod)?(x-mod):x;}
inline int mns(int x,int y){x-=y;return (x<0)?(x+mod):x;}
inline int mul(int x,int y){return (LL)x*(LL)y%mod;}
inline void upd(int &x,int y){x+=y;(x>=mod)?(x-=mod):0;}
int n,m,p[M],t[M],F[40][M],G[40][M],ans1,ans2,T[40],B[M],S[M];
int main(){
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	n=read(),m=read(); int all=(1<<(n-1));
	for(int i=0;i<n;i++) p[i]=read(); F[m][0]=G[m][0]=1;
	for(int i=0;i<m;i++) for(int k=0;k<n;k++) T[i]|=(((p[k]>>i)&1)<<k);
	for(int i=0;i<(1<<n);i++){
		for(int k=0;k<(n-1);k++){
			if(((i>>k)&1)>((i>>(k+1))&1)) B[i]|=(1<<k);
			if(((i>>k)&1)<((i>>(k+1))&1)) S[i]|=(1<<k);
		}
	} int maxn=(1<<n)-1;
	for(int bt=m-1;bt>=0;bt--) for(int sta=0;sta<all;sta++){
		for(int tar=T[bt];tar>=0&&F[bt+1][sta]>0;--tar,tar&=T[bt]){
			if((sta&B[tar])==B[tar]) upd(F[bt][S[tar]|sta],F[bt+1][sta]);
			if(!tar) break;
		}
		for(int tar=(maxn^T[bt]);tar>=0&&G[bt+1][sta]>0;--tar,tar&=(maxn^T[bt])){
			if((sta&S[maxn^tar])==S[maxn^tar]) upd(G[bt][B[tar^maxn]|sta],G[bt+1][sta]);
			if(!tar) break;
		}
	}
	for(int sta=0;sta<all;sta++) upd(ans1,F[0][sta]),upd(ans2,G[0][sta]);
	printf("%d\n",mul(ans1,ans2)); return 0;
}
