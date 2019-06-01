#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAXN 111111

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

int t,n,m;
int a[MAXN];
int cnt[2];
bool z[MAXN],f[MAXN];

int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout); 
	t=read();
	while (t--){
		n=read();m=read();
		for (int i=1;i<=n;i++) a[i]=read()%2,cnt[a[i]]++;
		if ((n%2)==m){
			puts("A");
			continue;
		}
		if (n%2){
			bool flag=true;
			for (int i=1;i<=n;i+=2) if (a[i]==0) flag=false;
			if (flag) puts("B");
			else puts("A");
			continue;
		}
		else{
			z[1]=a[1];
			for (int i=3;i<=n;i+=2) z[i]=z[i-2]&a[i];
			f[n]=a[n];
			for (int i=n-2;i>0;i--) f[i]=f[i+2]&a[i];
			bool flag=false;
			for (int i=1;i<=n;i+=2){
				int l=i-2;int r=i+3;
				if ((a[i]!=0 || a[i+1]!=0) && (l>0 ? z[l] : 1) && (r<=n ? f[r] : 1)) flag=true;
			}
			for (int i=2;i<=n;i+=2){
				int l=i-1;int r=i+2;
				if ((l>0 ? z[l] : 1) && (r<=n ? f[r] : 1)) flag=true;
			}
			if (flag) puts("B");
			else puts("A");
		}
	}
}
