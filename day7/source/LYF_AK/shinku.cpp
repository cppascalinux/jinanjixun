#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
#define fgx cerr<<" -------------------------- "<<endl
#define LL long long
namespace IO{
	const int BS=(1<<24)+5; int Top=0;
	char Buffer[BS],OT[BS],*OS=OT,*HD,*TL,SS[20]; const char *fin=OT+BS-1;
	char Getchar(){if(HD==TL){TL=(HD=Buffer)+fread(Buffer,1,BS,stdin);} return (HD==TL)?EOF:*HD++;}
	void flush(){fwrite(OT,1,OS-OT,stdout),OS=OT;}
	void Putchar(char c){*OS++ =c;if(OS==fin)flush();}
	void write(int x){
		if(!x){Putchar('0');return;} if(x<0) x=-x,Putchar('-');
		while(x) SS[++Top]=x%10,x/=10;
		while(Top) Putchar(SS[Top]+'0'),--Top;
	}
	inline int read(){
		int nm=0; bool fh=true; char cw=Getchar();
		for(;!isdigit(cw);cw=Getchar()) fh^=(cw=='-');
		for(;isdigit(cw);cw=Getchar()) nm=nm*10+(cw-'0');
		return fh?nm:-nm;
	}
} using namespace IO;
#define M 1000200
#define pii pair<int,int> 
#define mp make_pair
#define ps first
#define vl second
int n,m,last[M],p[M],c[11][M],ans[11][M],up[M],dn[M];
struct que{int L,R,id;inline void gtin(int _id){L=read(),R=read(),id=_id;}}q[M];
bool cmp(que i,que j){return i.R<j.R;} pii t[40];
inline void add(int x,int typ,int dt){for(;x<=n;x+=(x&-x)) c[typ][x]+=dt;}
inline int qry(int x,int typ,int res=0){for(;x;x-=(x&-x))res+=c[typ][x];return res;}
inline void mdf(int l,int r,int typ,int dt){if(typ<1||typ>10)return;add(l,typ,dt),add(r+1,typ,-dt);}
int main(){
	freopen("shinku.in","r",stdin);
	freopen("shinku.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++) p[i]=read()+11;
	for(int i=1;i<=m;i++) q[i].gtin(i);
	sort(q+1,q+m+1,cmp);
	for(int i=1,bas,nw=1,tt=0;i<=n;i++,tt=0){
		bas=last[p[i]],t[tt++]=mp(bas,0),last[p[i]]=i;
		for(int k=-11;k<=11;k++) if(last[p[i]+k]>bas) t[tt++]=mp(last[p[i]+k],k+11); sort(t,t+tt);
		for(int sta=0,k=tt-1,mi=11,mx=11;k>0;k--){
			sta|=(1<<t[k].vl);
			while(mi>0&&((sta>>(mi-1))&1)) --mi;
			while((sta>>(mx+1))&1) ++mx;
			mdf(t[k-1].ps+1,t[k].ps,11-mi,-1);
			mdf(t[k-1].ps+1,t[k].ps,mx-11,-1);
			mdf(t[k-1].ps+1,t[k].ps,mx-mi+1,1);
		}
		for(;nw<=m&&q[nw].R==i;nw++) for(int k=1;k<=10;k++)
			ans[k][q[nw].id]=(qry(q[nw].L,k))%10;
	}
	for(int i=1;i<=m;i++,Putchar('\n'))
		for(int k=1;k<=10;k++) Putchar(ans[k][i]+'0');
	flush(); return 0;
}
