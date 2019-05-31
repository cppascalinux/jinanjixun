#include<bits/stdc++.h>
using namespace std;
#define li long long
#define gc getchar()
#define pc putchar
inline int read(){
	int x = 0,c = gc;
	while(!isdigit(c)) c = gc;
	while(isdigit(c)) x = x * 10 + c - '0',c = gc;
	return x;
}
inline void print(int x){
	if(x >= 10) print(x / 10);
	pc(x % 10 + '0');
}
inline void file(){
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m;
char cc[510];
int a[510][510],b[510][510],c[510][510],d[510][510];
int dx[4] = {-1,0,1,0},dy[4] = {0,1,0,-1};
int fg[510][510],cnt,st[250010],ft,gf[510][510],tto;
bool fw[250010];
inline void dfs(int x,int y){
	fg[x][y] = cnt;
	for(int i = 0;i < 4;++i){
		int tx = x + dx[i],ty = y + dy[i];
		if(tx >= 1 && tx <= n && ty >= 1 && ty <= m && a[tx][ty] && !fg[tx][ty]) dfs(tx,ty);
	}
}
inline void dfs2(int x,int y){
	gf[x][y] = tto;
	for(int i = 0;i < 4;++i){
		int tx = x + dx[i],ty = y + dy[i];
		if(tx >= 1 && tx <= n && ty >= 1 && ty <= m){
			if(!a[tx][ty] && !gf[tx][ty]) dfs2(tx,ty);
			if(a[tx][ty] && !fw[fg[tx][ty]]) fw[fg[tx][ty]] = 1,st[++ft] = fg[tx][ty];
		}
	}
}
inline bool chk3(){
	for(int i = 1;i <= n;++i) for(int j = 1;j <= m;++j) if(!a[i][j] && !gf[i][j]){
		++tto;
		dfs2(i,j);
		if(ft == cnt) return 1;
		while(ft) fw[st[ft--]] = 0;
	}
	return 0;
}
int main(){
	srand(time(0));rd();
	file();
	int i,j,k,l;
	n = read();m = read();
	for(i = 1;i <= n;++i){
		scanf("%s",cc + 1);
		for(j = 1;j <= m;++j) a[i][j] = cc[j] - '0'; 
	}
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j) if(a[i][j] && !fg[i][j]){
		++cnt;dfs(i,j);
	}
	if(cnt == 0){
		pc('0');pc('\n');return 0;
	}
	if(cnt == 1){
		pc('1');pc('\n');pc('+');pc('\n');
		for(i = 1;i <= n;++i){
			for(j = 1;j <= m;++j) pc(a[i][j] + '0');pc('\n');
		}
		return 0;
	}
	if(cnt == 2){
		pc('2');pc('\n');
		pc('+');pc('\n');
		for(i = 1;i <= n;++i){
			for(j = 1;j <= m;++j) pc(fg[i][j] == 1 ? '1' : '0');pc('\n');
		}
		pc('+');pc('\n');
		for(i = 1;i <= n;++i){
			for(j = 1;j <= m;++j) pc(fg[i][j] == 2 ? '1' : '0');pc('\n');
		}
		return 0;
	}
	if(chk3()){
		pc('2');pc('\n');
		pc('+');pc('\n');
		for(i = 1;i <= n;++i){
			for(j = 1;j <= m;++j) pc(fg[i][j] || gf[i][j] == tto ? '1' : '0');pc('\n');
		}
		pc('-');pc('\n');
		for(i = 1;i <= n;++i){
			for(j = 1;j <= m;++j) pc(gf[i][j] == tto ? '1' : '0');pc('\n');
		}
		return 0;
	}
	if(n == 1){
		print(cnt);pc('\n');
		for(i = 1;i <= cnt;++i){
			pc(i % 2 ? '+' : '-');pc('\n');
			for(k = 1;k <= m;++k) if(a[1][k]) break;
			for(l = m;l;--l) if(a[1][l]) break; 
			for(j = 1;j < k;++j) pc('0');
			for(;j <= l;++j) pc('1'),a[1][j] += (i % 2 ? -1 : 1);
			for(;j <= m;++j) pc('0');
			pc('\n');
		}
		return 0;
	}
	if(m == 1){
		print(cnt);pc('\n');
		for(i = 1;i <= cnt;++i){
			pc(i % 2 ? '+' : '-');pc('\n');
			for(k = 1;k <= n;++k) if(a[k][1]) break;
			for(l = n;l;--l) if(a[l][1]) break; 
			for(j = 1;j < k;++j) pc('0'),pc('\n');
			for(;j <= l;++j) pc('1'),pc('\n'),a[j][1] += (i % 2 ? -1 : 1);
			for(;j <= n;++j) pc('0'),pc('\n');
		}
		return 0;
	}
	pc('3');pc('\n');
	if(n == 2){
		for(i = 1;i <= m;++i) b[1][i] = 1,b[2][i] = a[2][i];
		pc('+');pc('\n');
		for(i = 1;i <= n;++i){
			for(j = 1;j <= m;++j) pc(b[i][j] + '0');pc('\n');
		}
		pc('-');pc('\n');
		for(i = 1;i <= n;++i){
			for(j = 1;j <= m;++j) pc('1');pc('\n');
		}
		for(i = 1;i <= m;++i) b[1][i] = a[1][i],b[2][i] = 1;
		pc('+');pc('\n');
		for(i = 1;i <= n;++i){
			for(j = 1;j <= m;++j) pc(b[i][j] + '0');pc('\n');
		}
		return 0;
	}
	if(m == 2){
		for(i = 1;i <= n;++i) b[i][1] = 1,b[i][2] = a[i][2];
		pc('+');pc('\n');
		for(i = 1;i <= n;++i){
			for(j = 1;j <= m;++j) pc(b[i][j] + '0');pc('\n');
		}
		pc('-');pc('\n');
		for(i = 1;i <= n;++i){
			for(j = 1;j <= m;++j) pc('1');pc('\n');
		}
		for(i = 1;i <= n;++i) b[i][1] = a[i][1],b[i][2] = 1;
		pc('+');pc('\n');
		for(i = 1;i <= n;++i){
			for(j = 1;j <= m;++j) pc(b[i][j] + '0');pc('\n');
		}
		return 0;
	}
	pc('+');pc('\n');
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j){
			if(j == 1) pc('1');
			else if(j == m) pc('0');
			else if(i & 1) pc('1');
			else pc(a[i][j] + '0');
		}
		pc('\n');
	}
	pc('+');pc('\n');
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j){
			if(j == m) pc('1');
			else if(j == 1) pc('0');
			else if(i % 2 == 0) pc('1');
			else pc(a[i][j] + '0');
		}
		pc('\n');
	}
	pc('-');pc('\n');
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j){
			if(j == 1 || j == m) pc(!a[i][j] + '0');
			else pc('1');
		}
		pc('\n');
	}
	return 0;
}
