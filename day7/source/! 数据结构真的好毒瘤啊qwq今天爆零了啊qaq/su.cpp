#include<bits/stdc++.h>
using namespace std;
#define li long long
char buf[100010],*buff = buf + 100000;
#define gc (((buff == buf + 100000) ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
//#define gc getchar()
char bfu[50000010],*bfuu = bfu;
#define pc(x) (*(bfuu++) = (x))
//#define pc putchar
inline li read(){
	li x = 0,y = 0,c = gc;
	while(!isdigit(c)) y = c,c = gc;
	while(isdigit(c)) x = x * 10 + c - '0',c = gc;
	return y == '-' ? -x : x;
}
inline void print(li x){
	if(x < 0) pc('-'),x = -x;
	if(x >= 10) print(x / 10);
	pc(x % 10 + '0');
}
inline void file(){
	freopen("su.in","r",stdin);
	freopen("su.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m,fa[100010],fsts[100010],nxt[100010],dpt[100010],col[100010],nw,mx,mn,as;
struct edge{
	int to,nxt;
}e[200010];
int cnt,fir[100010];
inline void ins(int u,int v){
	e[++cnt].to = v;e[cnt].nxt = fir[u];fir[u] = cnt;
	e[++cnt].to = u;e[cnt].nxt = fir[v];fir[v] = cnt;
}
inline void dfs(int q){
	for(int i = fsts[q];i;i = nxt[i]){
		dpt[i] = dpt[q] + 1;
		dfs(i);
	}
}
inline void dfs2(int q,int x){
	col[q] = x;
	for(int i = fsts[q];i;i = nxt[i]) if(col[i] == nw) dfs2(i,x);
}
inline void dfs3(int q){
	++as;mx = max(mx,dpt[q]);mn = min(mn,dpt[q]); 
	for(int i = fsts[q];i;i = nxt[i]) if(col[i] == nw) dfs3(i);
}
int main(){
	srand(time(0));rd();
	file();
	int i,j,op,x,y;
	n = read();
	for(i = 1;i <= n;++i) fa[i] = read(),nxt[i] = fsts[fa[i]],fsts[fa[i]] = i,ins(i,fa[i]);
	for(i = 1;i <= n;++i) col[i] = read();
	dfs(1);
	m = read();
	for(i = 1;i <= m;++i){
		op = read();
		if(op == 1){
			x = read();y = read();col[x] = y;
		}
		else if(op == 2){
			x = read();y = read();nw = col[x];
			while(col[x] == col[fa[x]]) x = fa[x];
			dfs2(x,y);
		}
		else{
			x = read();nw = col[x];as = mx = 0;mn = n;
			while(col[x] == col[fa[x]]) x = fa[x];	
			dfs3(x);
			print(col[x]);pc(' ');print(as);pc(' ');print(mx - mn + 1);pc('\n');
		}
	}
	fwrite(bfu,1,bfuu - bfu,stdout);
	return 0;
}

