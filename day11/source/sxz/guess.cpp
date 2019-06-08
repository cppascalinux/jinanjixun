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

char s[Maxn];
int f[Maxn][Maxn];

int main() {
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
	scanf("%s",s);
	int n=strlen(s);
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<=n;i++) f[i][i]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=n-i;j++)
			for(int k=0;k<i;k++)
				qmin(f[j][j+i],max(f[j][j+k],f[j+k+1][j+i])+s[j+k]-'0');
	printf("%d\n",f[0][n]);
	return 0;
}

