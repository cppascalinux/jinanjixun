#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<map>
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
const int Maxn=21;
const int inf=0x3f3f3f3f;

int n,k,tot;
pir a[Maxn],b[Maxn],p[Maxn];
map<ll,int> ma;

ll hash() {
	ll ans=0;
	for(int i=1;i<=n;i++) ans=ans*n+b[i].fr;
	return ans;
}

bool dfs(int now) {
	for(int i=1;i<=n;i++) if(a[i].fr==k) {
		for(int j=1;j<=n;j++) if(a[j].sc==1) swap(a[j].sc,a[i].sc);
		return true;
	}
	pir c[Maxn];
	for(int i=1;i<=n;i++) if(a[i].fr)
		for(int j=i+1;j<=n;j++) {
			for(int k=1;k<=n;k++) b[k]=a[k];
			b[j].fr-=b[i].fr,b[i].fr<<=1;
			sort(b+1,b+n+1);
			if(!ma[hash()]) {
				ma[hash()]=1;
				for(int k=1;k<=n;k++) c[k]=a[k],a[k]=b[k];
				if(dfs(now+1)) {
					p[++tot]=mp(c[j].sc,c[i].sc);
					return true;
				}
				for(int k=1;k<=n;k++) a[k]=c[k];
			}
		}
	return false;
}

void work(int l,int r) {
	if(l==r) return ;
	int mid=l+r>>1;
	work(l,mid);
	work(mid+1,r);
	p[++tot]=mp(mid+1,l);
}

int main() {
	freopen("chemistry.in","r",stdin);
	freopen("chemistry.out","w",stdout);
	read(n,k);
	for(int i=1;i<=n;i++) a[i]=mp(1,i);
	if(n<=10) {
		if(!dfs(0)) puts("-1");
		else {
			printf("%d\n",tot);
		while(tot) printf("%d %d\n",p[tot].fr,p[tot].sc),tot--;
		}
	}
	else {
		int temp=1;
		while(temp<=k) temp<<=1;
		work(1,temp);
		k=temp-k;
		int las=1,zhy=1;
		for(int i=1;i<=k;i<<=1)
			if(i&k) {
				while(las<i) {
					work(temp+zhy+1,temp+zhy+las);
					p[++tot]=mp(temp+las+1,temp+1);
					zhy+=las;
					las<<=1;
				}
				p[++tot]=mp(1,temp+1);
				las<<=1;
			}
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++) printf("%d %d\n",p[i].fr,p[i].sc);
	}
	return 0;
}

