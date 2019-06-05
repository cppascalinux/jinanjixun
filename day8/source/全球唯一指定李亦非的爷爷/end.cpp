#include<bits/stdc++.h>
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
#define fgx cerr<<"-----------------------------------"<<endl
#define LL long long
using namespace std;
int read(){
	int nm=0,fh=1; char cw=getchar();
	for(;!isdigit(cw);cw=getchar()) if(cw=='-') fh=-fh;
	for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
	return nm*fh;
}
#define mod 1000000007
inline int mul(LL x,LL y){return (LL)x*(LL)y%mod;}
inline void upd(int &x,int y){x+=y;(x>=mod)?(x-=mod):0;}
inline int qpow(int x,int sq){int res=1;for(;sq;sq>>=1,x=mul(x,x))if(sq&1)res=mul(res,x);return res;}
#define M 200020
#define MAXN 52
#define pb push_back
int n,m,K,mt[MAXN][MAXN],trans[MAXN][MAXN],res[MAXN][MAXN],L;
int p[M][9],c[M][9],sz[M],t[9],tk[9],tot,be[M],lm[M],T[2][MAXN][MAXN],bt[M],tt;
vector<int>tr[3][MAXN],kt[2][MAXN]; char ch[M];
inline int gt(int tm){
	sort(tk+1,tk+tt+1),reverse(tk+1,tk+tt+1);
	for(int i=1,ok=1;i<=tot;i++,ok=1) if(sz[be[i]]==tt){
		for(int j=1;ok==1&&j<=sz[be[i]];j++) ok&=(tk[j]==p[be[i]][j]);
		if(ok&&tm==lm[i]) return i;
	} return -1;
}
inline void dfs(int x,int lim,int rem){
	if(!rem){
		sz[++m]=x-1;
		for(int i=1;i<x;i++) p[m][i]=t[i];
		for(int i=x-1;i>0;--i) c[m][p[m][i]]=i;
		for(int i=1;i<=n;i++) if(c[m][i]) be[++tot]=m,lm[tot]=i;
		be[++tot]=m,lm[tot]=0;
	}
	for(int i=min(lim,rem);i>0;--i) t[x]=i,dfs(x+1,i,rem-i);
}
inline void ins(int x){if(x>0) tk[++tt]=x;}
#define rep1 for(int x=1;x<=tot;x++) for(int k=0,TP=tr[2][x].size();k<TP;++k)
#define rep2(typ) for(int y=tr[2][x][k],z=0,DTP=tr[typ][y].size();z<DTP;++z)
#define rep(len) for(int i=1;i<=len;i++) for(int j=1;j<=len;j++) for(int k=1;k<=len;k++)
inline void init(){
	for(int i=1;i<=tot;i++) trans[i][i]=1;
	for(int xx=0;xx<L;xx++){
		bool typ=(ch[xx]=='1');
		rep1 rep2(typ) if(trans[x][y]) upd(mt[x][tr[typ][y][z]],mul(trans[x][y],kt[typ][y][z]));
//		debug(typ)el;
		memcpy(trans,mt,sizeof(mt)),memset(mt,0,sizeof(mt));
	}
}
inline void mul1(){
	memset(mt,0,sizeof(mt));
	rep(tot) upd(mt[i][j],mul(res[i][k],trans[k][j]));
	memcpy(res,mt,sizeof(mt));
}
inline void mul2(){
	memset(mt,0,sizeof(mt));
	rep(tot) upd(mt[i][j],mul(trans[i][k],trans[k][j]));
	memcpy(trans,mt,sizeof(mt));
}
int main(){
	freopen("end.in","r",stdin);
	freopen("end.out","w",stdout);
	n=read(); int all=(1<<n); dfs(1,n,n),K=read(),scanf("%s",ch);
	for(int i=0;i<(1<<n);++i) bt[i]=bt[i>>1]+(i&1); L=strlen(ch);
	for(int kd=0;kd<2;kd++){
		for(int i=1;i<=tot;i++){		
			for(int k=0;k<(1<<n);k++){
				if(bt[k]&1) continue;
				int now=k,ot=0; bool ok=true; tt=0;
				for(int bk=1;bk<=sz[be[i]];now>>=p[be[i]][bk++]){
					if(c[be[i]][lm[i]]==bk){
						ot=bt[now&((1<<p[be[i]][bk])-1)];
						if(kd==0&&ot>0){ok=false;break;}
						if(kd==0) ot=p[be[i]][bk];
						ins(ot),ins(p[be[i]][bk]-ot);
					}
					else{
						ins(bt[now&((1<<p[be[i]][bk])-1)]);
						ins(p[be[i]][bk]-bt[now&((1<<p[be[i]][bk])-1)]);
					}
				}
				if(ok) T[kd][i][gt(ot)]++;
			}
		}
	}
	for(int kd=0;kd<2;kd++) for(int i=1;i<=tot;i++) for(int j=1;j<=tot;j++)
		if(T[kd][i][j]) tr[kd][i].pb(j),kt[kd][i].pb(T[kd][i][j]),T[0][i][j]=1;
	rep(tot) T[0][j][k]|=(T[0][j][i]&T[0][i][k]);
	for(int i=1;i<=tot;i++) for(int j=1;j<=tot;j++)	if(T[0][i][j]) tr[2][i].pb(j);
	for(int i=1;i<=tot;i++) res[i][i]=1; tt=n,init();
	for(int i=1;i<=n;i++) tk[i]=1; int id=gt(0);
	while(K){if(K&1)mul1();mul2(),K>>=1;} int ans=res[1][id];
	for(int i=1;i<=n;i++) ans=mul(ans,qpow(i,mod-2)); printf("%d\n",ans); return 0;
}
