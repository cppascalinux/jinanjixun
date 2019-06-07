#include<iostream>
#include<cstdio>
using namespace std;
const int N=22019,mod=1e9+7;
int n,dep[N][3],dt[N][3],anc[N][20][3],v[3][N],tot[3];
struct Edge{int to,next,data;}e[3][N<<1];
void add(int x,int y,int z,int th){
	e[th][++tot[th]].to=y; e[th][tot[th]].data=z;
	e[th][tot[th]].next=v[th][x]; v[th][x]=tot[th];
}
void dfs(int x,int fa,int th){
	for(int i=1;i<=15;i++)
		anc[x][i][th]=anc[anc[x][i-1][th]][i-1][th];
	for(int p=v[th][x];p;p=e[th][p].next){
		int kp=e[th][p].to;
		if(kp!=fa){
			dt[kp][th]=dt[x][th]+e[th][p].data;
			dep[kp][th]=dep[x][th]+1;
			anc[kp][0][th]=x;
			dfs(kp,x,th);
		}
	}
}
int LCA(int x,int y,int th){
	if(dep[x][th]<dep[y][th])swap(x,y);
	int cha=dep[x][th]-dep[y][th];
	for(int i=0;i<=15;i++)
		if(cha & (1<<i))x=anc[x][i][th];
	if(x==y)return x;
	for(int i=15;i>=0;i--)
		if(anc[x][i][th] != anc[y][i][th])
			x=anc[x][i][th],y=anc[y][i][th];
	return anc[x][0][th];
}
long long dis(int x,int y,int th){
	return 1ll*(dt[x][th]+dt[y][th]-2*dt[LCA(x,y,th)][th])%mod;
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v,w;cin>>u>>v>>w;
		add(u,v,w,1); add(v,u,w,1);
	}
	for(int i=1;i<n;i++){
		int u,v,w;cin>>u>>v>>w;
		add(u,v,w,2); add(v,u,w,2);
	}
	dfs(1,0,1); dfs(1,0,2);
/*	cout<<LCA(2,3,1)<<endl;
	for(int i=1;i<=n;i++,cout<<endl)
		for(int j=0;j<=5;j++)
			cout<<anc[i][j][1]<<" ";
	for(int a,b,i=1;i<=1000;i++){
		cin>>a>>b;
		cout<<dis(a,b,1)<<" "<<dis(a,b,2)<<endl;
	}*/
	long long ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			ans=(ans+1ll*dis(i,j,1)*dis(i,j,2))%mod;
	cout<<ans<<endl;
	fclose(stdin); fclose(stdout);
	return 0;
}
/*
3
1 2 3
2 3 2
1 3 4
1 2 5
*/
