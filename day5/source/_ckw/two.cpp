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
	freopen("two.in","r",stdin);
	freopen("two.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
char c[100010];
int n,k;
li as;
int fa[200010],son[200010][26],len[200010],sz[200010],cnt = 1,lst = 1,fsts[200010],nxt[200010];
set<int> rt[200010];
int f[5000010],l[5000010],r[5000010],vl[5000010],ss[5000010],gg[5000010],tto,gn[200010];
int wz[200010];
inline void ins(int x,int id){
	int p = lst,np = ++cnt;lst = np;len[np] = len[p] + 1;sz[np] = 1;rt[np].insert(id);
	for(;p && !son[p][x];p = fa[p]) son[p][x] = np;
	if(!p) fa[np] = 1;
	else{
		int q = son[p][x];
		if(len[q] == len[p] + 1) fa[np] = q;
		else{
			int nq = ++cnt;
			len[nq] = len[p] + 1;
			memcpy(son[nq],son[q],sizeof(son[nq]));
			fa[nq] = fa[q];
			fa[q] = fa[np] = nq;
			for(;son[p][x] == q;p = fa[p]) son[p][x] = nq;
		}
	}
}
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
inline void cr(int q,int &rt){
	//cerr<<"*"<<q<<endl;
	if(!rt){
		rt = ++tto;vl[tto] = q;ss[tto] = gg[tto] = 1;return;
	}
	int nw = rt;
	while(1){
		++ss[nw];
		if(vl[nw] == q){
			++gg[nw];sp(nw);rt = nw;return;
		}
		else if(q < vl[nw]){
			if(!l[nw]){
				l[nw] = ++tto;f[tto] = nw;vl[tto] = q;ss[tto] = gg[tto] = 1;sp(tto);rt = tto;return;
			}
			else nw = l[nw];
		}
		else{
			if(!r[nw]){
				r[nw] = ++tto;f[tto] = nw;vl[tto] = q;ss[tto] = gg[tto] = 1;sp(tto);rt = tto;return;
			}
			else nw = r[nw];
		}
	}
}
inline int fd(int q,int &rt){
	int nw = rt;
	while(1){
		if(!nw) return -1;
		if(vl[nw] == q){
			sp(nw);rt = nw;return nw;
		}
		else if(q < vl[nw]) nw = l[nw];
		else nw = r[nw];
	}
}
inline void del(int q,int &rt){
	//cerr<<"&"<<q<<endl;
	int p = fd(q,rt);
	if(p == -1) return; 
	sp(p);rt = p;
	if(gg[p] > 1) --gg[p],--ss[p];
	else{
		int u = l[p],v = r[p];
		f[u] = f[v] = l[p] = r[p] = 0;
		if(!u){rt = v;return;}
		if(!v){rt = u;return;}
		while(r[u]) u = r[u];sp(u);
		r[u] = v;f[v] = u;ud(u);rt = u;return;
	}
}
int nwq;
inline int cx(int k,int &rt,bool fg){
	//cerr<<k<<"*"<<fg<<" "<<ss[rt]<<endl;
	if(k <= 0) return -1;
	if(k > ss[rt]) return n + 1;
	int nw = rt;
	while(1){
		if(ss[l[nw]] >= k) nw = l[nw];
		else if(ss[l[nw]] + gg[nw] >= k){
			if(fg || ss[l[nw]] + gg[nw] == k){
				sp(nw);rt = nw;return vl[nw];
			} 
			sp(nw);rt = nw;return -2;
		}
		else k -= ss[l[nw]] + gg[nw],nw = r[nw];
	}
}
inline void dbg(int q){
	if(l[q]) dbg(l[q]);
	cerr<<q<<":::"<<ss[q]<<" "<<gg[q]<<" "<<vl[q]<<endl;
	if(r[q]) dbg(r[q]); 
}
inline void dfs(int q){
	for(int i = fsts[q];i;i = nxt[i]){
		dfs(i);
		int u = q,v = i;
		if(sz[u] < sz[v]) swap(u,v);
		u = wz[u];v = wz[v];
		
		for(set<int>::iterator it = rt[v].begin();it != rt[v].end();++it){
			if(rt[u].empty()) rt[u].insert(*it);
			else{
				set<int>::iterator it2 = rt[u].lower_bound(*it);
				if(it2 == rt[u].end()){
					//cerr<<q<<" ";
					cr(*it - *(--it2),gn[u]);
				} 
				else if(it2 == rt[u].begin()){
					//cerr<<q<<" ";
					cr(*it2 - *it,gn[u]);
				} 
				else{
					int x = *it2,y = *(--it2);
					//cerr<<q<<":"<<endl;
					del(x - y,gn[u]);cr(x - *it,gn[u]);cr(*it - y,gn[u]);
				}
				rt[u].insert(*it);
			}
		}
		if(sz[q] < sz[i]) wz[q] = wz[i];
		sz[q] += sz[i];
	}
	//nwq = q;
	//cerr<<q<<"***"<<sz[q]<<" "<<wz[q]<<":"<<rt[wz[q]].size()<<endl;
	if(q != 1){
		//cerr<<q<<"()"<<len[q]<<" "<<len[fa[q]]<<endl;
		int u = cx(sz[q] - k,gn[wz[q]],0),v = cx(sz[q] - k + 1,gn[wz[q]],1);
		//cerr<<"&&&&&&&&&&"<<u<<" "<<v<<endl;
		//int lstas = as;
		if(u != -2) as += max(0,min(len[q],v - 1) - max(len[fa[q]],u - 1));
		//if(*rt[wz[q]].begin() == 59) cerr<<q<<"******"<<len[q]<<" "<<len[fa[q]]<<" "<<sz[q] - k<<" "<<u<<" "<<v<<" "<<as<<endl;
		//if(q == 243) dbg(gn[wz[q]]);
		//if(lstas != as) cerr<<q<<"()()()"<<len[q]<<" "<<len[fa[q]]<<" "<<as<<" "<<*rt[wz[q]].begin()<<" "<<c[*rt[wz[q]].begin()]<<endl;
	}
}
int main(){
	srand(time(0));rd();
	file();
	int i,j;
	scanf("%s",c + 1);n = strlen(c + 1);k = read();
	for(i = 1;i <= n;++i) ins(c[i] - 'a',i);
	for(i = 2;i <= cnt;++i) nxt[i] = fsts[fa[i]],fsts[fa[i]] = i;
	for(i = 1;i <= cnt;++i) wz[i] = i;
	dfs(1);
	print(as);pc('\n');
	return 0;
}
