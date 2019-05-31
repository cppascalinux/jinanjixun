#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define qmin(x,y) (x=min(x,y))
#define qmax(x,y) (x=max(x,y))
#define pir pair<int,int>
#define fr first
#define sc second
#define mp(x,y) make_pair(x,y)
#define vic vector<int>
#define vit vic::iterator
#define rsort(x,y) sort(x,y),reverse(x,y)
using namespace std;

inline char gc() {
	return  getchar();
}

template<typename T1>
int read(T1 &a) {
	a=0;
	char ch=gc();
	T1 f=1;
	while(!isdigit(ch)) {
		if(ch==EOF) return 0;
		if(ch=='-') f=-1;
		ch=gc();
	}
	while(isdigit(ch)) {
		a=a*10+ch-'0';
		ch=gc();
	}
	a=a*f;
	return 1;
}

template<typename T1,typename T2>
int read(T1 &a,T2 &b) {
	return read(a)+read(b);
}

template<typename T1,typename T2,typename T3>
int read(T1 &a,T2 &b,T3 &c) {
	return read(a,b)+read(c);
}

typedef long long ll;
const int Maxn=110;
const int inf=0x3f3f3f3f;

int n,k,c[Maxn],d[Maxn],b[Maxn],ans;

int check() {
	int ans=0;
	for(int i=1;i<n;i++) d[i]=c[i]>c[i+1];
	for(int i=1;i<n;i++) if(d[i]!=d[i+1]) ans++;
	return ans==k-1;
}

void dfs(int now) {
	if(now>n) {
		ans+=check();
		return ;
	}
	for(int i=1;i<=n;i++)
		if(!b[i]) {
			b[i]=1;
			c[now]=i;
			dfs(now+1);
			b[i]=0;
		}
}

int main() {
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	read(n,k);
	dfs(1);
	printf("%d\n",ans);
	return 0;
}

