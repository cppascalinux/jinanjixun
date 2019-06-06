#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<ctime>
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
	return getchar();
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
const int Maxn=1100000;
const int inf=0x3f3f3f3f;
const int mod=100000007;

inline int modd(int x) {
	return x>=mod?x-mod:x;
}

int n,m,a[31][31],b[31][31],f[2][Maxn];
clock_t ttim;

int main() {
	freopen("scumwish.in","r",stdin);
	freopen("scumwish.out","w",stdout);
	read(n,m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++) read(a[i][j]);
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++) read(b[i][j]);
	f[0][0]=1; int ed=1<<m,now=0;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			now^=1;
			int *f=::f[now^1],*g=::f[now];
			for(int k=0;k<(ed>>1);k++) if(f[k<<1]||f[(k<<1)|1]) g[k]=modd(f[k<<1]+f[(k<<1)|1]); else g[k]=0;
			for(int k=ed>>1;k<ed;k++) g[k]=0;
//			for(int k=0;k<(ed>>1);k++) if(f[k<<1]) {
//				if((k&1)==0&&a[i][j]) {
//					g[k|1]=modd(g[k|1]+f[k<<1]);
//					if(b[i][j]) g[(k|1)|(1<<m-1)]=modd(g[(k|1)|(1<<m-1)]+f[k<<1]);
//				}
//				if(b[i][j]) {
//					g[k|(1<<m-1)]=modd(g[k|(1<<m-1)]+f[k<<1]);
//					if(a[i+1][j-1]&&(k&(1<<m-2))==0) g[k|(3<<m-2)]=modd(g[k|(3<<m-2)]+f[k<<1]);
//				}
//			}
			if(a[i][j]) {
				for(int k=0;k<(ed>>2);k++) if(f[k<<2]) g[(k<<1)|1]=modd(g[(k<<1)|1]+f[k<<2]);
				if(b[i][j]) for(int k=0;k<(ed>>2);k++) if(f[k<<2]) g[(k<<1)|1|(1<<m-1)]=modd(g[(k<<1)|1|(1<<m-1)]+f[k<<2]);
			}
			if(b[i][j]) {
				for(int k=0;k<ed>>1;k++) if(f[k<<1]) g[k|(1<<m-1)]=modd(g[k|(1<<m-1)]+f[k<<1]);
				if(a[i+1][j-1]) for(int k=0;k<ed>>2;k++) if(f[k<<1]) g[k|(3<<m-2)]=modd(g[k|(3<<m-2)]+f[k<<1]);
			}
		}
	}
	printf("%d\n",f[now][0]);
	return 0;
}

