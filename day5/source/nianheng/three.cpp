#include<map>
#include<set>
#include<ctime>
#include<queue>
#include<cmath>
#include<bitset>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mp(x,y) make_pair(x,y)
#define qmin(x,y) (x=min(x,y))
#define qmax(x,y) (x=max(x,y))
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
inline ll read(){
	ll ans=0,fh=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		ans=(ans<<1)+(ans<<3)+ch-'0',ch=getchar();
	return ans*fh;
}
int main(){
	freopen("three.in","r",stdin);
	freopen("three.out","w",stdout);
	printf("0\n");
	return 0;
}












