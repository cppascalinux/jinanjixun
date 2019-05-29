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
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
}
int n,m;
struct edge{
	int to,nxt;
	li val;
}e[200010];
int cnt,fir[100010];
inline void ins(int u,int v,li w){
	e[++cnt].to = v;e[cnt].nxt = fir[u];fir[u] = cnt;e[cnt].val = w;
	e[++cnt].to = u;e[cnt].nxt = fir[v];fir[v] = cnt;e[cnt].val = w;
}
li a[100010],as;
li b[100010],sb[100010];
struct spl{
	int f[100010],l[100010],r[100010],rt,cnt,sz[100010];
	li a[100010],s[100010];
	inline void ud(int q){
		s[q] = s[l[q]] + s[r[q]] + a[q];
		sz[q] = sz[l[q]] + sz[r[q]] + 1;
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
	inline void sp(int q){
		while(f[q]){
			int p = f[q];
			if(f[p]){
				if((l[f[p]] == p) ^ (l[p] == q)) ro(q);
				else ro(p);
			}
			ro(q);
		}
		rt = q;
	}
	inline void dfs(int q){
		if(l[q]) dfs(l[q]);
		cerr<<q<<":"<<f[q]<<" "<<l[q]<<" "<<r[q]<<"  "<<a[q]<<" "<<s[q]<<" "<<sz[q]<<endl;
		if(r[q]) dfs(r[q]);
	}
	inline void ins(li q){
		if(!rt){
			rt = ++cnt;a[rt] = s[rt] = q;sz[rt] = 1;return;
		}
		int nw = rt;
		while(1){
			s[nw] += q;++sz[nw];
			if(q <= a[nw]){
				if(!l[nw]){
					l[nw] = ++cnt;f[cnt] = nw;a[cnt] = s[cnt] = q;sz[cnt] = 1;
					sp(cnt);
					return;
				}
				else nw = l[nw];
			}
			else{
				if(!r[nw]){
					r[nw] = ++cnt;f[cnt] = nw;a[cnt] = s[cnt] = q;sz[cnt] = 1;
					sp(cnt);
					return;
				}
				else nw = r[nw];
			}
		}
	}
	inline li cx(){
		int nw = rt,ss = 0,lst = nw;
		li as = 0;
		while(nw){
			if(a[nw] < b[ss + sz[l[nw]] + 1]){
				as += s[l[nw]] + a[nw];
				ss += sz[l[nw]] + 1;
				lst = nw;nw = r[nw];
			}
			else lst = nw,nw = l[nw];
		}
		sp(lst);
		return sb[ss] - as;
	}
}t;
int fa[100010],dpt[100010];
li val[100010];

inline void dfs(int q){
	for(int i = fir[q];i;i = e[i].nxt) if(e[i].to != fa[q]){
		fa[e[i].to] = q;
		val[e[i].to] = e[i].val;
		dpt[e[i].to] = dpt[q] + 1;
		dfs(e[i].to);
	}
}
li f[100010][2];
int ww[100010][2],mx;
inline void wk(int q){
	f[q][0] = f[q][1] = 0;
	ww[q][0] = ww[q][1] = q;
	for(int i = fir[q];i;i = e[i].nxt) if(fa[e[i].to] == q){
		wk(e[i].to);
		if(f[e[i].to][0] + val[e[i].to] > f[q][0]){
			f[q][1] = f[q][0];ww[q][1] = ww[q][0];
			f[q][0] = f[e[i].to][0] + val[e[i].to];ww[q][0] = ww[e[i].to][0];
		}
		else if(f[e[i].to][0] + val[e[i].to] > f[q][1]){
			f[q][1] = f[e[i].to][0] + val[e[i].to];ww[q][1] = ww[e[i].to][0];
		}
	}
	
	if(f[q][0] + f[q][1] > f[mx][0] + f[mx][1]) mx = q;
}

int main(){
	file();
	int u,v,w,i,j;
	n = read();m = read();
	for(i = 1;i < n;++i){
		u = read();v = read();w = read();ins(u,v,w);as += w * 2;
	}
	for(i = 1;i <= m;++i) a[i] = read();
	dfs(1);
	print(as);pc(' ');	
	bool fg = 1;
	for(i = 1;i <= cnt;i += 2) if(e[i].to != 1 && e[i + 1].to != 1){
		fg = 0;break;
	}
	if(fg){
		for(i = 1;i <= cnt;i += 2) sb[i + 1 >> 1] = e[i].val;
		sort(sb + 1,sb + n);
		int tto = 0;
		for(i = n - 1;i;i -= 2) b[++tto] = sb[i] + sb[i - 1];
		memset(sb,0,sizeof(sb));for(i = 1;i <= tto;++i) sb[i] = sb[i - 1] + b[i];
		for(i = 1;i <= m;++i){
			t.ins(a[i]);
			print(as - t.cx());pc(' ');
		}
		return 0;
	}
	for(i = 1;i <= m;++i){
		mx = 0;
		wk(1);
		if(f[mx][0] + f[mx][1] > 0){
			b[i] = f[mx][0] + f[mx][1];
			sb[i] = sb[i - 1] + b[i];
			for(j = ww[mx][0];j != mx;j = fa[j]) val[j] = -val[j];
			for(j = ww[mx][1];j != mx;j = fa[j]) val[j] = -val[j];
		}
		else break;
	}
	for(i = 1;i <= m;++i){
		t.ins(a[i]);
		print(as - t.cx());pc(' ');
		/*j = i;while(j > 1 && a[j] < a[j - 1]) swap(a[j],a[j - 1]),--j;
		li an = as;
		for(j = 1;j <= i;++j){
			if(a[j] >= b[j]) break;
			else an += a[j] - b[j];
		}
		print(an);pc(' ');*/
	}
	return 0;
}
