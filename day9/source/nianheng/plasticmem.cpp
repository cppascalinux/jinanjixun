#include<map>
#include<cmath>
#include<ctime>
#include<queue>
#include<vector>
#include<cstdio>
#include<bitset>
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
int n,m;
bitset<maxn>a,mx;
inline bitset<maxn> get0(int l,int r){
	return (mx>>n-l+1)|((mx<<r)&mx);
}
int main(){
	freopen("plasticmem.in","r",stdin);
	freopen("plasticmem.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) mx[i]=1;
	while(m--){
		int ms=read(),l=read(),r=read();
		if(ms==1) a&=get0(l,r);
		if(ms==2) a|=(mx^get0(l,r));
		if(ms==3){
			bitset<maxn> tmp=a&(mx^get0(l+1,r));
			a|=tmp>>1,a[n+1]=0;
		}
		if(ms==4){
			bitset<maxn> tmp=a&(mx^get0(l,r-1));
			a|=tmp<<1;
		}
		if(ms==5){
			bitset<maxn> sxz=get0(l+1,r);
			bitset<maxn> tmp=a&(mx^sxz)|sxz;
			tmp[n+1]=1,a&=tmp>>1;
		}
		if(ms==6){
			bitset<maxn> sxz=get0(l,r-1);
			bitset<maxn> tmp=a&(mx^sxz)|sxz;
			tmp[0]=1,a&=tmp<<1;
		}
		if(ms==7) printf("%d\n",(a&(mx^get0(l,r))).count());
		else a&=mx; 
	}
	return 0;
}













