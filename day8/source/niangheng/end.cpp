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
const int maxn=12,maxd=1<<maxn;
const int P=1e9+7;
int n,k,len,lim,mx;
int f[2][maxn][maxd];
char s[maxn];
int main(){
	freopen("end.in","r",stdin);
	freopen("end.out","w",stdout);
	n=read(),k=read(),scanf("%s",s+1);
	len=strlen(s+1),lim=1<<len;
	for(int i=1;i<=len;i++) 
		mx=(mx<<1)+s[i]-'0';
	int nw=0;f[0][0][0]=1;
	for(int d=0;d<mx;d++){
		nw^=1,memset(f[nw],0,sizeof(f[nw]));
		for(int i=0;i<=n;i++)
			for(int j=0;j<lim;j++){
				if(!f[nw^1][i][j]) continue;
				int tmp=j;
				for(int z=0;z<len;z++)
					if((d>>z)&1) tmp^=1<<z;
				(f[nw][i+1][tmp]+=f[nw^1][i][j])%=P;
				(f[nw][i][j]+=f[nw^1][i][j])%=P;
			}
	}
	printf("%d\n",f[nw][n][0]);
    return 0;
}















