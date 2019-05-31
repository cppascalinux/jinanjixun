#include<bits/stdc++.h>
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
#define fgx cerr<<"-----------------------------------"<<endl
#define LL long long
using namespace std;
namespace IO{
	const int BS=(1<<23)+5; int Top=0;
	char Buffer[BS],OT[BS],*OS=OT,*HD,*TL,SS[20]; const char *fin=OT+BS-1;
	char Getchar(){if(HD==TL){TL=(HD=Buffer)+fread(Buffer,1,BS,stdin);} return (HD==TL)?EOF:*HD++;}
	void flush(){fwrite(OT,1,OS-OT,stdout),OS=OT;}
	void Putchar(char c){*OS++ =c;if(OS==fin)flush();}
	void write(int x){
		if(!x){Putchar('0');return;} if(x<0) x=-x,Putchar('-');
		while(x) SS[++Top]=x%10,x/=10;
		while(Top) Putchar(SS[Top]+'0'),--Top;
	}
	int read(){
		int nm=0,fh=1; char cw=getchar();
		for(;!isdigit(cw);cw=getchar()) if(cw=='-') fh=-fh;
		for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
		return nm*fh;
	}
} using namespace IO;
#define M 1000020
int cnt,L[M],R[M],val[M],rt;
inline int ins(int &x,int k,int lev){
	if(!x){x=++cnt,L[x]=R[x]=0,val[x]=k;return lev;}
	return (k>val[x])?ins(R[x],k,lev+1):ins(L[x],k,lev+1);
}
int main(){
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
	for(int Cas=read();Cas;--Cas){
		int a=read(),b=read(),m=read(),now=(a+b)%m,n=read(); cnt=rt=0;
		for(int i=1;i<n;i++,now+=b,now%=m) ins(rt,now,0);
		printf("%d\n",ins(rt,now,0));
	} return 0;
}
