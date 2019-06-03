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
const int maxn=100;
struct point{
	int x,y,z;
}p[maxn];
int n,lim,st[maxn],tp;
bool cmp(point x,point y){
	return x.x<y.x;
}
inline void work(){
	
}
int main(){
	freopen("but.in","r",stdin);
	freopen("but.out","w",stdout);
	n=read(),lim=1<<n;
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		p[i]=(point){x,y,read()};
	}
	sort(p+1,p+n+1,cmp);
	for(int d=0;d<lim;d++){
		for(int i=1;i<=n;i++)
			cz[i]=(d>>i-1)&1;
		work();
	}
    return 0;
}













