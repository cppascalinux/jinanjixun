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
const int Maxn=1100000;
const int inf=0x3f3f3f3f;

int dat[Maxn],ch[Maxn][2],dep[Maxn],t,a,b,n,m,cnt;

inline int newnode(int x) {
	int root=++cnt;
	dat[root]=x;
	return root;
}

int ins(int x,int y) {
	if(!x) return y;
	if(dat[x]>dat[y]) ch[x][0]=ins(ch[x][0],y);
	else ch[x][1]=ins(ch[x][1],y);
	if(ch[x][0]==y||ch[x][1]==y) dep[y]=dep[x]+1;
	return x;
}

int main() {
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
	read(t);
	while(t--) {
		read(a,b);
		read(m,n);
		a=(a+b)%m;
		int rt=0;
		while(n--) {
			rt=ins(rt,newnode(a));
			a=(a+b)%m;
		}
		printf("%d\n",dep[cnt]);
	}
	return 0;
}

