#include<bits/stdc++.h>
const int P=1e8+7;
int n,m,lr[24][24],ud[24][24],*f,*g;
int read(int l,int r){
	int x;
	scanf("%d",&x);
	assert(l<=x&&x<=r);
	return x;
}
int mx=2;
void calc(int p,int k,int S0,int S1){
	S0<<=p,S1<<=p;
	int m1=1<<p,m2=m1<<k;
	for(int i=0;i<mx;i+=m2){
		for(int j=0;j<m1;++j)g[S1+i+j]+=f[S0+i+j];
	}
}
void trans(int y,int x,int w){
	g=new int[mx]();
	calc(w,1,1,0);
	calc(w,1,0,0);
	if(ud[y][x])calc(w-1,2,0,1);
	if(lr[y][x]){
		calc(w,1,0,1);
		if(ud[y][x])calc(w-1,2,0,3);
		if(ud[y-1][x+1])calc(w,2,0,3);
	}
	for(int i=0;i<mx;++i)g[i]%=P;
	delete[]f;f=g;
}
void ins(){
	g=new int[mx<<1]();
	for(int i=0;i<mx;++i)g[i<<1]=f[i];
	delete[]f;f=g;
	mx<<=1;
}
void del(){
	mx>>=1;
}
int main(){
	freopen( "scumwish.in" , "r" , stdin );
	freopen( "scumwish.out" , "w" , stdout );
	n=read(1,20);
	m=read(1,n);
	for(int i=1;i<=n;++i){
		for(int j=1;j<m;++j)lr[i][j]=read(0,1);
	}
	for(int i=1;i<n;++i){
		for(int j=1;j<=m;++j)ud[i][j]=read(0,1);
	}
	f=new int[mx]();
	f[0]=1;
	for(int a=1;a<m;++a){
		ins();
		for(int x=1,y=a;x<=a;++x,--y)trans(y,x,x);
	}
	for(int a=m;a<n;++a){
		ins();
		for(int x=1,y=a;x<=m;++x,--y)trans(y,x,x);
		del();
	}
	for(int a=1;a<=m;++a){
		for(int x=a,y=n;x<=m;++x,--y)trans(y,x,x-a);
		del();
	}
	printf("%d\n",f[0]);
	return 0;
}
