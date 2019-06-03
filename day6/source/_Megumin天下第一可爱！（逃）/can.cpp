#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define ull unsigned lint
#define db long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define gc getchar()
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
inline int inn()
{
	int x,ch;while((ch=gc)<'0'||ch>'9');
	x=ch^'0';while((ch=gc)>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch^'0');return x;
}
const int N=10;int ans,vis[N][N],a[N][N];char str[N][N];
inline int dfs(int x,int y,int n,int m,int c)
{
	if(x<1||y<1||x>n||y>m||vis[x][y]||a[x][y]!=c) return 0;vis[x][y]=1;
	return dfs(x+1,y,n,m,c)+dfs(x-1,y,n,m,c)+dfs(x,y+1,n,m,c)+dfs(x,y-1,n,m,c)+1;
}
inline int gabs(int x) { return x<0?-x:x; }
inline int check(int n,int m,int k)
{
	int c0=0,c1=0;rep(i,1,n) rep(j,1,m) if(a[i][j]==0) c0++;else c1++;
	if(gabs(c0-c1)>k) return 0;rep(i,1,n) rep(j,1,m) vis[i][j]=0;
	rep(i,1,n) rep(j,1,m) if(a[i][j]==0&&!vis[i][j]&&dfs(i,j,n,m,0)!=c0) return 0;
	rep(i,1,n) rep(j,1,m) if(a[i][j]==1&&!vis[i][j]&&dfs(i,j,n,m,1)!=c1) return 0;
	return 1;
}
inline int can(int x,int y,int n,int m)
{
	if(x>1&&y>1&&a[x][y]==a[x-1][y]&&a[x][y]==a[x][y-1]&&a[x][y]==a[x-1][y-1]) return 0;
	rep(i,y+1,m) a[x][i]=a[x][y];rep(i,x+1,n) rep(j,1,m) a[i][j]=a[x][y];
	int c=0;rep(i,1,n) rep(j,1,m) vis[i][j]=0,c+=(a[i][j]==a[x][y]);return dfs(x,y,n,m,a[x][y])==c;
}
#define go(c) a[x][y]=c,can(x,y,n,m)?(y==m?calc(x+1,1,n,m,k):calc(x,y+1,n,m,k)):0
inline int calc(int x,int y,int n,int m,int k) { if(x>n) return ans+=check(n,m,k);if(str[x][y]!='B') go(0);if(str[x][y]!='A') go(1);return 0; }
int main()
{
	freopen("can.in","r",stdin),freopen("can.out","w",stdout);
	int n=inn(),m=inn(),k=inn();rep(i,1,n) scanf("%s",str[i]+1);
	return calc(1,1,n,m,k),!printf("%d\n",ans);
}
