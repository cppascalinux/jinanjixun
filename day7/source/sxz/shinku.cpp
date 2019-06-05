#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<cmath>
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

struct querys {
	int fr,sc,id;
}p[Maxn];

int n,m,a[Maxn],bj[Maxn],res[Maxn],in[Maxn];
char ans[Maxn][12];

int cmp(querys a,querys b) {
	if(in[a.sc]==in[b.sc]) return in[a.sc]&1?a.fr>b.fr:a.fr<b.fr;
	else return in[a.sc]<in[b.sc];
}

inline void add(int x) {
	bj[x]++;
	if(bj[x]!=1) return ;
	int l=1,r=1;
	while(r<=11&&bj[x+r]) r++;
	while(l<=11&&bj[x-l]) l++;
	r--,l--;
	if(l<=10&&l) res[l]--;
	if(r<=10&&r) res[r]--;
	if(l+r+1<=10) res[l+r+1]++; 
}

inline void del(int x) {
	bj[x]--;
	if(bj[x]) return ;
	int l=1,r=1;
	while(r<=11&&bj[x+r]) r++;
	while(l<=11&&bj[x-l]) l++;
	r--,l--;
	if(l<=10&&l) res[l]++;
	if(r<=10&&r) res[r]++;
	if(l+r+1<=10) res[l+r+1]--;
}

int main() {
	freopen("shinku.in","r",stdin);
	freopen("shinku.out","w",stdout);
	read(n,m);
	int sqr=sqrt(n)*1.5;
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1;i<=n;i++) in[i]=i/sqr;
	for(int i=1;i<=m;i++) read(p[i].fr,p[i].sc),p[i].id=i;
	sort(p+1,p+m+1,cmp);
	int l=1,r=1; add(a[1]);
	for(int i=1;i<=m;i++) {
		while(r<p[i].sc) add(a[++r]);
		while(l>p[i].fr) add(a[--l]);
		while(r>p[i].sc) del(a[r--]);
		while(l<p[i].fr) del(a[l++]);
		for(int j=1;j<=10;j++) ans[p[i].id][j]='0'+res[j]%10;
	}
	for(int i=1;i<=m;i++) puts(ans[i]+1);
	return 0;
}

