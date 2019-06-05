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
const int N=100010;
vector<int> g[N];int lst[N],lc,col[N],d[N];
inline int dfs(int x,int fa=0)
{
	lst[++lc]=x;
	Rep(i,g[x]) if(g[x][i]!=fa&&g[x][i][col]==x[col]) dfs(g[x][i],x);
	return 0;
}
int main()
{
	freopen("su.in","r",stdin),freopen("su.out","w",stdout);
	int n=inn(),x;d[0]=-1;
	rep(i,1,n) x=inn(),(x?g[x].pb(i),g[i].pb(x),0:0),d[i]=d[x]+1;
	rep(i,1,n) col[i]=inn();int m=inn();
	while(m--)
	{
		int tp=inn(),x,y;
		if(tp==1) x=inn(),col[x]=inn();
		else{
			x=inn(),lc=0;dfs(x);
			if(tp==2) { y=inn();rep(i,1,lc) lst[i][col]=y; }
			else{
				printf("%d %d ",col[x],lc);int mn=d[x],mx=d[x];
				rep(i,1,lc) mn=min(mn,d[lst[i]]),mx=max(mx,d[lst[i]]);
				printf("%d\n",mx-mn+1);
			}
		}
	}
	return 0;
}
