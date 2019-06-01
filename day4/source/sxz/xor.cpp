#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<set>
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
const int Maxn=11000;
const int inf=0x3f3f3f3f;

int f[Maxn],dat[Maxn],m,q,n,opt,x;
set<int> se;

int find(int x) {
	if(f[x]!=x) f[x]=find(f[x]);
	return f[x];
}

void merge(int x,int y) {
	if(find(x)!=find(y)) {
		dat[f[y]]+=dat[f[x]];
		f[f[x]]=f[y];
	}
}

int calc() {
	for(int i=0;i<n;i++) f[i]=i,dat[i]=1;
	for(set<int>::iterator i=se.begin();i!=se.end();i++) {
		for(int j=0;j<n;j++) merge(j,j^(*i));
	}
	int ans=0;
	for(int i=0;i<n;i++) qmax(ans,dat[i]);
	return ans;
}

int main() {
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	read(m,q); n=1<<m;
	for(int i=1;i<=q;i++) {
		read(opt,x);
		if(opt==1) se.insert(x);
		else se.erase(x);
		printf("%d\n",calc());
	}
	return 0;
}

