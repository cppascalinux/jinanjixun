#include<bits/stdc++.h>
#define to edge[i].v
#define mp make_pair
#define rint register int
#define fgx cerr<<"-------------"<<endl
#define N 1000000
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
void dbg(){cerr<<endl;}
template<typename A,typename... B>void dbg(A x,B... y){cerr<<x<<" ";dbg(y...);}
#define debug(...) cerr<<#__VA_ARGS__<<"=",dbg(__VA_ARGS__)
#define qpre(x) (x>=1?pre[x]:1)
#define qsuf(x) (x<=n?suf[x]:1)
int a[N],pre[N],suf[N];
int main()
{	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int t; cin>>t;
	while(t--)
	{	int n,m; scanf("%d%d",&n,&m);
		for(rint i=1;i<=n;i++) scanf("%d",&a[i]),a[i]&=1;
		if(n==1){cout<<(a[1]?"B\n":"A\n");continue;}
		pre[1]=a[1]; pre[2]=a[2]; for(rint i=3;i<=n;i++) pre[i]=pre[i-2]&a[i];
		suf[n]=a[n]; suf[n-1]=a[n-1]; for(rint i=n-2;i;i--) suf[i]=suf[i+2]&a[i];
		if(((n&1)^m)==0) cout<<"A\n";
		else if(!m) cout<<(pre[n]?"B\n":"A\n");
		else
		{	int tag=0;
			for(rint i=1;i<=n;i+=2)
			tag|=qpre(i-2)&(a[i]^a[i+1])&qsuf(i+3),tag|=qpre(i-2)&(a[i]&a[i+1])&qsuf(i+3),tag|=qpre(i)&qsuf(i+3);
			cout<<(tag?"B\n":"A\n");
		}
	}
	return 0;
}

