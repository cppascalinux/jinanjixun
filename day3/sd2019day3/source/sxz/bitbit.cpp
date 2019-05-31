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
const int Maxn=310000;
const int Maxm=510;
const int inf=0x3f3f3f3f;

int to[2100000],nxt[2100000],first[Maxn],tot=2;
int a[Maxm][Maxm],dat[Maxm][Maxm],flag[Maxn];
int n,m,dep[Maxn],col[Maxn],num1,ans=inf,sxz,le[Maxn];
int bj[Maxm][Maxm],num,d[][2]={{0,1},{0,-1},{1,0},{-1,0}};
pir *vi[Maxn],b[Maxn];
char s[Maxm][Maxm];

int getanum() {
	char ch=gc();
	while(!isdigit(ch)) ch=gc();
	return ch-'0';
}

inline void add(int u,int v) {
	to[tot]=v;
	nxt[tot]=first[u];
	first[u]=tot++;
	to[tot]=u;
	nxt[tot]=first[v];
	first[v]=tot++;
}

void bfs(int s) {
	queue<int> q;
	q.push(s);
	dep[s]=1;
	int cnt=1,temp=col[s];
	flag[s]=s;
	while(!q.empty()&&temp!=num1) {
		int now=q.front(); q.pop();
		for(int i=first[now];i;i=nxt[i])
			if(flag[to[i]]!=s) {
				flag[to[i]]=s;
				dep[to[i]]=dep[now]+1;
				qmax(cnt,dep[to[i]]);
				if(dep[to[i]]>=ans) return ;
				temp+=col[to[i]];
				q.push(to[i]);
			}
	}
	sxz=s;
	ans=cnt;
}

int main() {
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	read(n,m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) a[i][j]=getanum();
	for(int i=1;i<=n;i++) bj[i][0]=bj[i][m+1]=1;
	for(int i=1;i<=m;i++) bj[0][i]=bj[n+1][i]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) if(!bj[i][j]) {
			queue<pir> q;
			q.push(mp(i,j));
			bj[i][j]=1;
			int sxz=a[i][j];
			num++;
			int cnt=0;
			while(!q.empty()) {
				pir now=q.front(); q.pop();
				b[++cnt]=now; dat[now.fr][now.sc]=num;
				for(int k=0;k<4;k++) {
					int nx=now.fr+d[k][0],ny=now.sc+d[k][1];
					if(!bj[nx][ny]&&a[nx][ny]==a[i][j]) {
						q.push(mp(nx,ny));
						bj[nx][ny]=1;
					}
				}
			}
			if(a[i][j]) num1++,col[num]=1;
			vi[num]=new pir[cnt+1];
			le[num]=cnt;
			for(int i=1;i<=cnt;i++) vi[num][i]=b[i];
		}
	for(int i=1;i<=num;i++) {
		flag[0]=i;
		for(int j=1;j<=le[i];j++) {
			for(int k=0;k<4;k++) {
				int nx=vi[i][j].fr+d[k][0],ny=vi[i][j].sc+d[k][1];
				if(flag[dat[nx][ny]]!=i) {
					flag[dat[nx][ny]]=i;
					add(i,dat[nx][ny]);
				}
			}
		}
	}
	if(num1==0) {
		return 0*puts("0");
	}
	memset(flag,0,sizeof(flag));
	for(int i=1;i<=num;i++)
		bfs(i);
	printf("%d\n",ans);
	memset(dep,0,sizeof(dep));
	queue<int> q;
	q.push(sxz);
	dep[sxz]=1; num1-=col[sxz];
	while(!q.empty()&&num1) {
		int now=q.front(); q.pop();
		for(int i=first[now];i;i=nxt[i])
			if(!dep[to[i]]) {
				dep[to[i]]=dep[now]+1;
				q.push(to[i]);
				num1-=col[to[i]];
			}
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) s[i][j]='0';
	memset(dat,0,sizeof(dat));
	for(int i=1;i<=num;i++) if(dep[i]) {
		b[++cnt]=mp(dep[i],i);
		for(int j=1;j<=le[i];j++) s[vi[i][j].fr][vi[i][j].sc]='1';
	}
	rsort(b+1,b+cnt+1);
	int temp=1;
	for(int i=1;i<=cnt;i=temp) {
		puts(col[b[i].sc]?"+":"-");
		for(int i=1;i<=n;i++) printf("%s\n",s[i]+1);
		while(b[i].fr==b[temp].fr) {
			for(int j=1;j<=le[b[temp].sc];j++) s[vi[b[temp].sc][j].fr][vi[b[temp].sc][j].sc]='0';
			temp++;
		}
	}
	for(int i=1;i<=num;i++) delete [] vi[i];
	return 0;
}

