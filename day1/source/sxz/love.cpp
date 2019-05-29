#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<queue>
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
const int Maxn=110000;
const int inf=0x3f3f3f3f;

ll n,m,b[Maxn],a[Maxn],tot,u,v,wi;
ll ans;

int main() {
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
	read(n,m);
	for(int i=1;i<n;i++) {
		read(u,v,wi);
		b[v]=b[u]=wi;
	}
	rsort(b+2,b+n+1);
	for(int i=1;i<=m;i++) read(a[i]);
	for(int i=2;i<=n;i+=2) b[++tot]=b[i]+b[i+1];
	for(int i=1;i<=tot;i++) ans+=b[i]*2ll;
	priority_queue<int> q;
	int temp=0;
	ll sxz=ans;
	printf("%lld ",ans);
	b[tot+1]=0;
	for(int i=1;i<=m;i++) {
		q.push(a[i]),temp++; sxz+=a[i],sxz-=b[temp];  
		while(temp&&q.top()>b[temp]) sxz-=q.top(),sxz+=b[temp],q.pop(),temp--;
		qmin(ans,sxz);
		printf("%lld ",ans);
	}
	return 0;
}

