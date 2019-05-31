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
#define mod 998244353
inline int add(int x,int y){x+=y;return (x>=mod)?(x-mod):x;}
inline int mul(int x,int y){return (LL)x*(LL)y%mod;}
inline void upd(int &x,int y){x+=y;(x>=mod)?(x-=mod):0;}
int n,m,F[5002][5002];
int main(){
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	F[1][1]=1; n=read(),m=read();
	for(int i=1;i<=n;i++) for(int j=1;j<=i&&j<=m;j++){
		upd(F[i][j],mul(F[i-1][j],j)),upd(F[i][j],F[i-1][j-1]);
		if(j>1) upd(F[i][j],mul(i-j+1,F[i-1][j-2]));
	} printf("%d\n",F[n][m]); return 0;
}

