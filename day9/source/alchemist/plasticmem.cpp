#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
const int maxn=1000001;

int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}

int n,m,a[maxn];

int main(){
	freopen("plasticmem.in","r",stdin);
	freopen("plasticmem.out","w",stdout);
	n=read(),m=read();
	int l=0,r=0;
	for (int i=1;i<=n;++i)
		a[i]=read();
	for (int k=1;k<=m;++k){
		int op=read(),l=read(),r=read();
		if (op==1){
			for (int k=l;k<=r;++k)
			a[k]=0;
		}
		if (op==2){
			for (int k=l;k<=r;++k)
			a[k]=1;
		}
		if (op==3){
			for (int k=l;k<r;++k)
			a[k]|=a[k+1];
		}
		if (op==4){
			for (int k=r;k>l;--k)
			a[k]|=a[k-1];
		}
		if (op==5){
			for (int k=l;k<r;++k)
			a[k]&=a[k+1];
		}
		if (op==6){
			for (int k=r;k>l;--k)
			a[k]&=a[k-1];
		}
		if (op==7){
			int res=0;
			for (int k=l;k<=r;++k)
			res+=a[k];
			printf("%d\n",res);
		}
	}
}
