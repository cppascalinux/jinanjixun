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
const int maxn=1e3+100;
const int inf=0x3f3f3f3f;
int n,a[maxn];
int f[maxn][maxn];
char s[maxn];
int main(){
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
	scanf("%s",s+1),n=strlen(s+1);
	for(int i=1;i<=n;i++) a[i]=s[i]-'0';
	for(int L=2;L<=n+1;L++)
		for(int i=1,j=i+L-1;j<=n+1;i++,j++){
			f[i][j]=inf;
			for(int k=i;k<j;k++)
				qmin(f[i][j],max(f[i][k],f[k+1][j])+a[k]);
		}
	printf("%d\n",f[1][n+1]);
	return 0;
}












