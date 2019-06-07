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
int n,m,p1,ttsz,ed,vv;
li as,c,ds[200010];
int wz[200010],ee[200010],nw;
const int mo = 1000000007;
int st[200010],ft;
bool ys[200010];
int b[200010],tot;
struct tree4{
	int fa[200010],nxt[200010],fsts[200010];
	li sz[200010][2],vl[200010][2],vd[200010][2],dd[200010][2];
	inline void dfs(int q){
		//cerr<<q<<"*"<<endl;
		//cerr<<q<<"&&&"<<fa[q]<<" "<<sz[q][0]<<" "<<sz[q][1]<<" "<<vl[q][0]<<" "<<vl[q][1]<<" "<<dd[q][0]<<" "<<dd[q][1]<<" "<<vd[q][0]<<" "<<vd[q][1]<<"*"<<ds[q]<<" "<<as<<endl;
		for(int i = fsts[q];i;i = nxt[i]){
			dfs(i);
			(as += vd[q][0] * sz[i][1] + vd[q][1] * sz[i][0] + vd[i][1] * sz[q][0] + vd[i][0] * sz[q][1]) %= mo;
			(as += vl[q][0] * dd[i][1] + vl[q][1] * dd[i][0] + vl[i][1] * dd[q][0] + vl[i][0] * dd[q][1]) %= mo;
			(as -= (vl[q][0] * sz[i][1] + vl[q][1] * sz[i][0] + vl[i][1] * sz[q][0] + vl[i][0] * sz[q][1]) % mo * 2 * ds[q]) %= mo;
			(sz[q][0] += sz[i][0]) %= mo;(sz[q][1] += sz[i][1]) %= mo;
			(vl[q][0] += vl[i][0]) %= mo;(vl[q][1] += vl[i][1]) %= mo;
			(vd[q][0] += vd[i][0]) %= mo;(vd[q][1] += vd[i][1]) %= mo;
			(dd[q][0] += dd[i][0]) %= mo;(dd[q][1] += dd[i][1]) %= mo;
		}
		//cerr<<q<<"***"<<fa[q]<<" "<<sz[q][0]<<" "<<sz[q][1]<<" "<<vl[q][0]<<" "<<vl[q][1]<<" "<<dd[q][0]<<" "<<dd[q][1]<<" "<<vd[q][0]<<" "<<vd[q][1]<<"*"<<ds[q]<<" "<<as<<endl;
	}
	inline void dfs2(int q){
		for(int i = fsts[q],j = nxt[i];i;i = j,j = nxt[i]) dfs2(i);
		fa[q] = nxt[q] = fsts[q] = sz[q][0] = sz[q][1] = vl[q][0] = vl[q][1] = vd[q][0] = vd[q][1] = dd[q][0] = dd[q][1] = 0; 
	}
}t4;
struct tree3{
    int to[400000],nxt[400000];
    li val[400000],dis[200000];
    int cnt = 1,fir[200000],sz[200000];
    bool vis[200000];
    inline void ins(int u,int v,li w){
    	//cerr<<u<<" "<<v<<"*"<<w<<endl;
        to[++cnt] = v;nxt[cnt] = fir[u];fir[u] = cnt;val[cnt] = w;
        to[++cnt] = u;nxt[cnt] = fir[v];fir[v] = cnt;val[cnt] = w;
    }
    void dfs(int q,int lst){
        if(q <= n) ++p1;
        //cerr<<q<<"()"<<endl;
        sz[q] = 1;
        for(int i = fir[q];i;i = nxt[i]) if(!vis[i >> 1] && to[i] != lst){
            dfs(to[i],q);
            if(max(sz[to[i]],ttsz - sz[to[i]]) < vv) vv = max(sz[to[i]],ttsz - sz[to[i]]),ed = i;
            sz[q] += sz[to[i]];
        }
    }
    void dfs2(int q,int lst,bool fg){
    	if(q <= n){
    		++t4.sz[q][fg];(t4.vl[q][fg] += dis[q]) %= mo;(t4.vd[q][fg] += dis[q] * ds[q]) %= mo;(t4.dd[q][fg] += ds[q]) %= mo;
    		ys[q] = fg;b[++tot] = q;
		}
		for(int i = fir[q];i;i = nxt[i]) if(!vis[i >> 1] && to[i] != lst){
            dis[to[i]] = (dis[q] + val[i]) % mo;
            dfs2(to[i],q,fg);
        }
    }
}t3;
struct tree1{
    int to[200000],nxt[200000];
    li val[200000];
    int cnt,fir[200000];
    inline void ins(int u,int v,li w){
        to[++cnt] = v;nxt[cnt] = fir[u];fir[u] = cnt;val[cnt] = w;
        to[++cnt] = u;nxt[cnt] = fir[v];fir[v] = cnt;val[cnt] = w;
    }
    inline void dfs(int q,int lst){
        int la = q;
        for(int i = fir[q];i;i = nxt[i]) if(to[i] != lst){
            t3.ins(la,++m,0);t3.ins(la = m,to[i],val[i]);
        }
        for(int i = fir[q];i;i = nxt[i]) if(to[i] != lst) dfs(to[i],q);
    }
}t1;

