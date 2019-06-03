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
const int Maxn=531;
const int inf=0x3f3f3f3f;
const int mod=1000000007;

inline int modd(int x) {
	return x<0?x+mod:x>=mod?x-mod:x;
}

int n,m,b[Maxn],f[Maxn][Maxn],g[Maxn][Maxn],s1[Maxn],s2[Maxn],ss1[Maxn],ss2[Maxn],top1,top2,ttop1,ttop2,c[Maxn],d[Maxn],r[Maxn];

int main() {
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	read(n,m);
	for(int i=1;i<=n;i++) read(b[i]);
	if(n==1) return 0*printf("%d\n",(1<<m)%mod);
	f[0][0]=1;
	for(int i=m;i;i--) {
		memset(g,0,sizeof(g));
		int x=1<<(i-1);
		int ed=1<<n;
		for(int j=1;j<=n;j++) c[j]=b[j]&x;
		for(int j=0;j<ed;j++) {
			int sxz1=0,sxz2=0,zhy1=0,zhy2=0;
			top1=top2=ttop1=ttop2=0;
			for(int k=1,temp=1;k<=n;k++,temp<<=1)
				if(j&temp) {
					d[k]=c[k];
					r[k]=x;
				}
				else {
					d[k]=0;
					r[k]=c[k];
				}
			for(int k=1;k<n;k++) {
				if(d[k]<d[k+1]) sxz1|=1<<(k-1);
				if(d[k]<=d[k+1]) s1[++top1]=k;
				else zhy1|=1<<(k-1);
			}
			for(int k=1;k<n;k++) {
				if(r[k]>r[k+1]) sxz2|=1<<(k-1);
				if(r[k]>=r[k+1]) s2[++top2]=k;
				else zhy2|=1<<(k-1);
			}
			int ed1=1<<top1;
			for(int k=0;k<ed1;k++) {
				int x=zhy1;
				for(int l=1,temp=1;l<=top1;l++,temp<<=1)
					if(k&temp) x|=1<<(s1[l]-1);
				ss1[++ttop1]=x;
			}
			ed1=1<<top2;
			for(int k=0;k<ed1;k++) {
				int x=zhy2;
				for(int l=1,temp=1;l<=top2;l++,temp<<=1)
					if(k&temp) x|=1<<(s2[l]-1);
				ss2[++ttop2]=x;
			}
			
			for(int k=1;k<=ttop1;k++) {
				int *h=g[ss1[k]|sxz1],*hh=f[ss1[k]];
				for(int l=1;l<=ttop2;l++)
					if(hh[ss2[l]]) h[ss2[l]|sxz2]=modd(h[ss2[l]|sxz2]+hh[ss2[l]]);
			}
		}
		memcpy(f,g,sizeof(f));
	}
	int ed=1<<(n-1),ans=0;
	for(int i=0;i<ed;i++)
		for(int j=0;j<ed;j++) ans=modd(ans+f[i][j]);
	printf("%d\n",ans);
	return 0;
}

