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
	freopen("three.in","r",stdin);
	freopen("three.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
li n;
char c[10010];
int sl[35][52][105];
li as;
int main(){
	srand(time(0));rd();
	file();
	int i,j,k,u,v,w;
	n = read();
	scanf("%s",c);
	int tmp = 0;for(i = 0;i < n;++i) tmp += (c[i] == '1');
	if(!tmp){
		pc('0');pc('\n');return 0;
	}
	if(n <= 100){
		for(i = 0;i < n;++i) for(j = i + 1;j < n;++j) for(k = j + 1;k < n;++k) if(c[i] == '1' || c[j] == '1' || c[k] == '1'){
			u = j - i;v = k - j;w = i - k + n;
			if(u > v) swap(u,v);if(v > w) swap(v,w);if(u > v) swap(u,v);
			++sl[u][v][w];
			//cerr<<u<<" "<<v<<" "<<w<<endl;
		}
		for(i = 1;i <= n / 3;++i) for(j = 1;j <= n / 2;++j) for(k = 1;k <= n;++k) as += 1ll * sl[i][j][k] * (sl[i][j][k] - 1) / 2;
		print(as);pc('\n');
		return 0;
	}
	if(n - tmp <= 2){
		if(n % 6 == 0) print((-120 * n + 940 * n * n - 600 * n * n * n + 120 * n * n * n * n) / 720);
		if(n % 6 == 1) print((-120 * n + 600 * n * n - 600 * n * n * n + 120 * n * n * n * n) / 720);
		if(n % 6 == 2) print((-120 * n + 780 * n * n - 600 * n * n * n + 120 * n * n * n * n) / 720);
		if(n % 6 == 3) print((-120 * n + 760 * n * n - 600 * n * n * n + 120 * n * n * n * n) / 720);
		if(n % 6 == 4) print((-120 * n + 780 * n * n - 600 * n * n * n + 120 * n * n * n * n) / 720);
		if(n % 6 == 5) print((-120 * n + 600 * n * n - 600 * n * n * n + 120 * n * n * n * n) / 720);
		return 0;
	}
	return 0;
}

