#include<bits/stdc++.h>
using namespace std;
#define li long long
#define gc getchar()
#define pc putchar
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
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m,q,as[200010];
struct edge{
	int to,nxt;
}e[200010];
int cnt = 1,fir[200010];
inline void ins(int u,int v){
	e[++cnt].to = v;e[cnt].nxt = fir[u];fir[u] = cnt;
	e[++cnt].to = u;e[cnt].nxt = fir[v];fir[v] = cnt;
}
struct lian{
	int x,y,l;
}a[200010];
struct qy{
	int l,r,id;
}b[200010];
inline bool operator < (qy q,qy w){
	return q.r < w.r;
}
int fa[200010],ff[200010],dpt[200010],st[18][200010];
int f[200010],l[200010],r[200010],mn[200010],c[200010],sz1[200010],sz2[200010];
inline void dfs(int q){
	//cerr<<q<<"*"<<fa[q]<<endl;
	for(int i = fir[q];i;i = e[i].nxt) if(e[i].to != fa[q]){
		fa[e[i].to] = q;
		dpt[e[i].to] = dpt[q] + 1;
		f[e[i].to] = ff[e[i].to] = (i >> 1) + n;
		f[(i >> 1) + n] = ff[(i >> 1) + n] = q;
		dfs(e[i].to);
	}
}
inline void buildst(){
	register int i,j;
	for(i = 1;i <= n;++i) st[0][i] = fa[i];
	for(i = 1;i < 18;++i) for(j = 1;j <= n;++j) st[i][j] = st[i - 1][st[i - 1][j]];
}
inline int lca(int u,int v){
	if(dpt[u] < dpt[v]) swap(u,v);
	int j = dpt[u] - dpt[v],i = 0;
	while(j){
		if(j & 1) u = st[i][u];
		j >>= 1;++i;
	}
	if(u == v) return u;
	for(i = 17;i >= 0;--i) if(st[i][u] != st[i][v]) u = st[i][u],v = st[i][v];
	return st[0][u];
}
int t[200010],t2[200010];
inline void xg(int q,int x){
	//cerr<<"*"<<q<<" "<<x<<endl;
	if(!q) return;
	for(int i = q;i <= n + n;i += i & -i) t[i] += x;
}
inline int cx(int q){
	if(!q) return 0;
	int as = 0;
	for(int i = q;i;i -= i & -i) as += t[i];
	return as;
}
inline void xg2(int q,int x){
	//cerr<<"%"<<q<<" "<<x<<endl;
	if(!q) return;
	for(int i = q;i <= n + n;i += i & -i) t2[i] += x;
}
inline int cx2(int q){
	if(!q) return 0;
	int as = 0;
	for(int i = q;i;i -= i & -i) as += t2[i];
	return as;
}
inline bool is(int q){
	return l[f[q]] != q && r[f[q]] != q; 
}
inline void ud(int q){
	sz1[q] = sz1[l[q]] + sz1[r[q]] + (q <= n);
	sz2[q] = sz2[l[q]] + sz2[r[q]] + (q > n);
}
inline void rv(int q,int x){
	mn[q] = c[q] = x;
}
inline void ps(int q){
	if(!c[q]) return;
	if(l[q]) rv(l[q],c[q]);
	if(r[q]) rv(r[q],c[q]);
	c[q] = 0;
}
inline void ro(int q){
	int p = f[q];
	if(l[f[p]] == p) l[f[p]] = q;
	else if(r[f[p]] == p) r[f[p]] = q;
	f[q] = f[p];f[p] = q;
	if(l[p] == q){
		l[p] = r[q];r[q] = p;
		if(l[p]) f[l[p]] = p;
	}
	else{
		r[p] = l[q];l[q] = p;
		if(r[p]) f[r[p]] = p;
	}
	ud(p);ud(q);
}
inline void gx(int q){
	if(!is(q)) gx(f[q]);
	ps(q);
}
inline void sp(int q){
	gx(q);
	while(!is(q)){
		int p = f[q];
		if(!is(p)){
			if((l[f[p]] == p) ^ (l[p] == q)) ro(q);
			else ro(p);
		}
		ro(q);
	}
}
inline void ct(int q){
	sp(q);
	if(!l[q]){
		f[q] = 0;return;
	}
	f[l[q]] = f[q];l[q] = f[q] = 0;
	ud(q);
}
inline void lk(int u,int v){
	sp(u);
	assert(!f[u]);
	f[u] = v;
}
inline void ac(int u,int v,int sj){
	//cerr<<"&&&"<<u<<" "<<v<<" "<<sj<<endl;
	ct(v);
	int p = 0;
	while(u){
		sp(u);
		r[u] = 0;
		ud(u);
		//cerr<<"()()()"<<u<<" "<<mn[u]<<" "<<sz1[u]<<" "<<sz2[u]<<endl;
		xg(mn[u],-sz1[u]);
		xg2(mn[u],-sz2[u]);
		r[u] = p;
		ud(u);
		p = u;u = f[u];
	}
	rv(p,sj);xg(sj,sz1[p]);xg2(sj,sz2[p]);
	lk(v,ff[v]);
}
int main(){
	srand(time(0));rd();
	file();
	int i,j,u,v;
	n = read();m = read();q = read();
	for(i = 1;i <= n;++i) sz1[i] = 1;
	for(i = 1;i < n;++i) sz2[i + n] = 1;
	for(i = 1;i < n;++i) ins(read(),read());
	
	dfs(1);
	buildst();
	
	for(i = 1;i <= m;++i){
		a[i].x = read();a[i].y = read();a[i].l = lca(a[i].x,a[i].y);
		//cerr<<a[i].l<<"()"<<endl;
	}
	for(i = 1;i <= q;++i){
		b[i].l = read();b[i].r = read();b[i].id = i;
	}
	sort(b + 1,b + q + 1);
	//cerr<<clock()<<endl;
	//return 0;
	for(i = 1,j = 1;i <= m;++i){
		ac(a[i].x,a[i].l,i * 2 - 1);ac(a[i].y,a[i].l,i * 2);
		for(;j <= q && b[j].r == i;++j){
			//cerr<<"???"<<b[j].id<<" "<<
			as[b[j].id] = (cx(i * 2) - cx(b[j].l * 2 - 2)) - (cx2(i * 2) - cx2(b[j].l * 2 - 2));
		} 
	}
	//cerr<<clock()<<endl;
	for(i = 1;i <= q;++i) print(as[i]),pc('\n');
	//cerr<<clock()<<endl;
	return 0;
}
