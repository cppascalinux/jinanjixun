#include<map>
#include<cmath>
#include<ctime>
#include<queue>
#include<cstdio>
#include<vector>
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
const int maxn=1e5+100;
const int P=1e9+7;
struct road{
	int head[maxn],nex[maxn<<1],v[maxn<<1],w[maxn<<1],num;
	inline void add(int x,int y,int z){
		v[++num]=y,w[num]=z,nex[num]=head[x],head[x]=num;
		v[++num]=x,w[num]=z,nex[num]=head[y],head[y]=num;
	}
	road(){num=1;}
}r1,r2;
int n;
ll d1[maxn],d2[maxn],Ans;
void dfs1(int x,int Fa,ll Dep){
	d1[x]=Dep;
	for(int i=r1.head[x];i;i=r1.nex[i])
		if(r1.v[i]!=Fa) dfs1(r1.v[i],x,Dep+r1.w[i]);
}
void dfs2(int x,int Fa,ll Dep){
	d2[x]=Dep;
	for(int i=r2.head[x];i;i=r2.nex[i])
		if(r2.v[i]!=Fa) dfs2(r2.v[i],x,Dep+r2.w[i]);
}
queue<int>q;
int qq[maxn];
inline void bfs1(int s){
	d1[s]=0,qq[s]=s,q.push(s);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=r1.head[x];i;i=r1.nex[i]){
			int y=r1.v[i];if(qq[y]==s) continue;
			qq[y]=s,q.push(y),d1[y]=d1[x]+r1.w[i];
		}
	}
}
inline void bfs2(int s){
	d2[s]=0,qq[s]=-s,q.push(s);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=r2.head[x];i;i=r2.nex[i]){
			int y=r2.v[i];if(qq[y]==-s) continue;
			qq[y]=-s,q.push(y),d2[y]=d2[x]+r2.w[i];
			if(y<s) Ans+=d1[y]*d2[y]%P;
		}
	}
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		r1.add(x,y,read());
	}
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		r2.add(x,y,read());
	}
	for(int i=1;i<=n;i++){
//		dfs1(i,i,0),dfs2(i,i,0);
		bfs1(i),bfs2(i),Ans%=P;
	}
	printf("%lld\n",Ans*2%P);
	return 0;
}













