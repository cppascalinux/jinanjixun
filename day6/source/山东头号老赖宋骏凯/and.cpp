#include<bits/stdc++.h>
#define to edge[i].v
#define mp make_pair
#define rint register int
#define fgx cerr<<"-------------"<<endl
#define N 1050
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
void dbg(){cerr<<endl;}
template<typename A,typename... B>void dbg(A x,B... y){cerr<<x<<" ";dbg(y...);}
#define debug(...) cerr<<#__VA_ARGS__<<"=",dbg(__VA_ARGS__)
const int mod=1e9+7;
int a[50],f[50][N],g[50][N],go[N][N*2];
int main()
{	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	int n,m,x; cin>>n>>m;
	for(rint i=1;i<=n;i++)
	{	scanf("%d",&x);
		for(rint j=0;j<m;j++) a[j]|=(x>>j&1)<<(i-1);
	}
	f[0][0]=g[0][0]=1;
	for(rint s=0;s<(1<<n-1);s++)
	for(rint t=0;t<(1<<n);t++)
	for(rint i=0;i<n-1;i++)
	if((t>>i&1)&&!(t>>(i+1)&1)) go[s][t]|=1<<i;
	else if((t>>i&1)==(t>>(i+1)&1)) go[s][t]|=(s>>i&1)<<i;
	for(rint i=0;i<m;i++)
	for(rint s=0;s<(1<<n-1);s++)
	if(f[i][s])
	{	for(rint t=0;t<(1<<n);t++)
		if(!(t&(a[i]^((1<<n)-1)))) (f[i+1][go[s][t]]+=f[i][s])%=mod;
	}
	memset(go,0,sizeof(go));
	for(rint s=0;s<(1<<n-1);s++)
	for(rint t=0;t<(1<<n);t++)
	for(rint i=0;i<n-1;i++)
	if(!(t>>i&1)&&(t>>(i+1)&1)) go[s][t]|=1<<i;
	else if((t>>i&1)==(t>>(i+1)&1)) go[s][t]|=(s>>i&1)<<i;
	for(rint i=0;i<m;i++)
	for(rint s=0;s<(1<<n-1);s++)
	if(g[i][s])
	{	for(rint t=0;t<(1<<n);t++)
		if(!((t^((1<<n)-1))&a[i])) (g[i+1][go[s][t]]+=g[i][s])%=mod;
	}
	cout<<(ll)f[m][0]*g[m][0]%mod;
	return 0;
}

