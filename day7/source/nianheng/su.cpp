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
const int maxn=1e6+100;
int n,m,head[maxn],nex[maxn],v[maxn],num=1;
int fa[maxn],a[maxn],dep[maxn],mx,mn,siz;
inline void add(int x,int y){
	v[++num]=y,nex[num]=head[x],head[x]=num;
}
void dfs(int x,int Fa){
	fa[x]=Fa,dep[x]=dep[Fa]+1;
	for(int i=head[x];i;i=nex[i])
		dfs(v[i],x);
}
inline int getfa(int x){
	while(a[fa[x]]==a[x]) x=fa[x];
	return x;
}
void rev(int x,int z){
	for(int i=head[x];i;i=nex[i])
		if(a[v[i]]==a[x]) rev(v[i],z);
	a[x]=z;
}
void work(int x){
	siz++;
	qmin(mn,dep[x]);
	qmax(mx,dep[x]);
	for(int i=head[x];i;i=nex[i])
		if(a[v[i]]==a[x]) work(v[i]);
}
int main(){
	freopen("su.in","r",stdin);
	freopen("su.out","w",stdout);
	n=read(),read();
	for(int i=2;i<=n;i++)
		add(read(),i);
	for(int i=1;i<=n;i++)
		a[i]=read();
	dfs(1,0);
	m=read();
	while(m--){
		int ms=read(),x=read();
		if(ms==1) a[x]=read();
		if(ms==2) rev(getfa(x),read());
		if(ms==3){
			mn=n,mx=0,siz=0;
			work(getfa(x));
			printf("%d %d %d\n",a[x],siz,mx-mn+1);
		}
	}
	return 0;
}












