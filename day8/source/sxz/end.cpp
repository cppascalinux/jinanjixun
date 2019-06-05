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
const int Maxn=1100;
const int inf=0x3f3f3f3f;
const int mod=1000000007;

inline int modd(int x) {
	return x>=mod?x-mod:x;
}

inline int readnum(int &x) {
	x=gc();
	while(!isdigit(x)) {
		if(x==EOF) return 0;
		x=gc();
	}
	x-='0';
	return 1;
}

int n,k,temp,sxz,f[Maxn][Maxn],g[Maxn][Maxn];

int main() {
	freopen("end.in","r",stdin);
	freopen("end.out","w",stdout);
	read(n,k);
	int ed=1;
	while(readnum(temp)) sxz=(sxz<<1)|temp,ed<<=1;
	f[0][sxz]=1;
	for(int i=1;i<=n;i++) {
		memset(g,0,sizeof(g));
		for(int j=0;j<ed;j++) {
			int zhy=0;
			for(int k=sxz;k>0;k--) {
				zhy=modd(f[j][k]+zhy);
				g[j^(k-1)][k-1]=zhy;
			}
		}
		memcpy(f,g,sizeof(g));
	}
	int zhy=0;
	for(int i=0;i<=sxz;i++) zhy=modd(zhy+f[0][i]);
	printf("%d\n",zhy);
	return 0;
}

