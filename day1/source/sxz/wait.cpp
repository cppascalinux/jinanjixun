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
const int Maxn=110000;
const int inf=0x3f3f3f3f;

int n,m,l[Maxn],r[Maxn],w[Maxn],c[Maxn<<2],tot,cnt;
map<int,int> ma;

int main() {
	freopen("wait.in","r",stdin);
	freopen("wait.out","w",stdout);
	read(m,n);
	for(int i=1;i<=m;i++) read(l[i],r[i],w[i]),c[++tot]=l[i],c[++tot]=r[i],
		c[++tot]=l[i]-1,c[++tot]=l[i]+1,c[++tot]=r[i]-1,c[++tot]=r[i]+1;
	sort(c+1,c+tot+1);
	for(int i=1;i<=tot;i++) if(!ma[c[i]]) ma[c[i]]=++cnt;
	for(int i=1;i<=m;i++) l[i]=ma[l[i]],r[i]=ma[r[i]];
	if(m<=20) {
		int ed=1<<m,flag;
		for(int i=0;i<ed;i++) {
			flag=0;
			tot=0;
			for(int j=1;j<=cnt;j++) c[j]=0;
			for(int j=1,temp=1;j<=m;j++,temp<<=1)
				if((~w[j])&&w[j]!=((i&temp)>>j-1)) {
					flag=1;
					break;
				}
				else {
					if(i&temp) c[l[j]]++,c[r[j]+1]--;
					else c[l[j]]--,c[r[j]+1]++;
				}
			if(flag) continue;
			for(int j=1;j<=cnt;j++) c[j]+=c[j-1];
			for(int j=1;j<=cnt;j++) if(abs(c[j])>1) {
				flag=1;
				break;
			}
			if(flag) continue;
			for(int j=1,temp=1;j<=m;j++,temp<<=1)
				printf("%d ",(i&temp)>>j-1);
			putchar('\n');
			break;
		}
		if(flag) puts("-1");
	}
	return 0;
}

