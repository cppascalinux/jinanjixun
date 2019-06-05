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
#define M 200020
int n,m,p[M];
int main(){
	freopen("busy.in","r",stdin);
	freopen("busy.out","w",stdout);
	n=read(),m=read();	
	for(int i=1;i<=n;i++) p[i]=read();
	for(int op,last=0,x,y;m;--m){
		op=read(),x=read()^last,y=read()^last;
		if(op==1){
			for(int i=1;i<=n;i++) if(p[i]==x) p[i]=y;
			continue;
		} int ans=n+1;
		for(int i=1,lastx=-n,lasty=-n;i<=n;i++){
			if(p[i]==x) ans=min(ans,i-lasty),lastx=i;
			if(p[i]==y) ans=min(ans,i-lastx),lasty=i;
		}
		if(ans>n) puts("Chtholly"),last=0;
		else printf("%d\n",last=ans);
	}
	return 0;
}
