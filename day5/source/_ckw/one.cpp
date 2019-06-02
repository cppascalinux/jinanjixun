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
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,a[30];
const int mo = 1000000007;
inline li ksm(li q,li w){
	li as = 1;
	while(w){
		if(w & 1) as = as * q % mo;
		q = q * q % mo;
		w >>= 1;
	}
	return as;
}
int cnt;
li f[650][650];
inline void xy(){
	register int i,j,k;
	for(i = 1;i <= cnt;++i){
		if(!f[i][i]){
			for(j = i;j <= cnt;++j) if(f[j][i]) break;
			if(j > cnt) return;
			for(k = i;k <= cnt + 1;++k) swap(f[i][k],f[j][k]);
		}
		li tmp = ksm(f[i][i],mo - 2);
		for(j = i;j <= cnt + 1;++j) (f[i][j] *= tmp) %= mo;
		for(j = i + 1;j <= cnt;++j){
			tmp = f[j][i];
			for(k = i;k <= cnt + 1;++k) (f[j][k] += mo - tmp * f[i][k] % mo) %= mo;
		}
	}
	for(i = cnt;i > 1;--i){
		for(j = 1;j < i;++j){
			(f[j][cnt + 1] += mo - f[j][i] * f[i][cnt + 1] % mo) %= mo;
			f[j][i] = 0;
		}
	}
}
struct node{
	vector<int> a;
}c[650];
inline bool operator < (node q,node w){
	if(q.a.size() != w.a.size()) return q.a.size() < w.a.size();
	for(int i = 0;i < q.a.size();++i) if(q.a[i] != w.a[i]) return q.a[i] < w.a[i];
	return 0;
}
map<node,int> mp;
int b[30];
inline void dfs(int q,int w,int e){
	if(w < 0) return;
	if(w == 0){
		node nw;nw.a.clear();
		for(int i = 1;i < q;++i) nw.a.push_back(b[i]);
		mp[nw] = ++cnt;c[cnt] = nw;
		return;
	}
	for(int i = 1;i <= e;++i){
		b[q] = i;
		dfs(q + 1,w - i,i);
	}
}
int tp[30];
bool vis[30];
inline bool cmp(int q,int w){return q > w;}
inline int bm(int *q){
	int nw,i;
	memset(vis,0,sizeof(vis));
	node an;an.a.clear();
	for(i = 1;i <= n;++i) if(!vis[i]){
		vis[i] = 1;nw = 1;
		for(i = q[i];!vis[i];i = q[i]) ++nw,vis[i] = 1;
		an.a.push_back(nw);
	}
	sort(an.a.begin(),an.a.end(),cmp);
	return mp[an];
}
int main(){
	srand(time(0));rd();
	file();
	int i,j,k;
	n = read();
	for(i = 1;i <= n;++i) a[i] = read();
	if(n == 2){
		print(a[1] - 1);pc('\n');return 0;
	}
	bool fg = 0;
	for(i = 1;i < n;++i) if(a[i] != i) fg = 1;
	if(!fg){
		pc('0');pc('\n');return 0;
	}
	dfs(1,n,n);
	li ny = mo - ksm(n * (n - 1) / 2,mo - 2);
	for(i = 1;i <= cnt;++i){
		f[i][i] = 1;
		if(i == 1) continue;
		int qwq = 0;
		for(j = 0;j < c[i].a.size();++j){
			for(k = qwq + 1;k < qwq + c[i].a[j];++k) tp[k] = k + 1;
			tp[qwq + c[i].a[j]] = qwq + 1;
			qwq += c[i].a[j];
		}
		//cerr<<i<<":";
		//for(j = 1;j <= n;++j) cerr<<tp[j]<<" ";cerr<<endl;
		for(j = 1;j < n;++j) for(k = j + 1;k <= n;++k){
			swap(tp[j],tp[k]);
			(f[i][bm(tp)] += ny) %= mo;
			swap(tp[j],tp[k]);
		}
		f[i][cnt + 1] = 1;
	}
	//for(i = 1;i <= cnt;++i){
	//	for(j = 1;j <= cnt + 1;++j) cerr<<f[i][j]<<" ";cerr<<endl;
	//}
	xy();
	//for(i = 1;i <= cnt;++i){
	//	for(j = 1;j <= cnt + 1;++j) cerr<<f[i][j]<<" ";cerr<<endl;
	//}
	print(f[bm(a)][cnt + 1]);pc('\n');
	return 0;
}

