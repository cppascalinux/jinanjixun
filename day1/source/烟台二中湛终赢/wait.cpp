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
	freopen("wait.in","r",stdin);
	freopen("wait.out","w",stdout);
}
int n,m;
struct node{
	int l,r,w;
}a[100010];
struct lsh{
	int x,bel,fg;
}b[100010];
int cnt,nw;
inline bool operator < (lsh q,lsh w){
	return q.x == w.x ? q.fg < w.fg : q.x < w.x;
}
inline bool operator != (lsh q,lsh w){
	return q.x != w.x || q.fg != w.fg;
}
int fg[100010],zt[100010];
inline void dfs(int q){
	if(q == n + 1){
		for(int i = 1;i <= nw;++i) if(abs(fg[i]) > 1) return;
		for(int i = 1;i <= n;++i) print(zt[i]),pc(' ');
		exit(0);
	}
	if(a[q].w != 0){
		zt[q] = 1;
		for(int i = a[q].l;i <= a[q].r;++i) ++fg[i];
		dfs(q + 1);
		for(int i = a[q].l;i <= a[q].r;++i) --fg[i];
	}
	if(a[q].w != 1){
		zt[q] = 0;
		for(int i = a[q].l;i <= a[q].r;++i) --fg[i];
		dfs(q + 1);
		for(int i = a[q].l;i <= a[q].r;++i) ++fg[i];
	}
}
int main(){
	file();
	int i,j;
	n = read();m = read();
	for(i = 1;i <= n;++i){
		a[i].l = read();a[i].r = read();a[i].w = read();
		b[++cnt].x = a[i].l;b[cnt].fg = 0;b[cnt].bel = i;
		b[++cnt].x = a[i].r;b[cnt].fg = 1;b[cnt].bel = i;
	}
	sort(b + 1,b + cnt + 1);
	for(i = 1;i <= cnt;++i){
		if(b[i] != b[i - 1]) ++nw;
		if(b[i].fg == 0) a[b[i].bel].l = nw;
		else a[b[i].bel].r = nw - 1;
	}
	//for(i = 1;i <= n;++i) cerr<<a[i].l<<" "<<a[i].r<<endl;
	if(n <= 20){
		dfs(1);
		puts("-1");
		return 0;
	}
	
	return 0;
}
