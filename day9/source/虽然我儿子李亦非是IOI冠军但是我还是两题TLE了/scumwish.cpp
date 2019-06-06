#include<bits/stdc++.h>
#define to edge[i].v
#define mp make_pair
#define rint register int
#define fgx cerr<<"-------------"<<endl
#define N 25
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
void dbg(){cerr<<endl;}
template<typename A,typename... B>void dbg(A x,B... y){cerr<<x<<" ";dbg(y...);}
#define debug(...) cerr<<#__VA_ARGS__<<"=",dbg(__VA_ARGS__)
const int mod=1e8+7;
int a[N][N],b[N][N]; ll f[2][1100000];
int main()
{	freopen("scumwish.in","r",stdin);
	freopen("scumwish.out","w",stdout);
	int n,m,g=0,v; cin>>n>>m;
	for(rint i=1;i<=n;i++)
	for(rint j=1;j<m;j++) scanf("%d",&a[i][j]),a[i][j]^=1;
	for(rint i=1;i<n;i++)
	for(rint j=1;j<=m;j++) scanf("%d",&b[i][j]),b[i][j]^=1;
	f[0][(1<<m)-1]=1;
	for(rint i=1;i<=n;i++)
	for(rint j=1;j<=m;j++,g^=1)
	for(rint s=0;s<(1<<m);s++)
	if(v=f[g][s]%mod)
	{	f[g][s]=0;
		if(s>>(j-1)&1) f[g^1][s]+=v,f[g^1][s^(1<<j-1)]+=v;
		if(j!=1&&(s>>(j-1)&1)&&!a[i][j-1]&&!(s>>(j-2)&1)) f[g^1][s^(1<<j-2)]+=v;
		if(!b[i-1][j]&&!(s>>(j-1)&1)) f[g^1][s^(1<<j-1)]+=v;
		if(j!=m&&!b[i-1][j]&&!a[i-1][j]&&!(s>>(j-1)&1)&&!(s>>j&1)) f[g^1][s^(3<<j-1)]+=v;
		if(j!=1&&!a[i][j-1]&&!b[i-1][j]&&!(s>>(j-2)&1)&&!(s>>(j-1)&1)) f[g^1][s^(3<<j-2)]+=v;
	}
	cout<<f[g][(1<<m)-1]%mod<<"\n";
	return 0;
}

