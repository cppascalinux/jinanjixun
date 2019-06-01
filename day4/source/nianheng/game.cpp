#include<map>
#include<ctime>
#include<cmath>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
inline int read(){
	int ans=0,fh=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		ans=ans*10+ch-'0',ch=getchar();
	return ans*fh;
}
const int maxn=1e5+100;
int T,n,m,a[maxn],f[2][21][1<<20],cz[2][21][1<<20],kk[21];
int lim,S;
int dfs(int nw,int L,int d){
	if(cz[nw][L][d]) return f[nw][L][d];
	int dc=d&kk[1],dr,Ans=0;
	for(int i=1;i<L;i++){
		dc&=kk[i+1],dr=d&((1<<i-1)-1);
		int x=(d>>i-1)&1,y=(d>>i)&1;
		int z=(x+y)%2;
		int tmp=dr|(dc>>1)|(z<<i-1);
		if(!dfs(nw^1,L-1,tmp)){
			Ans=1;
			break;
		}
		z=x*y;
		tmp=dr|(dc>>1)|(z<<i-1);
		if(!dfs(nw^1,L-1,tmp)){
			Ans=1;
			break;
		}
	}
	f[nw][L][d]=Ans,cz[nw][L][d]=1;
	return Ans;
}
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	T=read();
	for(int i=1;i<=20;i++)
		kk[i]=(lim-1)^(1<<i-1);
	f[0][1][0]=1,f[1][1][0]=0;
	f[0][1][1]=0,f[1][1][1]=1;
	cz[0][1][0]=1,cz[1][1][0]=1;
	cz[0][1][1]=1,cz[1][1][1]=1;
	while(T--){
		n=read(),m=read();
		for(int i=1;i<=n;i++) a[i]=read()%2;
		if(n<=20){
			lim=1<<n,S=0;
			for(int i=1;i<=n;i++)
				S|=a[i]<<i-1;
			if(dfs(m,n,S)) printf(m?"B\n":"A\n");
			else printf(m?"A\n":"B\n");
		}
		else{
			int err=0;
			for(int i=1;i<=n;i++)
				if(!a[i]){
					err=1;
					break;
				}
			if(err) printf("A\n");
			else printf(n%2?"B\n":"A\n");
		}
	}
	return 0;
}












