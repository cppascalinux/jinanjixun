#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int nm=0; bool fh=true; char cw=getchar();
	for(;!isdigit(cw);cw=getchar()) fh^=(cw=='-');
	for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
	return nm*fh;
}
#define M 200020
bool pre[M],suf[M],p[M];
inline void solve(){
	int n=read(),m=read();
	for(int i=1;i<=n;i++) p[i]=read()&1; if(n==1){puts(p[1]?"B":"A");return;}
	if((n+m+1)&1){puts("A");return;} suf[n+1]=pre[0]=true;
	for(int i=1,sd=1;i<=n;i++,sd^=1) pre[i]=(pre[i-1]&(1^(sd&p[i])^sd));
	for(int i=n,sd=1;i>=1;i--,sd^=1) suf[i]=(suf[i+1]&(1^(sd&p[i])^sd));
	if(n&1){puts(pre[n]?"B":"A");return;}
	for(int i=1;i<n;i++) if((p[i]|p[i+1]|((i^1)&1))&pre[i-1]&suf[i+2]){puts("B");return;}
	puts("A"); return;
} 
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	for(int Cas=read();Cas;--Cas) solve(); 
}

