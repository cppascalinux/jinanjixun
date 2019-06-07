#include <bits/stdc++.h>
using namespace std;
const int maxn=5e5+1;
const int maxv=141;

void chkmax(int &x,int y){y>x?x=y:0;}
void chkmin(int &x,int y){x>y?x=y:0;}

int n,v=140,a[maxn];
int f[maxv][maxn],g[maxv][maxn];
char c[maxn];

int main(){
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
	scanf("%s",c+1);n=strlen(c+1);
	for (int i=1;i<=n;++i) a[i]=c[i]-'0';
	for (int j=0;j<=v;++j) 
		for (int i=1;i<=n+1;++i)
			f[j][i]=g[j][i]=i;
	for (int j=1;j<=v;++j){
		for (int i=1;i<=n;++i) if (a[i]<=j){
			chkmax(f[j][g[j-a[i]][i]],f[j-a[i]][i+1]);
			chkmin(g[j][f[j-a[i]][i+1]],g[j-a[i]][i]);
		}
		for (int i=2;i<=n+1;++i)
		 	chkmax(f[j][i],f[j][i-1]);
		for (int i=n;i>=1;--i)
			chkmin(g[j][i],g[j][i+1]);
	}
	for (int i=1;i<=v;++i)
		if (f[i][1]==n+1)
			return printf("%d\n",i),0;
}
