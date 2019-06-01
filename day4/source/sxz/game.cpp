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
//const int Maxn=;
const int inf=0x3f3f3f3f;

signed char f[1100000][2][21];
int t,n,m,a;

bool dp(int zt,int fr,int len) {
	signed char &sxz=f[zt][fr][len];
	if(~sxz) return sxz;
	sxz=0;
	for(int i=1,temp=2;i<len;i++,temp<<=1) {
		int x=zt&(temp-1),y=(zt&(~(temp-1)))>>1;
		if(!dp((x|(~(temp-1)))&(y|((temp-1)>>1)),fr^1,len-1)||!dp(x^y,fr^1,len-1)) return sxz=1;
	}
	return sxz;
}

int main() {
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	read(t); memset(f,-1,sizeof(f));
	f[1][0][1]=f[0][1][1]=0;
	f[0][0][1]=f[1][1][1]=1;
	while(t--) {
		read(n,m);
		int temp=0;
		for(int i=1;i<=n;i++)
			read(a),a&=1,temp<<=1,temp|=a;
		if(!temp) {
			puts("A");
			continue;
		}
		if(n<=20)
		puts((dp(temp,m,n)^m)?"A":"B");
		else puts("A");
	}
	return 0;
}

