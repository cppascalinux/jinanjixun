#include<bits/stdc++.h>
#define to edge[i].v
#define mp make_pair
#define rint register int
#define fgx cerr<<"-------------"<<endl
#define N 55
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
void dbg(){cerr<<endl;}
template<typename A,typename... B>void dbg(A x,B... y){cerr<<x<<" ";dbg(y...);}
#define debug(...) cerr<<#__VA_ARGS__<<"=",dbg(__VA_ARGS__)
int f[N][N][N],g[N][N],n,ans[N],w[N];
struct P{int x,y;}a[N];
inline bool operator ==(P x,P y){return mp(x.x,x.y)==mp(y.x,y.y);}
inline bool operator <(P x,P y){return mp(x.x,x.y)<mp(y.x,y.y);}
inline P operator -(P x,P y){return (P){x.x-y.x,x.y-y.y};}
inline ll cross(P x,P y){return (ll)x.x*y.y-(ll)x.y*y.x;}
inline void gao(int S)
{	for(rint i=1;i<=n;i++) if(a[i].x>a[S].x) f[2][S][i]=g[S][i]+w[S]+w[i];
	for(rint i=2;i<=n;i++)
	for(rint x=1;x<=n;x++)
	for(rint y=1;y<=n;y++)
	if(f[i][x][y]!=1e9)
	{	for(rint z=1;z<=n;z++)
		if(cross(a[z]-a[x],a[y]-a[x])>0)
		{	if(z==S) ans[i]=min(ans[i],f[i][x][y]+(a[z].x<a[y].x?-1:1)*g[y][z]);
			else if(cross(a[S]-a[y],a[z]-a[y])>0&&a[z].x>=a[S].x)
			f[i+1][y][z]=min(f[i+1][y][z],f[i][x][y]+(a[z].x>=a[y].x?w[z]:0)+(a[z].x<a[y].x?-1:1)*g[y][z]);
		}
		f[i][x][y]=1e9;
	}
}
int main()
{	freopen("but.in","r",stdin);
	freopen("but.out","w",stdout);
	cin>>n; for(rint i=1;i<=n;i++) scanf("%d%d%d",&a[i].x,&a[i].y,&w[i]),ans[i]=1e9;
	for(rint i=1;i<=n;i++)
	for(rint j=1;j<=n;j++)
	if(i!=j)
	for(rint k=1;k<=n;k++)
	if(k!=i&&k!=j)
	{	P x=a[i],y=a[j]; if(y<x) swap(x,y);
		if(cross(a[k]-x,y-x)>0&&y.x>a[k].x&&x.x<=a[k].x) g[i][j]+=w[k];
	}
	for(rint i=2;i<=n;i++)
	for(rint x=1;x<=n;x++)
	for(rint y=1;y<=n;y++) f[i][x][y]=1e9;
	for(rint i=1;i<=n;i++) gao(i);
	for(rint i=3;i<=n;i++) cout<<(ans[i]==1e9?-1:ans[i])<<" ";
	return 0;
}

