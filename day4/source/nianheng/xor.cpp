#include<map>
#include<ctime>
#include<cmath>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define qmax(x,y) (x=max(x,y))
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
const int maxn=2100;
int m,n,q,ok[maxn],siz[maxn],fa[maxn];
int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
inline void merge(int x,int y){
	x=getfa(x),y=getfa(y);
	if(x==y) return;
	fa[x]=y,siz[y]+=siz[x];
}
inline int work(){
	for(int i=1;i<=n;i++)
		fa[i]=i,siz[i]=1;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(ok[(i-1)^(j-1)]) merge(i,j);
	int tmp=0;
	for(int i=1;i<=n;i++)
		qmax(tmp,siz[i]);
	return tmp;
}
int main(){
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	m=read(),q=read(),n=1<<m;
	while(q--){
		int ms=read(),x=read();
		if(ms==1) ok[x]=1;
		else ok[x]=0;
		printf("%d\n",work());
	}
	return 0;
}












