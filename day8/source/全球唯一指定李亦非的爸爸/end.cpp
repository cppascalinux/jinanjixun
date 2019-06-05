#include<bits/stdc++.h>
#define to edge[i].v
#define mp make_pair
#define rint register int
#define fgx cerr<<"-------------"<<endl
#define N 150
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
void dbg(){cerr<<endl;}
template<typename A,typename... B>void dbg(A x,B... y){cerr<<x<<" ";dbg(y...);}
#define debug(...) cerr<<#__VA_ARGS__<<"=",dbg(__VA_ARGS__)
const int mod=1e9+7;
int n,m,f[10010][N],g[N][N][2],go[N][N*2]; char c[10010];
inline void add(int &x,int y){(x+=y)>=mod?x-=mod:x;}
struct S{int s[N][N];S(){memset(s,0,sizeof(s));}}A,I;
inline S operator *(S x,S y)
{	S ans;
	for(rint i=0;i<(1<<n);i++)
	for(rint k=0;k<(1<<n);k++)
	for(rint j=0;j<(1<<n);j++) add(ans.s[i][j],(ll)x.s[i][k]*y.s[k][j]%mod);
	return ans;
}
inline void gao(int S,int *ans)
{	f[1][S]=1;
	for(rint i=1;i<=m;i++)
	for(rint s=S;;s=(s-1)&S)
	{	if(f[i][s])
		{	for(rint t=s;;t=(t-1)&s){(f[i+1][t]+=(ll)f[i][s]*g[s][t][c[i]-'0']%mod)%=mod;if(!t)break;}
			f[i][s]=0;
		}
		if(!s) break;
	}
	for(rint s=S;;s=(s-1)&S){(ans[s]+=f[m+1][s])%=mod,f[m+1][s]=0;if(!s)break;}
}
int main()
{	freopen("end.in","r",stdin);
	freopen("end.out","w",stdout);
	int k; cin>>n>>k; scanf("%s",c+1); m=strlen(c+1);
	for(rint s=0;s<(1<<n);s++)
	for(rint t=0;t<(1<<n+1);t++)
	{	go[s][t]=s;
		for(rint i=1;i<=n;i++)
		if(s>>(i-1)&1)
		{	if((t>>(i-1)&1)<(t>>i&1)) go[s][t]^=s&(1<<i-1);
			else if((t>>(i-1)&1)>(t>>i&1)){go[s][t]=-1;break;}
		}
	}
	for(rint s=0;s<(1<<n);s++)
	for(rint t=s;;t=(t-1)&s)
	{	for(rint _=0;_<(1<<n);_++)
		if(__builtin_popcount(_)%2==0)
		{	if(go[s][_]==t) g[s][t][0]++;
			if(go[s][_|(1<<n)]==t) g[s][t][1]++;
		}
		if(!t) break;
	}
	for(rint s=0;s<(1<<n);s++) gao(s,A.s[s]),I.s[s][s]=1;
	for(;k;k>>=1,A=A*A) if(k&1) I=I*A; cout<<I.s[(1<<n)-1][0];
	return 0;
}

