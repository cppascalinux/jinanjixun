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
const int maxn=3e4+100;
int n,m,L[maxn],R[maxn],w[maxn],b[maxn<<1],mx,cnt[maxn<<1];
inline void lsh(){
	for(int i=1;i<=m;i++)
		b[++mx]=L[i],b[++mx]=R[i];
	sort(b+1,b+mx+1),mx=unique(b+1,b+mx+1)-b-1;
	for(int i=1;i<=m;i++){
		L[i]=lower_bound(b+1,b+mx+1,L[i])-b;
		R[i]=lower_bound(b+1,b+mx+1,R[i])-b;
	}
}
int main(){
	freopen("wait.in","r",stdin);
	freopen("wait.out","w",stdout);
	m=read(),n=read();
	for(int i=1;i<=m;i++)
		L[i]=read(),R[i]=read(),w[i]=read();
	lsh();
	if(m<=20){
		int lim=1<<m;
		for(int d=0;d<lim;d++){
			int err=0;
			for(int i=1;i<=m;i++)
				if(w[i]!=-1&&w[i]!=((d>>i-1)&1)){
					err=1;
					break;
				}
			if(err) continue;
			memset(cnt,0,sizeof(cnt));
			for(int i=1;i<=m;i++)
				if((d>>i-1)&1) cnt[L[i]]++,cnt[R[i]+1]--;
				else cnt[L[i]]--,cnt[R[i]+1]++;
			int tmp=0;
			for(int i=1;i<=mx;i++){
				tmp+=cnt[i];
				if(tmp<-1||tmp>1){
					err=1;
					break;
				}
			}
			if(!err){
				for(int i=1;i<=m;i++)
					printf("%d ",(d>>i-1)&1);
				printf("\n");
				return 0;
			}
		}
		printf("-1\n");
		return 0;
	}
	return 0;
}













