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
const int maxn=70;
const int P=998244353;
int n,m,h,a[maxn][maxn][maxn],b[maxn];
ll tot,val[maxn][maxn][maxn],bj[maxn][maxn][maxn],w,okt;
inline ll poww(ll x,ll y){
	ll base=1;
	while(y){
		if(y&1) base=base*x%P;
		x=x*x%P,y>>=1;
	}
	return base;
}
int main(){
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	n=read(),m=read(),h=read(),w=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=1;k<=h;k++){
				a[i][j][k]=read()^1;
				a[i][j][k]+=a[i-1][j][k];
				a[i][j][k]+=a[i][j-1][k];
				a[i][j][k]-=a[i-1][j-1][k];
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=1;k<=h;k++)
				val[i][j][k]=read();
	for(int ux=1;ux<=n;ux++)
		for(int uy=1;uy<=m;uy++)
			for(int vx=ux;vx<=n;vx++)
				for(int vy=uy;vy<=m;vy++){
					for(int k=1;k<=h;k++)
						b[k]=(a[vx][vy][k]-a[ux-1][vy][k]-a[vx][uy-1][k]+a[ux-1][uy-1][k])!=0;
					for(int uk=1,vk=1;uk<=h;){
						if(b[uk]){
							uk++;continue;
						}
						vk=uk;
						while(vk<h&&!b[vk+1]) vk++;
						for(int k=uk;k<=vk;k++){
							ll tmp=(k-uk+1)*(vk-k+1);
							bj[ux][uy][k]+=tmp;
							bj[ux][vy+1][k]-=tmp;
							bj[vx+1][uy][k]-=tmp;
							bj[vx+1][vy+1][k]+=tmp;
						}
						(okt+=(vk-uk+1)*(vk-uk+2)/2)%=P;
						uk=vk+1;
					}
				}
	tot=(1ll*n*(n+1)*m*(m+1)*h*(h+1)/8)%P;
	ll Ans=0,inv=poww(poww(tot,w),P-2);
	ll Tmp=poww(okt,w);
	for(int k=1;k<=h;k++){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				bj[i][j][k]+=bj[i-1][j][k];
				bj[i][j][k]+=bj[i][j-1][k];
				bj[i][j][k]-=bj[i-1][j-1][k];
				(Ans+=val[i][j][k]*(Tmp-poww((okt-bj[i][j][k])%P,w))%P)%=P;
			}
	}
	Ans=Ans*inv%P;
	printf("%lld\n",(Ans+P)%P);
	return 0;
}













