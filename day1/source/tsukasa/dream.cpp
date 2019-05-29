#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;
#define mo 998244353
#define MAXN 23

int read()
{
	int ret=0,neg=1;
	char c=getchar();
	while (c<'0' || c>'9'){
		if (c=='-') neg=-1;
		c=getchar();
	}
	while (c>='0' && c<='9'){
		ret=ret*10+c-'0';
		c=getchar();
	}
	return ret*neg;
}

int qpow(int a,int b)
{
	int ret=1;
	while (b){
		if (b&1) ret=1ll*ret*a%mo;
		a=1ll*a*a%mo;
		b>>=1;
	}
	return ret;
}

void add(int &x,int y)
{
	x=(x+y)%mo;
}

int n,m,h,w;
int sum[MAXN][MAXN][MAXN],val[MAXN][MAXN][MAXN],cha[MAXN][MAXN][MAXN];
int ans,cnt;

int main()
{
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	n=read();m=read();h=read();w=read();
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) for (int k=1;k<=h;k++) sum[i][j][k]=1-read();
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) for (int k=1;k<=h;k++) val[i][j][k]=read();
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) for (int k=1;k<=h;k++) sum[i][j][k]+=sum[i-1][j][k];
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) for (int k=1;k<=h;k++) sum[i][j][k]+=sum[i][j-1][k];
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) for (int k=1;k<=h;k++) sum[i][j][k]+=sum[i][j][k-1];
	for (int i1=1;i1<=n;i1++) for (int j1=1;j1<=m;j1++) for (int k1=1;k1<=h;k1++)
		for (int i2=i1;i2<=n;i2++) for (int j2=j1;j2<=m;j2++) for (int k2=k1;k2<=h;k2++){
			int tmp=sum[i2][j2][k2]-sum[i1-1][j2][k2]-sum[i2][j1-1][k2]-sum[i2][j2][k1-1]+sum[i2][j1-1][k1-1]+sum[i1-1][j2][k1-1]+sum[i1-1][j1-1][k2]-sum[i1-1][j1-1][k1-1];
//			printf("%d %d %d    %d %d %d     %d\n",i1,j1,k1,i2,j2,k2,tmp);
			if (tmp==0){
				cnt++;
				cha[i1][j1][k1]++;
				cha[i2+1][j1][k1]--;cha[i1][j2+1][k1]--;cha[i1][j1][k2+1]--;
				cha[i1][j2+1][k2+1]++;cha[i2+1][j1][k2+1]++;cha[i2+1][j2+1][k1]++;
				cha[i2+1][j2+1][k2+1]--;
			}
		}
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) for (int k=1;k<=h;k++) cha[i][j][k]+=cha[i-1][j][k];
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) for (int k=1;k<=h;k++) cha[i][j][k]+=cha[i][j-1][k];
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) for (int k=1;k<=h;k++) cha[i][j][k]+=cha[i][j][k-1];
	int inv=1ll*n*(n+1)%mo*m%mo*(m+1)%mo*h%mo*(h+1)%mo*qpow(8,mo-2)%mo;inv=qpow(inv,mo-2);
	int ni=qpow(cnt,mo-2);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) for (int k=1;k<=h;k++){
//		printf("%d %d %d %d\n",i,j,k,cha[i][j][k]);
		int tmp=1ll*cha[i][j][k]*ni%mo;tmp=(1-tmp+mo)%mo;
		tmp=qpow(tmp,w);tmp=(1-tmp+mo)%mo;
		add(ans,1ll*tmp*val[i][j][k]%mo);
	}
	printf("%lld",1ll*ans*qpow(cnt,w)%mo*qpow(inv,w)%mo);
}
