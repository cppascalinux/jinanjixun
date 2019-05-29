#include<bits/stdc++.h>
using namespace std;
#define li long long
#define gc getchar()
#define pc putchar
inline li read(){
	li x = 0,c = gc;
	while(!isdigit(c)) c = gc;
	while(isdigit(c)) x = x * 10 + c - '0',c = gc;
	return x;
}
inline void print(li x){
	if(x >= 10) print(x / 10);
	pc(x % 10 + '0');
}
inline void file(){
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
}
int n,m,k,w;
const int mo = 998244353;
inline li ksm(li q,li w){
	li as = 1;
	while(w){
		if(w & 1) as = as * q % mo;
		q = q * q % mo;
		w >>= 1;
	}
	return as;
}
int a[65][65][65],c[65][65][65],b[65][65][65];
int main(){
	//srand(time(0));
	file();
	register int i,j,l,g,h,o,p;
	n = read();m = read();k = read();w = read();
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j) for(l = 1;l <= k;++l) a[i][j][l] = 1 - read();
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j) for(l = 1;l <= k;++l) b[i][j][l] = read();
	//return 0;
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j) for(l = 1;l <= k;++l) a[i][j][l] += a[i][j - 1][l];
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j) for(l = 1;l <= k;++l) a[i][j][l] += a[i - 1][j][l];
	//for(i = 1;i <= n;++i){
	//	for(j = 1;j <= m;++j){
	//		for(l = 1;l <= k;++l) cerr<<a[i][j][l]<<" ";cerr<<endl;
	//	} 
	//	cerr<<endl;
	//} 
	li tto = 0;
	int tp;
	for(i = 1;i <= n;++i) for(j = i;j <= n;++j) for(l = 1;l <= m;++l) for(g = l;g <= m;++g){
		h = 0;
		for(o = 1;o <= k + 1;++o){
			if(o == k + 1 || a[j][g][o] - a[i - 1][g][o] - a[j][l - 1][o] + a[i - 1][l - 1][o]){
				tto += (o - h) * (o - h - 1) / 2;
				for(p = h + 1;p < o;++p){ 
					tp = (p - h) * (o - p);
					//cerr<<i<<" "<<j<<" "<<l<<" "<<g<<" "<<p<<":"<<tp<<endl;
					c[j + 1][g + 1][p] += tp;c[j + 1][l][p] -= tp;c[i][g + 1][p] -= tp;c[i][l][p] += tp;
				}
				h = o;
			}
		} 
	}
	//cerr<<c[1][1][1]<<endl;
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j) for(l = 1;l <= k;++l) c[i][j][l] += c[i][j - 1][l];
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j) for(l = 1;l <= k;++l) c[i][j][l] += c[i - 1][j][l];
	li tot = 1ll * n * (n + 1) * m * (m + 1) * k * (k + 1) / 8 % mo,as = 0;tot = ksm(tot,mo - 2);
	//cerr<<tto<<" "<<ksm(tot,mo - 2)<<" "<<tot<<endl;
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j) for(l = 1;l <= k;++l){
		//cerr<<i<<" "<<j<<" "<<l<<":"<<c[i][j][l]<<" "<<(ksm(tto,w) - ksm(tto - c[i][j][l],w) + mo) % mo<<endl;
		(as += b[i][j][l] * (ksm(tto % mo,w) - ksm((tto - c[i][j][l] + mo) % mo,w) + mo)) %= mo;
	} 
	print(as * ksm(tot,w) % mo);
	//cerr<<clock();
	return 0;
}
