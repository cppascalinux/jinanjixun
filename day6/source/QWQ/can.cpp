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
	freopen("can.in","r",stdin);
	freopen("can.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
li as;
int n,m,k,nw;
char c[10][10];
bool zt[10][10];
int vis[10][10];
int dx[4] = {-1,0,1,0},dy[4] = {0,1,0,-1};
inline void df(int x,int y){
	vis[x][y] = nw;
	for(int i = 0;i < 4;++i){
		int tx = x + dx[i],ty = y + dy[i];
		if(tx >= 1 && tx <= n && ty >= 1 && ty <= m && vis[tx][ty] != nw && zt[tx][ty] == zt[x][y]) df(tx,ty);
	}
}
inline bool chk(){
	bool sl1 = 0,sl2 = 0;
	for(int i = 1;i <= n;++i) for(int j = 1;j <= m;++j) if(vis[i][j] != nw){
		if(zt[i][j]){
			if(sl1) return 0;
			sl1 = 1;	
		}
		else{
			if(sl2) return 0;
			sl2 = 1;
		}
		df(i,j);
	}
	return 1;
}
inline bool chk0(int x,int y){
	bool sl = 0;
	for(int i = 1;i <= x;++i) for(int j = 1;j <= (i == x ? y : m);++j) if(vis[i][j] != nw && !zt[i][j]){
		if(sl) return 0;
		sl = 1;
		df(i,j);
	}
	return 1;
}
inline void dfs(int x,int y,int cha){
	++nw;
	if(!chk0(x,y - 1)) return;
	if(y == m + 1) ++x,y = 1;
	if(x == n + 1){
		++nw;
		if(abs(cha) <= k && chk()){
			++as;
		} 
		return;
	}
	if(c[x][y] != 'B' && (x == 1 || y == 1 || zt[x][y - 1] || zt[x - 1][y] || zt[x - 1][y - 1])) zt[x][y] = 0,dfs(x,y + 1,cha + 1);
	if(c[x][y] != 'A' && (x == 1 || y == 1 || !zt[x][y - 1] || !zt[x - 1][y] || !zt[x - 1][y - 1])) zt[x][y] = 1,dfs(x,y + 1,cha - 1);
	zt[x][y] = 0;
}
int main(){
	srand(time(0));rd();
	file();
	int i,j;
	n = read();m = read();k = read();
	for(i = 1;i <= n;++i) scanf("%s",c[i] + 1);
	//int d = clock();
	dfs(1,1,0);
	print(as);
	//cerr<<endl<<clock() - d<<endl;
	return 0;
}

