#include <bits/stdc++.h>
using namespace std;
const int maxn=1025;
const int md=1e9+7;

int S,n,k,len,ans;
char s[51];
int f[8][maxn];
int g[8][maxn];

void inc(int &x,int y){x=x+y>=md?x+y-md:x+y;}

int main(){
	freopen("end.in","r",stdin);
	freopen("end.out","w",stdout);
	scanf("%d%d",&n,&k);
	scanf("%s",s+1);
	len=strlen(s+1);
	for (int i=1;i<=len;++i)
	S=(S<<1)+s[i]-'0';
	for (int i=0;i<S;++i){
		f[1][i]=1;
		for (int k=1;k<=min(i,n-1);++k)
			for (int j=0;j<S;++j)
				inc(f[k+1][j^i],g[k][j]);
		for (int k=1;k<=n;++k)
			for (int j=0;j<S;++j)
				inc(g[k][j],f[k][j]),f[k][j]=0;
	}
	printf("%d\n",g[n][0]);
}
