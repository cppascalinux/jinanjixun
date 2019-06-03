#include <bits/stdc++.h>
using namespace std;
const int maxn=11;
const int maxm=32;
const int maxs=200;
const int md=1e9+7;
typedef long long ll;

int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x;
}

void inc(int &x,int y){x=(x+y)%md;}

int n,m,ans;
int a[maxn],b[maxn],c[maxn];
int x[maxn],y[maxn];
int f[maxm][maxs][maxs]; 

int main(){
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	n=read(),m=read();
	for (int i=1;i<=n;++i) b[i]=read();
	f[m][1][1]=1;
	for (int j=m-1;~j;--j) for (int S=0;S<1<<n;++S){
		for (int i=1;i<=n;++i) c[i]=(b[i]>>j)&1;
		for (int i=1;i<=n;++i) a[i]=(S>>(i-1))&1;
		for (int i=1;i<=n;++i) x[i]=c[i]&a[i];
		for (int i=1;i<=n;++i) y[i]=c[i]|a[i];
		int rxv=0,ryv=0,nxt=1,nyt=1;
		for (int i=2;i<=n;++i) if (x[i]<x[i-1]) rxv|=(1<<(i-1));
		for (int i=2;i<=n;++i) if (y[i-1]<y[i]) ryv|=(1<<(i-1));
		for (int i=2;i<=n;++i) if (x[i]>x[i-1]) nxt|=(1<<(i-1));
		for (int i=2;i<=n;++i) if (y[i-1]>y[i]) nyt|=(1<<(i-1));
		for (int pxe=1;pxe<1<<n;++pxe) for (int pye=1;pye<1<<n;++pye){
			if ((pxe^rxv)&rxv) continue;
			if ((pye^ryv)&ryv) continue;
			inc(f[j][nxt|pxe][nyt|pye],f[j+1][pxe][pye]);
		}
	}
	for (int X=1;X<1<<n;++X) for (int Y=1;Y<1<<n;++Y)
	inc(ans,f[0][X][Y]);
	printf("%d\n",ans);
}
