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
const int maxn=31,maxd=1<<11;
const int P=1e9+7;
int n,m,b[maxn],lim,al,bl,bc[11],aca[11],acb[11];
ll f[2][maxd][maxd],Ans;
int main(){
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	n=read(),m=read(),lim=1<<n,al=bl=1<<n-1;
	for(int i=1;i<=n;i++) b[i]=read();
	int nw=0;
	f[nw^1][al-1][bl-1]=1;
	for(int i=m-1;~i;i--,nw^=1){
		memset(f[nw],0,sizeof(f[nw]));
		for(int k=1;k<=n;k++)
			bc[k]=(b[k]>>i)&1;
		for(int d=0;d<lim;d++){
			for(int k=1;k<=n;k++){
				aca[k]=bc[k]&((d>>k-1)&1);
				acb[k]=bc[k]|((d>>k-1)&1);
			}
			int acae=0,acbe=0;
			for(int k=1;k<n;k++){
				acae|=(aca[k]>aca[k+1])<<k-1;
				acbe|=(acb[k]<acb[k+1])<<k-1;
			}
			int acaf=0,acbf=0;
			for(int k=1;k<n;k++){
				acaf|=(aca[k]==aca[k+1])<<k-1;
				acbf|=(acb[k]==acb[k+1])<<k-1;
			}
			for(int a=0;a<al;a++)
				for(int b=0;b<bl;b++){
					if(!f[nw^1][a][b]) continue;
					if((acae&a)||(acbe&b)) continue;
					(f[nw][a&acaf][b&acbf]+=f[nw^1][a][b])%=P;
				}
		}
	}
	for(int a=0;a<al;a++)
		for(int b=0;b<bl;b++)
			(Ans+=f[nw^1][a][b])%=P;
	printf("%lld\n",Ans);
    return 0;
}












