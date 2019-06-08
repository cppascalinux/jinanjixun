#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cassert>
#define rep(i,a,b) for (int i=a;i<(b);i++)
#define per(i,a,b) for (int i=(b)-1;i>=(a);i--)
using namespace std;
typedef long long ll;
string s;
int n;
pair<string,int> p[1010];
void ff(string s) {
	rep(i,0,n) p[i]=make_pair(s.substr(i),i);
	sort(p,p+n);
	rep(i,0,n) {
		printf("%d %s\n",p[i].second,p[i].first.c_str());
	}
	puts("");
}

int _[4]={3,0,2,1},__[4]={0,3,2,1};
ll f[1010][3];
#define bit(x) (1ll<<(x))
ll fuck(int k,ll n) {
	if (k<=1) return n;
	else if (k==2) {
		return _[n];
	} else {
		if (k%2==0) {
			if (n>=bit(k-1)) return fuck(k,n-bit(k-1))^1;
			else {
				if (n>=bit(k-2)) return fuck(k-1,n-bit(k-2))*2;
				else return fuck(k-1,n+bit(k-2))*2+1;
			}
		} else if (k%2==1) {
			if (n<f[k][0]) return fuck(k-1,n+bit(k-2))*2+1;
			else if (n==f[k][0]) return bit(k)-2;
			else if (n<=bit(k-2)) return fuck(k-1,n-1+bit(k-2))*2+1;
			else if (n<bit(k-1)) return fuck(k-1,n-bit(k-2))*2;
			else if (n==bit(k-1)) return bit(k)-1;
			else if (n<=3*bit(k-2)) return fuck(k-1,n-bit(k-2)-1)*2;
			else return fuck(k-1,n-3*bit(k-2))*2+1;
		}
	}
	assert(0);
	return 0;
}
int k,q;
ll x;
int main() {
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	f[2][0]=0; f[2][1]=1;
	rep(i,3,61) {
		f[i][0]=f[i-1][0]+f[i-1][1];
		f[i][1]=f[i-1][0]+f[i-1][1];
		if (i%2==0) f[i][1]++;
	}
	scanf("%d%d",&k,&q);
	rep(i,0,q) {
		scanf("%lld",&x);
		printf("%lld%c",fuck(k,x-1)," \n"[i==q-1]);
	}
}


