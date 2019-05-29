#include<map>
#include<cmath>
#include<ctime>
#include<queue>
#include<cstdio>
#include<vector>
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
const int maxn=1e5+100;
int n,m,head[maxn],nex[maxn<<1],v[maxn<<1],w[maxn<<1],num=1;
ll b[maxn],a[maxn];
bool cmp(int x,int y){return x>y;}
inline void add(int x,int y,int z){
	v[++num]=y,nex[num]=head[x],w[num]=z,head[x]=num;
	v[++num]=x,nex[num]=head[y],w[num]=z,head[y]=num;
}
int main(){
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
	n=read(),m=read();
	int err=0;
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		add(x,y,z),b[i]=z;
		if(x>1&&y>1) err=1;
	}
	for(int i=1;i<=m;i++)
		a[i]=read();
	if(!err){
		sort(b+1,b+n,cmp);
		ll Ans=0;
		int las=0;
		for(int i=1;i<n;i+=2)
			Ans+=(b[i]+b[i+1])*2,b[(i+1)/2]=b[i]+b[i+1],las=(i+1)/2;
		for(int i=las+1;i<n;i++) b[i]=0;
		ll tmp=Ans;
		for(int i=1;i<=m;i++){
			if(i<=las){
				tmp=tmp-b[i]+a[i];
				qmin(Ans,tmp);
			}
			printf("%lld ",Ans);
		}
		printf("\n");
		return 0;
	}
	return 0;
}













