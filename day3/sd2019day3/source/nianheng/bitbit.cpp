#include<map>
#include<cmath>
#include<ctime>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define qmin(x,y) (x=min(x,y))
#define qmax(x,y) (x=max(x,y))
#define mp(x,y) make_pair(x,y)
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
inline int read(){
	int ans=0,fh=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		ans=ans*10+ch-'0',ch=getchar();
	return ans*fh;
}
const int maxn=510,maxd=maxn*maxn,maxm=1e7+100;
clock_t St=clock();
int head[maxd],nex[maxm],v[maxm],num=1;
int n,m,a[maxn][maxn],c[maxn][maxn],Ans,ans,bb[maxd];
int tot,blk,isb[maxd],dep[maxd],qq[maxd],Nx;
int uu[4]={1,0,-1,0};
int vv[4]={0,-1,0,1};
char s[maxn],ok[maxn][maxn];
vector<pii>poi[maxd];
vector<int>Tmp[maxd];
map<int,bool>cz[maxd];
queue<int>q;
void dfs1(int x,int y,int bh){
	c[x][y]=bh,poi[bh].push_back(mp(x,y));
	for(int i=0;i<4;i++){
		int vx=x+uu[i],vy=y+vv[i];
		if(vx<1||vx>n||vy<1||vy>m) continue;
		if(a[vx][vy]) continue;
		if(!c[vx][vy]) dfs1(vx,vy,bh);
	}
}
void dfs2(int x,int y,int bh){
	c[x][y]=bh,poi[bh].push_back(mp(x,y));
	for(int i=0;i<4;i++){
		int vx=x+uu[i],vy=y+vv[i];
		if(vx<1||vx>n||vy<1||vy>m) continue;
		if(!a[vx][vy]) continue;
		if(!c[vx][vy]) dfs2(vx,vy,bh);
	}
}
inline void add(int x,int y){
	v[++num]=y,nex[num]=head[x],head[x]=num;
	v[++num]=x,nex[num]=head[y],head[y]=num;
}
inline void bfs(int s){
	memset(dep,0,sizeof(dep));
	while(!q.empty()) q.pop();
	dep[s]=1,q.push(s);
	int mx=0,tmp=blk;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=head[x];i;i=nex[i]){
			int y=v[i];if(dep[y]) continue;
			dep[y]=dep[x]+1,q.push(y);
			if(isb[y]){
				qmax(mx,dep[y]),tmp--;
				if(mx>Ans) return;
			}
			if(!tmp) break;
		}
		if(!tmp) break;
	}
	if(mx<Ans) Ans=mx,ans=s;
}
inline void bfs1(int s){
	memset(dep,0,sizeof(dep));
	memset(qq,0,sizeof(qq));
	while(!q.empty()) q.pop();
	dep[s]=1,q.push(s);
	int mx=0,tmp=blk;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=head[x];i;i=nex[i]){
			int y=v[i];if(dep[y]) continue;
			dep[y]=dep[x]+1,q.push(y);
			if(x==s) qq[y]=y;
			else qq[y]=qq[x];
			if(isb[y]){
				if(dep[y]>mx){
					mx=dep[y];
					Nx=qq[y];
				}
				if(mx>Ans) return;
				tmp--;
			}
			if(!tmp) break;
		}
		if(!tmp) break;
	}
	if(mx<Ans) Ans=mx,ans=s;
}
inline void work(int s){
	memset(dep,0,sizeof(dep));
	while(!q.empty()) q.pop();
	dep[s]=1,q.push(s),bb[1]=isb[1];
	Tmp[1].push_back(s);
	int tmp=blk;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=head[x];i;i=nex[i]){
			int y=v[i];if(dep[y]) continue;
			qq[y]=x,dep[y]=dep[x]+1,q.push(y);
			Tmp[dep[y]].push_back(y);
			if(isb[y]){
				int z=y;
				while(z&&!bb[z])
					bb[z]=1,z=qq[z];
				tmp--;
			}
			if(!tmp) break;
		}
		if(!tmp) break;
	}
	printf("%d\n",Ans);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			ok[i][j]='0';
	for(int i=1;i<=Ans;i++){
		for(int j=0;j<Tmp[i].size();j++){
			int x=Tmp[i][j];
			if(!bb[x]) continue;
			for(int k=0;k<poi[x].size();k++){
				pii y=poi[x][k];
				ok[y.first][y.second]='1';
			}
		}
		if((isb[s]&&i%2)||(!isb[s]&&!(i%2))) printf("+\n");
		else printf("-\n");
		for(int x=1;x<=n;x++){
			printf("%s",ok[x]+1);
			printf("\n");
		}
	}
}
int main(){
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)
			a[i][j]=s[j]-'0';
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!a[i][j]&&!c[i][j]) dfs1(i,j,++tot);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!c[i][j]){
				dfs2(i,j,++tot),blk++;
				isb[tot]=1;
			}
	if(blk==0){
		printf("0\n");
		return 0;
	}
	for(int x=1;x<=n;x++)
		for(int y=1;y<=m;y++)
			for(int i=0;i<4;i++){
				int vx=x+uu[i],vy=y+vv[i];
				if(vx<1||vx>n||vy<1||vy>m) continue;
				if(c[vx][vy]!=c[x][y]){
					int uc=c[vx][vy],vc=c[x][y];
					if(uc>vc) swap(uc,vc);
					if(cz[uc][vc]) continue;
					cz[uc][vc]=1,add(uc,vc);
				}
			}
	if(n<=30&&m<=30){
		Ans=0x7fffffff,ans=0;
		for(int i=1;i<=tot;i++) bfs(i);
		work(ans);
	}
	else{
		srand(time(0));
		Ans=0x7fffffff,ans=0,Nx=rand()%tot+1;
		int cnt=0;
		while((clock()-St)*1.0<CLOCKS_PER_SEC*7.0){
			bfs1(Nx);
			if(++cnt%100==0) Nx=rand()%tot+1;
		}
		work(ans);
		return 0;
	}
}













