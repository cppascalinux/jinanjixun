#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
#define fgx cerr<<" --------------------------------- "<<endl
#define LDB long double
inline int read(){
	int nm=0; bool fh=true; char cw=getchar();
	for(;!isdigit(cw);cw=getchar()) fh^=(cw=='-');
	for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
	return fh?nm:-nm;
}
#define M 120
#define mod 1000000007
#define LL long long
int n,m,T,d[102],ct[102][102];
LDB p,pos[102][102],con[102],bas[102];
int main(){
	freopen("distribution.in","r",stdin);
	freopen("distribution.out","w",stdout);
	cin>>T>>p;
	pos[0][0]=1.0;
	for(int i=0;i<100;i++) for(int j=0;j<=i;j++) pos[i+1][j+1]+=pos[i][j]*p,pos[i+1][j]+=pos[i][j]*(1.0-p);
	for(int i=1;i<=100;i++) con[i]=-i*1.0*p,bas[i]=sqrtl(i*p*(1.0-p));
	for(int i=1;i<=100;i++) for(int k=1;k<=i;k++) pos[i][k]+=pos[i][k-1];
	while(T--){
		m=read(); memset(d,0,sizeof(d)),memset(ct,0,sizeof(ct));
		for(int i=1;i<=m;i++){
			LDB x,l,r; cin>>x; int k;
			for(n=1;n<=100;n++){
				l=x*bas[n]-con[n]-0.5,r=x*bas[n]-con[n]+0.5;
				if(r<0.0||l>n*1.0) continue;
				d[n]++; ct[n][(int)ceil(l)]++;
			}
		}
		LDB now=1e18,val; int res=1;
		for(n=2;n<=100;n++) if(d[n]==m){
			val=0.0;
			for(int k=1;k<=n;k++) val+=fabs(pos[n][k]-(ct[n][k]/(m*1.0))); 
			val/=n;
			if(now>val) now=val,res=n;
		}
		printf("%d\n",res);
	}
	return 0;
}

/*

2
0.5
3 0.1 0.05 -0.2

3 0.05 -0.1 0.01

*/
