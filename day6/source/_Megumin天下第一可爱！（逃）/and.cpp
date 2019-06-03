#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define mod 1000000007
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
const int N=10,M=30,S=(1<<10)+3;
int b[N],dp[2][2][S][S][2];
inline void upd(int &x,int y) { ((x+=y)>=mod)?x-=mod:0; }
int main()
{
	freopen("and.in","r",stdin),freopen("and.out","w",stdout);
	int n=inn(),m=inn(),all=(1<<(n-1))-1;rep(i,0,n-1) b[i]=inn();
	dp[(m-1)&1][0][all][all][0]=dp[(m-1)&1][0][all][all][1]=1;
	for(int i=m-1,v;i>=0;i--)
	{
		int (*now)[S][S][2]=dp[i&1];
		rep(j,0,n-2)
		{
			int (*cur)[S][2]=now[j&1],(*nxt)[S][2]=now[(j+1)&1];
			rep(s1,0,all) rep(s2,0,all) rep(k,0,1) nxt[s1][s2][k]=0;
			rep(s1,0,all) rep(s2,0,all) rep(k,0,1) if((v=cur[s1][s2][k])) rep(t,0,1)
			{
				int x1=(b[j]>>i)&k,x2=((b[j]>>i)^1)&(k^1),
					y1=(b[j+1]>>i)&t,y2=((b[j+1]>>i)^1)&(t^1);
				if(((s1>>j)&1)&&x1>y1) continue;int t1=s1;
				if(((s2>>j)&1)&&x2>y2) continue;int t2=s2;
				if(((s1>>j)&1)&&x1<y1) t1^=1<<j;
				if(((s2>>j)&1)&&x2<y2) t2^=1<<j;
				upd(nxt[t1][t2][t],v);
			}
		}
		if(i==0) break;
		int (*cur)[S][2]=now[(n-1)&1],(*nxt)[S][S][2]=dp[(i-1)&1],(*qwq)[S][2]=nxt[0];
		rep(s1,0,all) rep(s2,0,all) rep(k,0,1) qwq[s1][s2][k]=0;
		rep(s1,0,all) rep(s2,0,all) rep(k,0,1) if((v=cur[s1][s2][k]))
			rep(t,0,1) upd(qwq[s1][s2][t],v);
	}
	int ans=0,v,(*now)[S][S][2]=dp[0],(*cur)[S][2]=now[(n-1)&1];
	rep(s1,0,all) rep(s2,0,all) rep(k,0,1) if((v=cur[s1][s2][k])) upd(ans,v);
	return !printf("%d\n",ans);
}
