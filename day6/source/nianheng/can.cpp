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
const int maxn=1<<25;
int n,m,k,lim,a[10][10],c[10][10],vis[6][6],tot,Ans,bh[10][10];
int uu[4]={0,1,0,-1};
int vv[4]={1,0,-1,0};
char s[10];
void dfs(int x,int y,int C){
	tot++,vis[x][y]=1;
	for(int i=0;i<4;i++){
		int vx=x+uu[i],vy=y+vv[i];
		if(vx<1||vx>n||vy<1||vy>m) continue;
		if(!vis[vx][vy]&&c[vx][vy]==C) dfs(vx,vy,C);
	}
}
int main(){
	freopen("can.in","r",stdin);
	freopen("can.out","w",stdout);
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			if(s[j]=='A') a[i][j]=0;
			if(s[j]=='B') a[i][j]=1;
			if(s[j]=='C') a[i][j]=2;
		}
	}
	lim=1<<n*m;
	int tmp=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			bh[i][j]=++tmp;
	for(int d=0;d<lim;d++){
		int c1=0,c2=n*m,err=0;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				c[i][j]=(d>>bh[i][j]-1)&1;
				if(c[i][j]&&!a[i][j]){
					err=1;
					break;
				} 
				if(!c[i][j]&&a[i][j]==1){
					err=1;
					break;
				}
				if(c[i][j]) c1++,c2--;
				if(c1-k>c2){
					err=1;
					break;
				}
				if(i>1&&j>1){
					int x=c[i][j];
					if(x!=c[i-1][j]) continue;
					if(x!=c[i][j-1]) continue;
					if(x!=c[i-1][j-1]) continue;
					err=1;break;
				}
				if(err) break;
			}
		if(err||abs(c1-c2)>k) continue;
		tot=0,dfs(1,1,c[1][1]);
		if(c[1][1]==1&&tot!=c1) continue;
		if(c[1][1]==2&&tot!=c2) continue;
		for(int i=1;i<=n;i++){
			int ok=0;
			for(int j=1;j<=m;j++)
				if(c[i][j]!=c[1][1]){
					dfs(i,j,c[i][j]);
					ok=1;break;
				}
			if(ok) break;
		}
		if(tot==n*m)
			Ans++;
	}
	printf("%d\n",Ans);
    return 0;
}













