#include<map>
#include<cmath>
#include<ctime>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define qmin(x,y) (x=min(x,y))
#define qmax(x,y) (x=max(x,y))
#define mp(x,y) make_pair(x,y)
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
const int maxn=600;
int T,n,m,a,b,p[maxn],tot,son[maxn][2],rt;
inline void ins(int &o,int z){
	if(!o){
		o=++tot,p[o]=z;
		return;
	}
	if(p[o]>z) ins(son[o][0],z);
	else ins(son[o][1],z);
}
inline int work(int &o,int z,int Dp){
	if(!o) return Dp;
	if(p[o]>z) work(son[o][0],z,Dp+1);
	else work(son[o][1],z,Dp+1);
}
int main(){
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
	T=read();
	while(T--){
		a=read(),b=read();
		m=read(),n=read();
		memset(son,0,sizeof(son));
		tot=0,rt=0;
		for(int i=1;i<n;i++)
			ins(rt,(a+1ll*i*b)%m);
		printf("%d\n",work(rt,(a+1ll*n*b)%m,0));
	}
	return 0;
}