struct tree2{
    int to[200000],nxt[200000],dpt[200010];
    li val[200000];
    int cnt,fir[100000],fa[200010],sz[200010],mx[200010],bg[200010];
    inline void ins(int u,int v,li w){
        to[++cnt] = v;nxt[cnt] = fir[u];fir[u] = cnt;val[cnt] = w;
        to[++cnt] = u;nxt[cnt] = fir[v];fir[v] = cnt;val[cnt] = w;
    }
    void dfs(int q,int lst){
    	wz[q] = ++nw;sz[q] = 1;
		for(int i = fir[q];i;i = nxt[i]) if(to[i] != lst){
			fa[to[i]] = q;dpt[to[i]] = dpt[q] + 1;
            ds[to[i]] = (ds[q] + val[i]) % mo;
            dfs(to[i],q);
            sz[q] += sz[to[i]];
            if(sz[to[i]] > sz[mx[q]]) mx[q] = to[i];
        }
        ee[q] = nw;
    }
    inline void dfs2(int q){
    	if(mx[fa[q]] != q) bg[q] = q;
    	else bg[q] = bg[fa[q]];
    	if(mx[q]) dfs2(mx[q]);
    	for(int i = fir[q];i;i = nxt[i]) if(to[i] != fa[q] && to[i] != mx[q]) dfs2(to[i]);
	}
	inline int lca(int u,int v){
		//cerr<<u<<"()"<<v<<" "<<bg[u]<<" "<<bg[v]<<" "<<dpt[bg[u]]<<" "<<dpt[bg[v]]<<endl;
		while(bg[u] != bg[v]){
			if(dpt[bg[u]] > dpt[bg[v]]) u = fa[bg[u]];
			else v = fa[bg[v]];
		}
		//cerr<<(dpt[u] < dpt[v] ? u : v)<<endl;
		return dpt[u] < dpt[v] ? u : v;
	}
}t2;
inline bool cmp(int q,int w){
	return wz[q] < wz[w];
}
inline bool isf(int u,int v){
	return wz[u] < wz[v] && ee[u] >= ee[v];
}
void work(int q){
    if(ttsz <= 1) return;
    ed = p1 = 0;vv = ttsz + 1;t3.dfs(q,0);c = t3.val[ed];
    if(p1 <= 1) return;
    int nd1 = t3.to[ed],nd2 = t3.to[ed ^ 1],sz1 = t3.sz[nd1],sz2 = ttsz - sz1;
    t3.vis[ed >> 1] = 1;t3.dis[nd1] = c;t3.dis[nd2] = 0;
    tot = ft = 0;
    t3.dfs2(nd1,0,0);t3.dfs2(nd2,0,1);b[++tot] = 1;
    sort(b + 1,b + tot + 1,cmp);
    //for(int i = 1;i <= tot;++i) cerr<<b[i]<<" ";cerr<<endl;
    int tto = tot,i,j;
    for(i = 1;i < tto;++i) b[++tot] = t2.lca(b[i],b[i + 1]);
	sort(b + 1,b + tot + 1,cmp);
	//for(i = 1;i <= n;++i) cerr<<wz[i]<<" ";cerr<<endl;
	//for(i = 1;i <= n;++i) cerr<<ee[i]<<" ";cerr<<endl;
	//for(i = 1;i <= tot;++i) cerr<<b[i]<<" ";cerr<<endl;
	for(i = 1;i <= tot;++i) if(b[i] != b[i - 1]){
		while(ft && !isf(st[ft],b[i])) --ft;
		//cerr<<b[i]<<"()"<<st[ft]<<endl;
		t4.fa[b[i]] = st[ft];t4.nxt[b[i]] = t4.fsts[st[ft]];t4.fsts[st[ft]] = b[i];
		st[++ft] = b[i];
	}
	t4.dfs(1);
	t4.dfs2(1);
	//cerr<<nd1<<" "<<nd2<<"*"<<as<<" "<<p1<<endl;
    ttsz = sz1;work(nd1);ttsz = sz2;work(nd2);
}
int main(){
	srand(time(0));rd();
	file();
	int i,j,u,v;
	li w;
	n = m = read();
	for(i = 1;i < n;++i){
		u = read();v = read();w = read();t1.ins(u,v,w);
	}
	for(i = 1;i < n;++i){
		u = read();v = read();w = read();t2.ins(u,v,w);
	}
	t1.dfs(1,0);t2.dfs(1,0);t2.dfs2(1);
	ttsz = m;work(1);
	print((as * 2 % mo + mo) % mo);pc('\n');
	return 0;
}

