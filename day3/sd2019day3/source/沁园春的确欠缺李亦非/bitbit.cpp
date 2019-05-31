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
#define M 505
const int dx[]={0,-1,0,1},dy[]={-1,0,1,0};
int n,m,f[M*M],ct[3],dk[4],all,mt[M][M]; char ch[M][M];
bool fg=false,op[M][M],col[M][M],c[M*M];
int fd(int x){return f[x]==x?x:(f[x]=fd(f[x]));}
inline void write(int typ){
	if(fg){for(int i=1;i<=m;i++) for(int j=1;j<i;j++) swap(op[i][j],op[j][i]);swap(n,m);}
	for(int i=1;i<=n;i++,putchar('\n')) for(int j=1;j<=m;j++) putchar(op[i][j]?'1':'0'),op[i][j]?mt[i][j]+=typ:0;
	if(fg) swap(n,m); memset(op,false,sizeof(op));
}
inline void opt(char typ,int kd){
	putchar(typ),putchar('\n');
	if(kd==-1){for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) op[i][j]=true;}
	else{
		int bk=-1;
		for(int i=1;i<=all&&bk==-1;i++)if(fd(i)==i&&c[i]==kd) bk=i;
		for(int i=1,tt=1;i<=n;i++) for(int j=1;j<=m;j++,tt++)
			if(fd(tt)==bk) op[i][j]=true; f[bk]=0;
	} write(typ=='+'?1:-1); return ;
}
int main(){
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	n=read(),m=read(),dk[0]=-1,dk[1]=-m,dk[2]=1,dk[3]=m;
	for(int i=1,tt=1;i<=n;i++){
		scanf("%s",ch[i]+1);
		for(int j=1;j<=m;j++,tt++) c[tt]=col[i][j]=(ch[i][j]=='1'),f[tt]=tt;
	}
	if(n>m){
		for(int i=1;i<=n;i++) for(int j=1;j<i;j++) swap(col[i][j],col[j][i]); swap(n,m),fg=true;
		for(int i=1,tt=1;i<=n;i++) for(int j=1;j<i;j++) c[tt]=col[i][j]; dk[1]=-m,dk[3]=m;
	} all=n*m;
	for(int i=1,tt=1;i<=n;i++) for(int j=1;j<=m;j++,tt++) for(int k=0;k<4;k++){
		int tx=i+dx[k],ty=j+dy[k],tk=tt+dk[k]; if(tx<1||ty<1||tx>n||ty>m) continue;
		if(!(col[i][j]^col[tx][ty])) f[fd(tt)]=fd(tk);
	}
	for(int i=1;i<=all;i++) if(fd(i)==i) ct[c[i]]++;
	
	if(ct[1]==1){puts("1"),opt('+',1);return 0;}
	if(ct[1]==2){puts("2"),opt('+',1),opt('+',1); return 0;}
	if(ct[0]==1){puts("2"),opt('+',-1);opt('-',0);return 0;}
	if(n==1){for(printf("%d\n",ct[1]);ct[1]--;opt('+',1));return 0;}
	puts("3");
	
	for(int i=1;i<=n;i++) op[i][1]=true;
	for(int i=1;i<=n;i++){
		if(i&1){for(int j=2;j<m;j++) op[i][j]=true;}
		else {for(int j=2;j<m;j++) op[i][j]=col[i][j];}
	} puts("+"),write(1);
	
	for(int i=1;i<=n;i++) op[i][m]=true;
	for(int i=1;i<=n;i++){
		if((i^1)&1){for(int j=2;j<m;j++) op[i][j]=true;}
		else {for(int j=2;j<m;j++) op[i][j]=col[i][j];}
	} puts("+"),write(1);
	
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
		if((j>1&&j<m)||(col[i][j]==false)) op[i][j]=true;
	puts("-"),write(-1);
	if(fg) swap(n,m);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) assert(mt[i][j]==ch[i][j]-'0');
	return 0;
}
