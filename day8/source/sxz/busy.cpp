#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<map>
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
const int Maxn=110000;
const int Maxm=321;
const int inf=0x3f3f3f3f;

int n,m,a[Maxn],opt,x,y,ans,cnt,bl[Maxn],br[Maxn],in[Maxn],fr[Maxm][Maxm],las[Maxm][Maxm],le[Maxm];
short dis[Maxm][Maxm][Maxm];
short ma[Maxm][Maxn];

void init(int x) {
	int l=bl[x],r=br[x];
	for(int i=l;i<=r;i++) {
		if(!ma[x][a[i]]) ma[x][a[i]]=++le[x];
		a[i]=ma[x][a[i]];
	}
	for(int i=l;i<=r;i++) {
		if(!fr[x][a[i]]) fr[x][a[i]]=i;
		las[x][a[i]]=i;
	}
	memset(dis[x],0x3f,sizeof(dis[x]));
	for(int i=l;i<=r;i++)
		for(int j=i+1;j<=r;j++)
			qmin(dis[x][a[i]][a[j]],(short)(j-i));
	for(int i=1;i<=le[x];i++)
		for(int j=2;j<=le[x];j++)
			dis[x][i][j]=dis[x][j][i]=min(dis[x][i][j],dis[x][j][i]);
}

int main() {
	freopen("busy.in","r",stdin);
	freopen("busy.out","w",stdout);
	read(n,m);
	for(int i=1;i<=n;i++) read(a[i]);
	if(n<=1000&&m<=1000) {
		while(m--) {
			read(opt,x,y);
			x^=ans,y^=ans;
			if(opt==1) {for(int i=1;i<=n;i++) if(a[i]==x) a[i]=y;}
			else {
				ans=inf;
				int temp=0;
				for(int i=1;i<=n;i++) if(a[i]==x) {
					temp=i; break;
				}
				if(temp) {
					if(x==y) ans=0;
					for(int i=1;i<temp;i++) if(a[i]==y) qmin(ans,temp-i);
					for(int i=temp+1;i<=n;i++) if(a[i]==x) {
						for(int j=temp+1;j<i;j++) if(a[j]==y) qmin(ans,min(i-j,j-temp));
						temp=i;
					}
					for(int i=temp+1;i<=n;i++) if(a[i]==y) qmin(ans,i-temp);
				}
				if(ans==inf) {
					puts("Chtholly");
					ans=0;
				}
				else printf("%d\n",ans);
			}
		}
	}
	else {
		int blo=sqrt(n); memset(bl,0x3f,sizeof(bl));
		for(int i=1;i<=n;i++) in[i]=i/blo,qmin(bl[in[i]],i),qmax(br[in[i]],i);
		for(int i=0;i<=in[n];i++) init(i);
		while(m--) {
			read(opt,x,y);
			x^=ans,y^=ans;
			ans=inf;
			if(x==y) {
				for(int i=0;i<=in[n];i++) if(ma[i][x]) {
					ans=0;
					break;
				}
			}
			else {
				int lasx=-1,lasy=-1;
				for(int i=0;i<=in[n];i++) {
					int tempx=ma[i][x];
					if(tempx) {
						int tempy=ma[i][y];
						if(~lasy) qmin(ans,fr[i][tempx]-lasy);
						if(tempy) {
							if(~lasx) qmin(ans,fr[i][tempy]-lasx);
							lasy=las[i][tempy];
							qmin(ans,(int)dis[i][tempx][tempy]);
						}
						lasx=las[i][tempx];
					}
					else {
						int tempy=ma[i][y];
						if(tempy) {
							if(~lasx) qmin(ans,fr[i][tempy]-lasx);
							lasy=las[i][tempy];
						}
					}
				}
			}
			if(ans==inf) {
				puts("Chtholly");
				ans=0;
			}
			else printf("%d\n",ans);
		}
	}
	return 0;
}

