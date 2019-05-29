#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
inline int read(){
	int nm=0; bool fh=true; char cw=getchar();
	for(;!isdigit(cw);cw=getchar()) fh^=(cw=='-');
	for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
	return fh?nm:-nm;
}
#define M 200020
int n,m,L[M],R[M],W[M],H[M<<2],tot; int p[50];
int main(){
	freopen("wait.in","r",stdin);
	freopen("wait.out","w",stdout);
	n=read(),m=read();
	for(int i=0;i<n;i++) L[i]=read(),R[i]=read()+1,W[i]=read(),H[++tot]=L[i],H[++tot]=R[i];
	sort(H+1,H+tot+1),tot=unique(H+1,H+tot+1)-H-1;
	for(int i=0;i<=n;i++) L[i]=lower_bound(H+1,H+tot+1,L[i])-H,R[i]=lower_bound(H+1,H+tot+1,R[i])-H;
	for(int sta=0;sta<(1<<n);++sta){
		memset(p,0,sizeof(p)); bool ok=true;
		for(int i=0;i<n&&ok;i++){
			if(W[i]>=0&&((W[i]^(sta>>i))&1)) ok=false;
			if((sta>>i)&1) p[L[i]]++,p[R[i]]--;
			else p[L[i]]--,p[R[i]]++;
		} if(!ok) continue;
		for(int i=1;ok&&i<=tot;i++) p[i]+=p[i-1],ok&=(p[i]>=-1&&p[i]<=1);
		if(!ok) continue;
		for(int i=0;i<n;i++) printf("%d%c",(sta>>i)&1,i<n-1?' ':'\n'); return 0; 
	} puts("-1"); return 0;
}

