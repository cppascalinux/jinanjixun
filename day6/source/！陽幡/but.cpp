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
const int N=52,INF=INT_MAX/10;
struct P{
	lint x,y;int w;P(lint _x=0,lint _y=0,int _w=0) { x=_x,y=_y,w=_w; }
	inline int input() { return scanf("%lld%lld%d",&x,&y,&w),0; }
	inline P operator-(const P &p)const { return P(x-p.x,y-p.y); }
	inline bool operator<(const P &p)const { if(x!=p.x) return x<p.x;return y<p.y; }
}p[N];int ans[N],f[N][N][N],g[N][N][N],val[N][N],F[N][N],G[N][N];
inline lint cross(const P &p,const P &q) { return p.x*q.y-p.y*q.x; }
inline lint cross(const P &s,const P &p,const P &q) { return cross(p-s,q-s); }
inline int sgn(lint x) { return x<0?-1:(x>0); } inline void upd(int &x,int y) { x=min(x,y); }
inline int in(const P &v,const P &x,const P &y,const P &z)
{
	int s1=sgn(cross(v,x,y)),s2=sgn(cross(v,y,z)),s3=sgn(cross(v,z,x));return s1==s2&&s2==s3;
}
inline int solve(P *p,int n)
{
	if(n+1<3) return 0;P s=p[0];rep(i,1,n) rep(j,1,n) val[i][j]=0;
	rep(i,1,n) rep(j,i+1,n) rep(k,1,n)
		if(k!=i&&k!=j&&in(p[k],s,p[i],p[j])) val[i][j]+=p[k].w,val[j][i]+=p[k].w;
	rep(i,1,n) rep(j,1,n) if(i!=j) val[i][j]+=p[j].w;
	rep(i,0,n) rep(x,0,n) rep(y,0,n) f[i][x][y]=INF,g[i][x][y]=INF;
	rep(x,1,n) f[1][0][x]=g[1][0][x]=p[x].w;
	rep(i,1,n) rep(x,0,n) rep(y,1,n) if(x^y)
	{
		if(f[i][x][y]<INF) rep(z,1,n)
			if(p[y].x<=p[z].x&&cross(p[x],p[y],p[z])<0) upd(f[i+1][y][z],f[i][x][y]+val[y][z]);
		if(g[i][x][y]<INF) rep(z,1,n)
			if(p[y].x< p[z].x&&cross(p[x],p[y],p[z])>0) upd(g[i+1][y][z],g[i][x][y]+val[y][z]);
	}
	rep(i,1,n) rep(x,1,n) F[i][x]=G[i][x]=INF;
	rep(i,1,n) rep(x,1,n) rep(y,0,n) upd(F[i][x],f[i][y][x]),upd(G[i][x],g[i][y][x]);
	rep(x,1,n) rep(i,1,n) rep(j,1,n-i+1) if(i+j>=3)
		if(max(F[i][x],G[j][x])<INF) upd(ans[i+j],F[i][x]+G[j][x]-p[x].w+s.w);
	return 0;
}
int main()
{
	freopen("but.in","r",stdin),freopen("but.out","w",stdout);
	int n;scanf("%d",&n);rep(i,1,n) p[i].input();
	rep(i,1,n) rep(j,i+1,n) assert(p[i].x!=p[j].x||p[i].y!=p[j].y);
	rep(i,1,n) rep(j,i+1,n) rep(k,j+1,n) assert(cross(p[i],p[j],p[k]));
	sort(p+1,p+n+1);rep(i,3,n) ans[i]=INF;rep(i,1,n) solve(p+i,n-i);
	rep(i,3,n) printf("%d ",ans[i]<INF?ans[i]:-1);return !printf("\n");
}
