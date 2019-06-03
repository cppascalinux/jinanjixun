#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<queue>
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
const int Maxn=11;
const int inf=0x3f3f3f3f;

char getach() {
	char ch=gc();
	while(!isalpha(ch)) ch=gc();
	return ch;
}

int vis[Maxn][Maxn],mp[Maxn][Maxn],n,m,k,tot,ans,d[][2]={{0,1},{0,-1},{1,0},{-1,0}},cnt;
char s[Maxn][Maxn];

bool check() {
	queue<pir> q;
	int cnt=0,temp=0;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) vis[i][0]=vis[i][m+1]=1;
	for(int i=1;i<=m;i++) vis[0][i]=vis[n+1][i]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!vis[i][j]) {
				cnt++;
				q.push(mp(i,j));
				vis[i][j]=1;
				while(!q.empty()) {
					pir now=q.front(); q.pop();
					for(int k=0;k<4;k++) {
						pir nx=mp(now.fr+d[k][0],now.sc+d[k][1]);
						if(!vis[nx.fr][nx.sc]&&mp[nx.fr][nx.sc]==mp[i][j]) {
							q.push(nx);
							vis[nx.fr][nx.sc]=1;
						}
					}
				}
			}
	return cnt==2;
}

void dfs(int x,int y) {
	if(n*m-tot+k<tot) return ;
	if(x!=1&&y!=1) {
		if(mp[x][y]&&mp[x-1][y]&&mp[x][y-1]&&mp[x-1][y-1]) return ;
		if(!mp[x][y]&&!mp[x-1][y]&&!mp[x][y-1]&&!mp[x-1][y-1]) return ;
		int z=mp[x-1][y-1];
		if(z==mp[x][y]&&z!=mp[x-1][y]&&z!=mp[x][y-1]) return ;
	}
	if(x==n&&y==m) {
		if(tot+k<n*m-tot) return ;
		if(check()) {
//			for(int i=1;i<=n;i++) {
//				for(int j=1;j<=m;j++)
//					printf("%d ",mp[i][j]);
//				putchar('\n');
//			}
//			puts("");
			ans++;
		}
		return ;
	}
	if(y==m) x++,y=1;
	else y++;
	if(s[x][y]!='C') dfs(x,y);
	else {
		mp[x][y]=0;
		dfs(x,y);
		mp[x][y]=1;tot++;
		dfs(x,y);tot--;
	}
}

int main() {
	freopen("cut.in","r",stdin);
	freopen("cut.out","w",stdout);
	read(n,m,k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) {
			s[i][j]=getach();
			tot+=mp[i][j]=s[i][j]=='A';
		}
	if(s[1][1]!='C') dfs(1,1);
	else {
		dfs(1,1);
		mp[1][1]=1;tot++;
		dfs(1,1);
	}
	printf("%d\n",ans);
	return 0;
}

