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
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
namespace INPUT_SPACE{
	const int BS=(1<<24)+5;char S[BS],*h,*t;inline int gc() { if(h==t) t=(h=S)+fread(S,1,BS,stdin);return h==t?EOF:(*h++); }
	inline int inn() { int x,ch;while((ch=gc())<'0'||ch>'9');x=ch^'0';while((ch=gc())>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^'0');return x; }
}using INPUT_SPACE::inn;
const int N=100010;
int a[N],ss[N],ps[N];
inline int jswzy0(int n) { rep(i,1,n) if(i%2==1&&!a[i]) return 1;return 0; }
inline int kyczzlgsbc1(int x,int y) { return x==1||y==1; }
inline int czygwzsdhjswzdhsncy2(int n)
{
	rep(i,1,n-1)
		if(i&1)
		{
			if((i>2?ps[i-2]:0)+(i+3<=n?ss[i+3]:0)+kyczzlgsbc1(a[i],a[i+1])==n/2) return 1;
		}
		else{
			if((i>1?ps[i-1]:0)+(i+2<=n?ss[i+2]:0)==n/2) return 1;
		}
	return 0;
}
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	for(int T=inn();T;T--)
	{
		int n=inn(),m=inn();
		rep(i,1,n) a[i]=inn()&1;
		if(n==1) printf(a[1]?"B\n":"A\n");
		else if(m==0)
		{
			if(n%2==0) printf("A\n");
			else if(jswzy0(n)) printf("A\n");
			else printf("B\n");
		}
		else{
			if(n%2==1) printf("A\n");
			else{
				rep(i,1,n) ps[i]=a[i]+(i>2?ps[i-2]:0);
				for(int i=n;i;i--) ss[i]=a[i]+(i<=n-2?ss[i+2]:0);
				if(czygwzsdhjswzdhsncy2(n)) printf("B\n");
				else printf("A\n");
			}
		}
	}
	return 0;
}
