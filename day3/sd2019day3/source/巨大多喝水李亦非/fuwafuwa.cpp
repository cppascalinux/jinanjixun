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
int top;
struct node{int v,lc,rc;}a[N];
inline int newnode(int x){++top;a[top].v=x;a[top].lc=a[top].rc=0;return top;}
int ins(int &x,int y)
{	if(!x){x=newnode(y);return 0;}
	if(a[x].v>y) return ins(a[x].lc,y)+1;
	else return ins(a[x].rc,y)+1;
}
int main()
{	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
	int t; cin>>t;
	while(t--)
	{	int a,b,m,n,rt=0; scanf("%d%d%d%d",&a,&b,&m,&n); top=0;
		for(rint i=1;i<=n;i++){(a+=b)%=m;if(i==n)cout<<ins(rt,a)<<"\n";else ins(rt,a);}
	}
	return 0;
}

