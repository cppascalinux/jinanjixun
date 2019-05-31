#include<bits/stdc++.h>
#define to edge[i].v
#define mp make_pair
#define rint register int
#define fgx cerr<<"-------------"<<endl
#define N 5100
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
void dbg(){cerr<<endl;}
template<typename A,typename... B>void dbg(A x,B... y){cerr<<x<<" ";dbg(y...);}
#define debug(...) cerr<<#__VA_ARGS__<<"=",dbg(__VA_ARGS__)
const int mod=998244353;
int f[N][N];
int main()
{	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	int n,k; cin>>n>>k;
	f[1][1]=1;
	for(rint i=2;i<=n;i++)
	for(rint j=1;j<=i;j++) f[i][j]=((ll)j*f[i-1][j]%mod+f[i-1][j-1]+(j>2?ll(i-j+1)*f[i-1][j-2]%mod:0))%mod;
	cout<<f[n][k];
	return 0;
}

