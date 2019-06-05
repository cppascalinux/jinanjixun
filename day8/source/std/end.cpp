#include<cstdio>
#include<cstring>
const int P=1e9+7;
typedef long long i64;
typedef int mat[8][8];
int n,k,sv=0,len,N;
char s[155555];
int G[10];
mat x,y0,y1,y,c;
void clr(mat a,int v=0){
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j)a[i][j]=0;
		a[i][i]=v;
	}
}
void cpy(mat a,mat b){
	for(int i=0;i<N;++i)
	for(int j=0;j<N;++j)
		a[i][j]=b[i][j];
}
void mul(mat a,mat b){
	clr(c);
	for(int i=0;i<N;++i)
	for(int k=0;k<N;++k)
	for(int j=0;j<N;++j)
		c[i][j]=(c[i][j]+i64(b[i][k])*a[k][j])%P;
	cpy(a,c);
}
int col[20],ct[20];
int inv(int a){
	int v=1;
	for(int n=P-2;n;n>>=1,a=i64(a)*a%P)if(n&1)v=i64(v)*a%P;
	return v;
}
int _cs(int t,int n){
	return n?1<<(n-1):t^1;
}
i64 _A(int n,int m){
	i64 v=1;
	for(int i=0;i<m;++i)v=v*(n-i)%P;
	return v;
}
i64 _fiv(int a){
	i64 v=1;
	for(int i=2;i<=a;++i)v=v*i%P;
	return inv(v);
}
i64 _C(int n,int m){
	return _A(n,m)*_fiv(m)%P;
}
void dfs(int c,int w,int mx){
	if(w==c){
		if(col[c-1]==c-1)return;
		int c1=0;
		for(int a=0;a<mx;++a)c1+=ct[a]&1;
		G[c]=(G[c]-G[c1]*_A(sv-c1,mx-c1))%P;
		return;
	}
	for(int i=0;i<=mx;++i){
		col[w]=i;
		++ct[i];
		dfs(c,w+1,mx+(i==mx));
		--ct[i];
	}
}
int pw(int a,int n){
	int v=1;
	for(;n;n>>=1,a=1ll*a*a%P)if(n&1)v=1ll*v*a%P;
	return v;
}
int main(){
	freopen( "end.in" , "r" , stdin );
	freopen( "end.out" , "w" , stdout );
	if(scanf("%d%d%s",&n,&k,s)!=3||n>7||n<3||k>100000)return 1;
	len=strlen(s);
	if(len>10000)return 1;
	for(int i=0;i<len;++i)s[i]-='0',sv=(sv*2+s[i])%P;
	int a=pw(2,len),b=sv;
	for(int i=1;i<k;++i)sv=(i64(sv)*a+b)%P;
	for(int c=0;c<=n;++c){
		if((n-c)&1)continue;
		if(c<2)G[c]=1;
		else{
			N=c+1;
			clr(x,1);clr(y,1);
			clr(y0);clr(y1);
			for(int a=0;a<=c;++a){
				y0[a][a]=_cs(0,c-a);
				for(int b=a;b<=c;++b){
					y1[a][b]=_cs(a&1,c-b)*_C(b,a)%P;
				}
			}
			for(int a=0;a<len;++a)mul(y,s[a]?y1:y0);
			for(int a=k;a;a>>=1,mul(y,y))if(a&1)mul(x,y);
			G[c]=x[0][c];
			dfs(c,0,0);
		}
	}
	printf("%lld\n",(G[n]*_fiv(n)%P+P)%P);
	return 0;
}
