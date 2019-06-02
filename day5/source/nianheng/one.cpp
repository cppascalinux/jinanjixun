#include<map>
#include<set>
#include<ctime>
#include<queue>
#include<cmath>
#include<bitset>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mp(x,y) make_pair(x,y)
#define qmin(x,y) (x=min(x,y))
#define qmax(x,y) (x=max(x,y))
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
inline ll read(){
	ll ans=0,fh=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		ans=(ans<<1)+(ans<<3)+ch-'0',ch=getchar();
	return ans*fh;
}
const int maxn=200;
const ll P=1e9+7;
struct node{
	int a[21];
}s,t;
int n,tot;
ll d[maxn][maxn],ps;
map<int,int>mp;
inline ll poww(ll x,ll y){
	ll base=1;
	while(y){
		if(y&1) base=base*x%P;
		x=x*x%P,y>>=1;
	}
	return base;
}
inline void add(int x,int y){
	d[x][y]=ps;
}
inline int getbh(node nw){
	int tmp=0;
	for(int i=1;i<=n;i++)
		tmp=tmp*10+nw.a[i];
	return mp[tmp];
}
inline void setbh(node nw,int z){
	int tmp=0;
	for(int i=1;i<=n;i++)
		tmp=tmp*10+nw.a[i];
	mp[tmp]=z;
}
void dfs(node nw){
	if(getbh(nw)) return;
	setbh(nw,++tot);
	int x=tot;
	if(x==getbh(t)) return;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			swap(nw.a[i],nw.a[j]),dfs(nw);
			int y=getbh(nw);swap(nw.a[i],nw.a[j]);
			add(x,y);
		}
}
inline void gauss(){
	for(int i=1;i<=tot;i++) d[i][i]=1;
	for(int i=1;i<=tot;i++) d[i][tot+1]=1;
	d[getbh(t)][tot+1]=0;
	for(int i=1;i<=tot;i++){
		for(int j=i;j<=tot;j++)
			if(d[j][i]){
				for(int k=1;k<=n;k++)
					swap(d[i][k],d[j][k]);
				break;
			}
		ll inv=poww(d[i][i],P-2);
		for(int k=i;k<=tot+1;k++)
			d[i][k]=d[i][k]*inv%P;
		for(int j=1;j<=tot;j++){
			if(i==j) continue;
			ll tmp=d[j][i];
			for(int k=i;k<=tot+1;k++)
				d[j][k]=(d[j][k]-d[i][k]*tmp%P+P)%P;
		}
	}
	printf("%lld ",d[1][tot+1]);
}
int main(){
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	n=read(),ps=P-poww(1ll*n*(n-1)/2%P,P-2);
	for(int i=1;i<=n;i++)
		s.a[i]=read(),t.a[i]=i;
	dfs(s),gauss();
	return 0;
}











