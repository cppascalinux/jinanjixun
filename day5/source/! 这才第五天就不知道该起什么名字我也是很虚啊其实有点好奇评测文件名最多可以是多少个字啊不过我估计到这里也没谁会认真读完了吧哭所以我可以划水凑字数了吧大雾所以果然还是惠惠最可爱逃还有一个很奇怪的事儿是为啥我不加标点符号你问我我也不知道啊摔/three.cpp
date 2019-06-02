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
const int N=10010;
char s[N];
namespace subtask1{
	const int N=110;int cnt[N][N];
	inline int brute_force20(int n)
	{
		rep(i,0,n-1) rep(j,i+1,n-1) rep(k,j+1,n-1)
			if(s[i]=='1'||s[j]=='1'||s[k]=='1')
			{
				int a=j-i,b=k-j,c=n+i-k;
				if(a>b) swap(a,b);if(b>c) swap(b,c);
				if(a>b) swap(a,b);cnt[a][b]++;
			}
		lint ans=0;int v;
		rep(i,1,n) rep(j,i,(n-i)/2) v=cnt[i][j],ans+=v*(v-1ll)/2;
		return !printf("%lld\n",ans);
	}
}
inline int all0(int n) { rep(i,0,n-1) if(s[i]^'0') return 0;return 1; }
inline int all1(int n) { rep(i,0,n-1) if(s[i]^'1') return 0;return 1; }
namespace subtask3{
	inline int brute_force20(int n)
	{
		lint x=0,y=0,z=0,tot=n*(n-1ll)*(n-2)/6;if(n%3==0) z=1;
		rep(i,1,n/2) if(n-i*2>0&&n-2*i!=i) y++;x=(tot-(n/3)*z-n*y)/2/n;
		lint ans=x*2*n*(2*n-1)/2+y*n*(n-1)/2+z*(n/3)*(n/3-1)/2;
		return !printf("%lld\n",ans);
	}
}
int main()
{
	freopen("three.in","r",stdin);
	freopen("three.out","w",stdout);
	int n=inn();scanf("%s",s);
	if(n<=100) return subtask1::brute_force20(n);
	if(all0(n)) return !printf("0\n");
	if(all1(n)) return subtask3::brute_force20(n);
}
