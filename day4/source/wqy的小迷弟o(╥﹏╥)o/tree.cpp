#include<cstdio>
#include<cstring>
#include<iostream>
#include<cctype>
#include<algorithm>
#include<queue>
#include<set>
#include<vector>
#include<cmath>
#define LL long long
#define pii pair<int,int>
#define mk make_pair
using namespace std;
const int N = 1e5 + 3;
int fa[N],top[N];
int n,m,q;
int size[N]; 
bool book[N];
int xi[N],yi[N],lc[N];
int tot = 0,cnt;
int sum[N];
int idx[N];
int s[N],son[N],deep[N];
int sum2[N];
vector <int> G[N];
inline int read(){
	int v = 0,c = 1;char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') c = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		v = v * 10 + ch - 48;
		ch = getchar();	
	}
	return v * c;
}
inline void dfs1(int x,int f,int dep){
	fa[x] = f;
	deep[x] = dep;
	int maxsize = - 1;
	size[x] = 1;
	for(int i = 0;i < G[x].size();++i){
		int y = G[x][i];
		if(y == f)	continue;
		dfs1(y,x,dep + 1);
		size[x] += size[y];
		if(size[y] > maxsize) maxsize = size[y],son[x] = y;
	}
}
inline void dfs2(int x,int topf){
	idx[++cnt] = x;
	top[x] = topf;
	if(!son[x]) return ;
	dfs2(son[x],topf);
	for(int i = 0;i < G[x].size();++i){
		int y = G[x][i];
		if(y == son[x] || y == fa[x]) continue;
		dfs2(y,y);
	}
}
inline int lca(int x,int y){
	while(top[x] != top[y]){
		if(deep[top[x]] < deep[top[y]]) swap(x,y);
		x = fa[top[x]];	
	}
	if(deep[x] > deep[y]) swap(x,y);
	return x;
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n = read(),m = read(),q = read();
	for(int i = 1;i < n;++i){
		int x = read(),y = read();
		G[x].push_back(y);
		G[y].push_back(x);	
	}
	dfs1(1,0,1);
	dfs2(1,1);
//	m = read();
	for(int i = 1;i <= m;++i) {xi[i] = read(),yi[i] = read();lc[i] = lca(xi[i],yi[i]);}
//	q = read();
	while(q--){
		for(int i = 1;i <= n;++i) sum[i] = sum2[i] = 0;
		int l = read(),r = read();
		for(int i = l;i <= r;++i){
			sum[xi[i]]++;
			sum[yi[i]]++;
			sum[lc[i]]-=2;
			sum2[xi[i]]++;
			sum2[yi[i]]++;
			sum2[lc[i]]--;
			sum2[fa[lc[i]]]--;
		}
		for(int i = n;i >= 1;--i) sum[fa[idx[i]]] += sum[idx[i]],sum2[fa[idx[i]]] += sum2[idx[i]];
		int ans1 = 0,ans2 = 0;
		for(int i = 1;i <= n;++i){
			if(sum[i]) ans1++;
			if(sum2[i]) ans2++;
		}
		printf("%d\n",ans2-ans1);
	}
	return 0;	
}
