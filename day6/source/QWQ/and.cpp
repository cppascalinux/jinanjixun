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
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m,a[12],mx,mm;
const int mo = 1000000007;
li f[32][520],an1,an2;
int cnt;
inline int chk(int y,int z){
	//for(int i = 1;i <= n;++i) if(z & (1 << i - 1) && !(a[i] & (1 << x - 1))) return -1;
	for(int i = 1;i < n;++i) if(!(y & (1 << i - 1))){
		if((z & (1 << i - 1)) && !(z & (1 << i))) return -1;
		if(!(z & (1 << i - 1)) && (z & (1 << i))) y += 1 << i - 1;
	}
	return y;
}
int zy[520][1030];
int main(){
	srand(time(0));rd();
	file();
	int i,j,k,l;
	n = read();m = read();mx = 1 << m;mm = 1 << n - 1;for(i = 1;i <= n;++i) a[i] = read();
	f[m][0] = 1;
	for(i = 0;i < mm;++i) for(j = 0;j < mm * 2;++j) zy[i][j] = chk(i,j);
	for(i = m;i;--i){
		int tp = 0;
		for(j = 1;j <= n;++j) if(a[j] & (1 << i - 1)) tp += 1 << j - 1;
		for(j = 0;j < mm;++j) if(f[i][j]){
			for(k = tp;k;k = (k - 1) & tp){
				int nxt = zy[j][k];
				if(nxt == -1) continue;
				(f[i - 1][nxt] += f[i][j]) %= mo;
			}
			(f[i - 1][j] += f[i][j]) %= mo;
		} 
	} 
	for(i = 0;i < mm;++i) an1 += f[0][i];an1 %= mo;
	for(i = 1;i <= n;++i) a[i] = mx - 1 - a[i];memset(f,0,sizeof(f));
	f[m][0] = 1;
	for(i = 0;i < mm;++i) for(j = 0;j < mm * 2;++j) zy[i][j] = chk(i,j);
	for(i = m;i;--i){
		int tp = 0;
		for(j = 1;j <= n;++j) if(a[j] & (1 << i - 1)) tp += 1 << j - 1;
		for(j = 0;j < mm;++j) if(f[i][j]){
			for(k = tp;k;k = (k - 1) & tp){
				int nxt = zy[j][k];
				if(nxt == -1) continue;
				(f[i - 1][nxt] += f[i][j]) %= mo;
			}
			(f[i - 1][j] += f[i][j]) %= mo;
		} 
	} 
	for(i = 0;i < mm;++i) an2 += f[0][i];an2 %= mo;
	print(an1 * an2 % mo);pc('\n');
	return 0;
}
