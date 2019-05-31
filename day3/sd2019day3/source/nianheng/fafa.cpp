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
const int maxn=20;
int n,k,p[maxn],c[maxn],Ans;
int f[maxn][2];
inline int getmx(){
	int mx=1;
	for(int i=1;i<=n;i++){
		f[i][0]=1,f[i][1]=0;
		for(int j=1;j<i;j++){
			if(p[j]>p[i]) qmax(f[i][1],f[j][0]+1);
			else if(f[j][1]) qmax(f[i][0],f[j][1]+1);
		}
		qmax(mx,f[i][0]),qmax(mx,f[i][1]);
	}
	return mx;
}
void dfs(int x){
	if(x>n){
		if(getmx()==k) Ans++;
		return;
	}
	for(int i=1;i<=n;i++){
		if(c[i]) continue;
		p[x]=i,c[i]=1,dfs(x+1),c[i]=0;
	}
}
int main(){
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	n=read(),k=read();
	dfs(1);
	printf("%d\n",Ans);
	return 0;
}













