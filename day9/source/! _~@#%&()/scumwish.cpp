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
	freopen("scumwish.in","r",stdin);
	freopen("scumwish.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
const int mo = 100000007;
int n,m;
bool a[25][25],b[25][25];
int f[2][21][1050000];
#define chk(u,v) (((u) >> (v)) & 1)
int cnt,tto;
inline int dfs(int x,int y,int s){
	//cerr<<x<<" "<<y<<" "<<s<<endl;
	++cnt;
	while(s & 1) ++y,s >>= 1;
	while(y > m) ++x,y -= m;
	if(x > n) return y != 1 || s ? 0 : 1;
	if(f[x][y][s >> 1]) return f[x][y][s >> 1] == -1 ? 0 : f[x][y][s >> 1];
	//cerr<<"***"<<x<<" "<<y<<" "<<s<<endl;
	int as = 0;
	as += dfs(x,y + 1,s >> 1);
	if(y != m && !chk(s,1) && a[x][y]) as += dfs(x,y + 2,s >> 2);
	if(x != n && b[x][y]) as += dfs(x,y + 1,(s >> 1) | (1 << m - 1));
	if(x != n && y != m && !chk(s,1) && a[x][y] && b[x][y]) as += dfs(x,y + 2,(s >> 2) | (1 << m - 2));
	if(x != n && y != 1 && b[x][y] && a[x + 1][y - 1] && !chk(s,m - 1)) as += dfs(x,y + 1,(s >> 1) | (1 << m - 1) | (1 << m - 2));
	if(as) ++tto;
	as %= mo;f[x][y][s >> 1] = as ? as : -1;
	//cerr<<x<<" "<<y<<" "<<s<<":"<<as<<endl;
	return as;
}
int main(){
	srand(time(0));rd();
	file();
	int i,j,k,l;
	//n = read();m = read();
	n = m = 20;
	for(i = 1;i <= n;++i) for(j = 1;j < m;++j) a[i][j] = read();
	for(i = 1;i < n;++i) for(j = 1;j <= m;++j) b[i][j] = read();
	int mx = 1 << m;
	f[1][1][0] = 1;
	for(i = 1;i <= n;++i){
		bool tp = i & 1;
		memset(f[!tp],0,sizeof(f[!tp]));
		for(j = 1;j <= m;++j){
			for(k = 0;k < mx;++k) if(f[tp][j][k]){
				f[tp][j][k] %= mo;
				if(k & 1){
					(j == m ? f[!tp][1][k >> 1] : f[tp][j + 1][k >> 1]) += f[tp][j][k];continue;
				}
				if(j == m){
					f[!tp][1][k >> 1] += f[tp][j][k];
					if(i != n && b[i][j]) f[!tp][1][(k >> 1) | (1 << m - 1)] += f[tp][j][k];
					if(i != n && j != 1 && b[i][j] && a[i + 1][j - 1] && !chk(k,m - 1)) f[!tp][1][(k >> 1) | (1 << m - 1) | (1 << m - 2)] += f[tp][j][k];
				}
				else{
					f[tp][j + 1][k >> 1] += f[tp][j][k];
					if(!chk(k,1) && a[i][j]) (j == m - 1 ? f[!tp][1][k >> 2] : f[tp][j + 2][k >> 2]) += f[tp][j][k];
					if(i != n && b[i][j]) f[tp][j + 1][(k >> 1) | (1 << m - 1)] += f[tp][j][k];
					if(i != n && !chk(k,1) && a[i][j] && b[i][j]) (j == m - 1 ? f[!tp][1][(k >> 2) | (1 << m - 2)] : f[tp][j + 2][(k >> 2) | (1 << m - 2)]) += f[tp][j][k];
					if(i != n && j != 1 && b[i][j] && a[i + 1][j - 1] && !chk(k,m - 1)) f[tp][j + 1][(k >> 1) | (1 << m - 1) | (1 << m - 2)] += f[tp][j][k];
				}
			}
		}
	}
	print(f[n + 1 & 1][1][0] % mo);pc('\n');
	//cerr<<clock()<<endl;
	return 0;
}
