#include<bits/stdc++.h>
#define to edge[i].v
#define mp make_pair
#define rint register int
#define fgx cerr<<"-------------"<<endl
#define N 555
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
void dbg(){cerr<<endl;}
template<typename A,typename... B>void dbg(A x,B... y){cerr<<x<<" ";dbg(y...);}
#define debug(...) cerr<<#__VA_ARGS__<<"=",dbg(__VA_ARGS__)
int mov[4][2]={{1,0},{-1,0},{0,1},{0,-1}},vis[N][N],a[N][N],n,m,fa[N*N],id[N][N],cov[N][N]; vector<int> V; char c[N][N];
inline int findfa(int x){return fa[x]==x?x:fa[x]=findfa(fa[x]);}
void dfs(int x,int y)
{	if(vis[x][y]) return; vis[x][y]=1;
	for(rint i=0;i<4;i++)
	{	int nx=x+mov[i][0],ny=y+mov[i][1];
		if(nx<1||nx>n||ny<1||ny>m) continue;
		if(c[nx][ny]==c[x][y]) fa[findfa(id[nx][ny])]=findfa(id[x][y]),dfs(nx,ny);
	}
}
void gao(int x,int y)
{	if(a[x][y]) return; a[x][y]=1;
	for(rint i=0;i<4;i++)
	{	int nx=x+mov[i][0],ny=y+mov[i][1];
		if(nx<1||nx>n||ny<1||ny>m) continue;
		if(c[nx][ny]==c[x][y]) gao(nx,ny);
	}
}
void find(int x,int y)
{	if(vis[x][y]) return; vis[x][y]=1;
	for(rint i=0;i<4;i++)
	{	int nx=x+mov[i][0],ny=y+mov[i][1];
		if(nx<1||nx>n||ny<1||ny>m) continue;
		if(c[nx][ny]==c[x][y]) find(nx,ny);
		else V.push_back(findfa(id[nx][ny]));
	}
	return;
}
int main()
{	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	int num=0,x=0,y=0,t=0; cin>>n>>m;
	for(rint i=1;i<=n;i++) scanf("%s",c[i]+1);
	for(rint i=1;i<=n;i++)
	for(rint j=1;j<=m;j++) id[i][j]=++t,fa[t]=t;
	for(rint i=1;i<=n;i++)
	for(rint j=1;j<=m;j++) if(!vis[i][j]) dfs(i,j);
	for(rint i=1;i<=n;i++)
	for(rint j=1;j<=m;j++) if(findfa(id[i][j])==id[i][j]&&c[i][j]=='1') num++,x=i,y=j;
	if(!num) return !printf("0");
	if(num==1)
	{	memset(a,0,sizeof(a)); gao(x,y); cout<<"1\n+\n";
		for(rint X=1;X<=n;X++,cout<<"\n")
		for(rint Y=1;Y<=m;Y++) cout<<a[X][Y];
		return 0;
	}
	memset(vis,0,sizeof(vis));
	for(rint i=1;i<=n;i++)
	for(rint j=1;j<=m;j++)
	if(findfa(id[i][j])==id[i][j]&&c[i][j]=='0')
	{	V.clear(); find(i,j); sort(V.begin(),V.end()); V.erase(unique(V.begin(),V.end()),V.end());
		if(V.size()==num)
		{	cout<<"2\n-\n"; memset(a,0,sizeof(a)); gao(i,j);
			for(rint X=1;X<=n;X++,cout<<"\n")
			for(rint Y=1;Y<=m;Y++) cout<<a[X][Y];
			for(x=1;x<=n;x++)
			for(y=1;y<=m;y++) if(findfa(id[x][y])==id[i][j]) c[x][y]='1';
			memset(a,0,sizeof(a)); gao(i,j); cout<<"+\n";
			for(rint X=1;X<=n;X++,cout<<"\n")
			for(rint Y=1;Y<=m;Y++) cout<<a[X][Y];
			return 0;
		}
	}
	if(n==1)
	{	vector<pii> v;
		for(rint i=1,j;i<=m;i=j)
		{	if(c[1][i]=='0'){j=i+1;continue;}
			for(j=i+1;j<=m&&c[1][j]=='1';j++);
			v.push_back(mp(i,j-1));
		}
		cout<<(int)v.size()<<"\n";
		for(auto _:v)
		{	for(rint i=1;i<=m;i++) a[1][i]=0;
			for(rint i=_.first;i<=_.second;i++) a[1][i]=1;
			cout<<"+\n";
			for(rint X=1;X<=n;X++,cout<<"\n")
			for(rint Y=1;Y<=m;Y++) cout<<a[X][Y];
		}
		return 0;
	}
	if(m==1)
	{	vector<pii> v;
		for(rint i=1,j;i<=n;i=j)
		{	if(c[i][1]=='0'){j=i+1;continue;}
			for(j=i+1;j<=n&&c[j][1]=='1';j++);
			v.push_back(mp(i,j-1));
		}
		cout<<(int)v.size()<<"\n";
		for(auto _:v)
		{	for(rint i=1;i<=n;i++) a[i][1]=0;
			for(rint i=_.first;i<=_.second;i++) a[i][1]=1;
			cout<<"+\n";
			for(rint X=1;X<=n;X++,cout<<"\n")
			for(rint Y=1;Y<=m;Y++) cout<<a[X][Y];
		}
		return 0;
	}
	if(m==2)
	{	swap(n,m);
		cout<<"3\n+\n"; memset(a,0,sizeof(a));
		for(rint i=1;i<=n;i++) a[i][1]=1,cov[i][1]++;
		for(rint i=1;i<=n;i++)
		if(i&1) for(rint j=2;j<m;j++) a[i][j]=1,cov[i][j]++;
		else for(rint j=2;j<m;j++) if(c[j][i]=='1') a[i][j]=1,cov[i][j]++;
		for(rint Y=1;Y<=m;Y++,cout<<"\n")
		for(rint X=1;X<=n;X++) cout<<a[X][Y];
		cout<<"+\n"; memset(a,0,sizeof(a));
		for(rint i=1;i<=n;i++) a[i][m]=1,cov[i][m]++;
		for(rint i=1;i<=n;i++)
		if(!(i&1)) for(rint j=2;j<m;j++) a[i][j]=1,cov[i][j]++;
		else for(rint j=2;j<m;j++) if(c[j][i]=='1') a[i][j]=1,cov[i][j]++;
		for(rint Y=1;Y<=m;Y++,cout<<"\n")
		for(rint X=1;X<=n;X++) cout<<a[X][Y];
		cout<<"-\n"; memset(a,0,sizeof(a));
		for(rint i=1;i<=n;i++)
		for(rint j=1;j<=m;j++) a[i][j]=cov[i][j]-(c[j][i]-'0');
		for(rint Y=1;Y<=m;Y++,cout<<"\n")
		for(rint X=1;X<=n;X++) cout<<a[X][Y];
		return 0;
	}
	cout<<"3\n+\n"; memset(a,0,sizeof(a));
	for(rint i=1;i<=n;i++) a[i][1]=1,cov[i][1]++;
	for(rint i=1;i<=n;i++)
	if(i&1) for(rint j=2;j<m;j++) a[i][j]=1,cov[i][j]++;
	else for(rint j=2;j<m;j++) if(c[i][j]=='1') a[i][j]=1,cov[i][j]++;
	for(rint X=1;X<=n;X++,cout<<"\n")
	for(rint Y=1;Y<=m;Y++) cout<<a[X][Y];
	cout<<"+\n"; memset(a,0,sizeof(a));
	for(rint i=1;i<=n;i++) a[i][m]=1,cov[i][m]++;
	for(rint i=1;i<=n;i++)
	if(!(i&1)) for(rint j=2;j<m;j++) a[i][j]=1,cov[i][j]++;
	else for(rint j=2;j<m;j++) if(c[i][j]=='1') a[i][j]=1,cov[i][j]++;
	for(rint X=1;X<=n;X++,cout<<"\n")
	for(rint Y=1;Y<=m;Y++) cout<<a[X][Y];
	cout<<"-\n"; memset(a,0,sizeof(a));
	for(rint i=1;i<=n;i++)
	for(rint j=1;j<=m;j++) a[i][j]=cov[i][j]-(c[i][j]-'0');
	for(rint X=1;X<=n;X++,cout<<"\n")
	for(rint Y=1;Y<=m;Y++) cout<<a[X][Y];
	return 0;
}

