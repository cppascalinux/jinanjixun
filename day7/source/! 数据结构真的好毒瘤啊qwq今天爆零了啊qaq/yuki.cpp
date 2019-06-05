#include<bits/stdc++.h>
using namespace std;
#define li long long
char buf[100010],*buff = buf + 100000;
#define gc (((buff == buf + 100000) ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
//#define gc getchar()
char bfu[100000010],*bfuu = bfu;
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
	freopen("yuki.in","r",stdin);
	freopen("yuki.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m;
struct edge{
	int to,nxt;
}e[2000010];
int cnt,fir[1000010],du[1000010];
inline void ins(int u,int v){
	e[++cnt].to = v;e[cnt].nxt = fir[u];fir[u] = cnt;
	e[++cnt].to = u;e[cnt].nxt = fir[v];fir[v] = cnt;
	++du[u];++du[v];
}
int fa[1000010],fsts[1000010],nxt[1000010],dpt[1000010],vl[1000010];
int wz[1000010],ed[1000010],nw,tou[1000010],mxe[1000010],sz[1000010],dfsx[1000010];
inline void dfs1(int q){
	sz[q] = 1;
	for(int i = fir[q];i;i = e[i].nxt) if(fa[q] != e[i].to){
		fa[e[i].to] = q;
		nxt[e[i].to] = fsts[q];
		fsts[q] = e[i].to;
		dpt[e[i].to] = dpt[q] + 1;
		dfs1(e[i].to);
		sz[q] += sz[e[i].to];
		if(sz[e[i].to] > sz[mxe[q]]) mxe[q] = e[i].to;
	}
}
inline void dfs2(int q){
	wz[q] = ++nw;dfsx[nw] = q;
	if(mxe[fa[q]] == q) tou[q] = tou[fa[q]];
	else tou[q] = q;
	if(mxe[q]) dfs2(mxe[q]);
	for(int i = fsts[q];i;i = nxt[i]) if(i != mxe[q]) dfs2(i);
	ed[q] = nw;
}
int t[1000010];
inline void xg(int q,int x){
	if(!q) return;
	for(int i = q;i <= n;i += i & -i) t[i] += x;
}
inline int cx(int q){
	if(!q) return 0;
	int as = 0;
	for(int i = q;i;i -= i & -i) as += t[i];
	return as;
}
inline int lca(int u,int v){
	while(tou[u] != tou[v]){
		if(dpt[tou[u]] < dpt[tou[v]]) v = fa[tou[v]];
		else u = fa[tou[u]];
	}
	return dpt[u] > dpt[v] ? v : u;
}

int qaq[1000010],tot;
int f[2000010],l[2000010],r[2000010],val[2000010],ss[2000010],gg[2000010],tto,gn[1000010];
int bin[2000010],ftt;
#define ud(q) (ss[q] = ss[l[q]] + ss[r[q]] + gg[q])
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
inline void sp(int q){
	while(f[q]){
		int p = f[q];
		if(f[p]){
			if((l[f[p]] == p) ^ (l[p] == q)) ro(q);
			else ro(p);
		}
		ro(q);
	}
}
inline int xind(int q){
	int p = ftt ? bin[ftt--] : ++tto;
	f[p] = l[p] = r[p] = 0;
	val[p] = q;ss[p] = gg[p] = 1;
	return p;
}
inline void cr(int q,int &rt){
	if(!rt){
		rt = xind(q);return;
	}
	int nw = rt;
	while(1){
		++ss[nw];
		if(val[nw] == q){
			++gg[nw];sp(nw);rt = nw;return;
		}
		else if(q < val[nw]){
			if(!l[nw]){
				int p = xind(q);
				l[nw] = p;f[p] = nw;sp(p);rt = p;return;
			}
			else nw = l[nw];
		}
		else{
			if(!r[nw]){
				int p = xind(q);
				r[nw] = p;f[p] = nw;sp(p);rt = p;return;
			}
			else nw = r[nw];
		}
	}
}
inline int fd(int q,int &rt){
	int nw = rt;
	while(1){
		if(!nw) return -1;
		if(val[nw] == q){
			sp(nw);rt = nw;return nw;
		}
		else if(q < val[nw]) nw = l[nw];
		else nw = r[nw];
	}
}
inline void del(int q,int &rt){
	int p = fd(q,rt);
	if(p == -1) return; 
	sp(p);rt = p;
	if(gg[p] > 1) --gg[p],--ss[p];
	else{
		int u = l[p],v = r[p];
		f[u] = f[v] = l[p] = r[p] = ss[p] = gg[p] = val[p] = 0;
		bin[++ftt] = p;
		if(!u){rt = v;return;}
		if(!v){rt = u;return;}
		while(r[u]) u = r[u];sp(u);
		r[u] = v;f[v] = u;ud(u);rt = u;return;
	}
}
inline int qy(int k,int &rt){
	int nw = rt;
	while(1){
		if(ss[l[nw]] >= k) nw = l[nw];
		else if(ss[l[nw]] + gg[nw] >= k){
			sp(nw);rt = nw;return val[nw];
		}
		else k -= ss[l[nw]] + gg[nw],nw = r[nw];
	}
}
#define cc(x) (vl[x] + cx(ed[x]) - cx(wz[x] - 1))
struct qry{
	int op,u,v,w;
}b[1000010];
int main(){
	srand(time(0));rd();
	file();
	int i,j,u,v,op,w,x;
	//cerr<<clock()<<endl;
	n = read();m = read();
	for(i = 1;i <= n;++i) vl[i] = read();
	for(i = 1;i < n;++i){
		u = read();v = read();ins(u,v);
	}
	li ttd = 0;
	for(i = 1;i <= m;++i){
		b[i].op = read();b[i].u = read(),b[i].v = read();
		if(b[i].op == 1) b[i].w = read();
		else ttd += du[b[i].u];
	}
	//cerr<<clock()<<endl;
	dfs1(1);dfs2(1);
	//cerr<<ttd<<" "<<clock()<<endl;
	if(ttd <= 0000000){
		for(i = 1;i <= m;++i){
			
			if(b[i].op == 1){
				u = b[i].u;v = b[i].v;w = b[i].w;x = lca(u,v);
				xg(wz[u],w);xg(wz[v],w);xg(wz[x],-w);xg(wz[fa[x]],-w);
			}
			else{
				u = b[i].u;v = b[i].v;
				qaq[tot = 1] = vl[u] + cx(ed[u]) - cx(wz[u] - 1);
				for(j = fir[u];j;j = e[j].nxt) qaq[++tot] = vl[e[j].to] + cx(ed[e[j].to]) - cx(wz[e[j].to] - 1);
				nth_element(qaq + 1,qaq + v,qaq + tot + 1);
				print(qaq[v]);pc('\n');
			}
		}
	}
	else{
		for(i = 1;i <= n;++i) for(j = fsts[i];j;j = nxt[j]) if(j != mxe[i]) cr(vl[j],gn[i]);
		for(i = 1;i <= m;++i){
			if(b[i].op == 1){
				u = b[i].u;v = b[i].v;w = b[i].w;x = lca(u,v);
				int p = tou[u];
				while(p != 1 && dpt[p] >= dpt[x]){
					del(cc(p),gn[fa[p]]);
					p = tou[fa[p]];
				}
				p = tou[v];
				while(p != 1 && dpt[p] > dpt[x]){
					del(cc(p),gn[fa[p]]);
					p = tou[fa[p]];
				}
				xg(wz[u],w);xg(wz[v],w);xg(wz[x],-w);xg(wz[fa[x]],-w);
				p = tou[u];
				while(p != 1 && dpt[p] >= dpt[x]){
					cr(cc(p),gn[fa[p]]);
					p = tou[fa[p]];
				}
				p = tou[v];
				while(p != 1 && dpt[p] > dpt[x]){
					cr(cc(p),gn[fa[p]]);
					p = tou[fa[p]];
				}
			}
			else{
				u = b[i].u;v = b[i].v;
				cr(cc(u),gn[u]);
				if(fa[u]) cr(cc(fa[u]),gn[u]);
				if(mxe[u]) cr(cc(mxe[u]),gn[u]);
				print(qy(v,gn[u]));pc('\n');
				del(cc(u),gn[u]);
				if(fa[u]) del(cc(fa[u]),gn[u]);
				if(mxe[u]) del(cc(mxe[u]),gn[u]);
			}
		}
	}
	//cerr<<clock()<<endl;
	fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}

