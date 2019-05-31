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
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
const int mo = 998244353;
li n,k,as;
li ff[2][5010];
#define maxn 263000
li tp1[maxn],tp2[maxn],tp3[maxn];
inline li ksm(li q,li w){
    li as = 1;
    while(w){
        if(w & 1) as = as * q % mo;
        q = q * q % mo;
        w >>= 1;
    }
    return as;
}
int wn[2][18][maxn >> 1];
li jc[maxn],nj[maxn],ny[maxn];
int tp[maxn];
inline void init(int x){
    register int i,j,l;
    wn[0][0][0] = wn[1][0][0] = 1;
    for(i = 1,l = 2;i <= x && l <= (maxn >> 1);l <<= 1,++i){
        wn[0][i][0] = wn[1][i][0] = 1;
        wn[1][i][1] = ksm(3,(mo - 1) / (l << 1));
        wn[0][i][1] = ksm(wn[1][i][1],mo - 2);
        for(j = 2;j < l;++j){
            wn[1][i][j] = 1ll * wn[1][i][j - 1] * wn[1][i][1] % mo;
            wn[0][i][j] = 1ll * wn[0][i][j - 1] * wn[0][i][1] % mo;
        }
    }
    jc[0] = 1;for(i = 1;i <= l;++i) jc[i] = jc[i - 1] * i % mo;
    nj[l] = ksm(jc[l],mo - 2);
    for(i = l - 1;i >= 0;--i) nj[i] = nj[i + 1] * (i + 1) % mo;
    ny[1] = 1;for(i = 2;i <= l;++i) ny[i] = (mo - mo / i * ny[mo % i] % mo) % mo;
}
inline int pre(int n){
    register int i,j,l;
    for(j = 0,l = 1;l <= n;l <<= 1,++j);
    for(i = 1;i < l;++i) tp[i] = (tp[i >> 1] >> 1) | ((i & 1) << (j - 1));
    return l;
}
inline void ntt(li *q,int l,bool fg){
    register int i,j,k,g;
    li tmp;
    for(i = 1;i < l;++i) if(i < tp[i]) swap(q[i],q[tp[i]]);
    for(i = 1,g = 0;i < l;i <<= 1,++g){
        for(j = 0;j < l;j += (i << 1)){
            for(k = 0;k < i;++k){
                tmp = q[k + i + j] * wn[fg][g][k] % mo;
                q[k + i + j] = q[k + j] - tmp;q[k + i + j] < 0 ? q[k + i + j] += mo : 0;
                q[k + j] += tmp;q[k + j] >= mo ? q[k + j] -= mo : 0;
            }
        }
    }
    if(!fg){
        li nn = ksm(l,mo - 2);
        for(i = 0;i < l;++i) (q[i] *= nn) %= mo;
    }
}
inline int mul(li *a,li *b,li *as,int n,int m){
    register int i,l;
    l = pre(n + m);
    for(i = 0;i <= n;++i) tp1[i] = a[i];
    for(i = 0;i <= m;++i) tp2[i] = b[i];
    ntt(tp1,l,1);ntt(tp2,l,1);for(i = 0;i < l;++i) as[i] = tp1[i] * tp2[i] % mo;ntt(as,l,0);
    for(i = 0;i < l;++i) tp1[i] = tp2[i] = 0;
    return l;
} 
inline void inv(li *a,li *b,int n){
    if(n == 1){
        b[0] = ksm(a[0],mo - 2);return;
    }
    inv(a,b,n + 1 >> 1);
    register int i,l;
    for(i = 0;i < n;++i) tp1[i] = a[i];
    l = pre(n + n);
    for(i = n + 1 >> 1;i < l;++i) b[i] = 0;
    ntt(tp1,l,1);ntt(b,l,1);for(i = 0;i < l;++i) b[i] = (2 * b[i] - tp1[i] * b[i] % mo * b[i] % mo + mo) % mo;ntt(b,l,0);
    for(i = 0;i < l;++i) tp1[i] = 0;
    for(i = n;i < l;++i) b[i] = 0; 
}
li ea[maxn],eb[maxn],ec[maxn];
int main(){
	srand(time(0));rd();
	file();
	int i,j;
	n = read();k = read();
	if(n <= 5000){
		ff[1][1] = 1;
		for(i = 1;i < n;++i){
			bool p = i & 1;
			for(j = 1;j <= i;++j){
				ff[p][j] %= mo;
				(ff[!p][j] += ff[p][j] * j) %= mo;
				(ff[!p][j + 1] += ff[p][j]) %= mo;
				(ff[!p][j + 2] += ff[p][j] * (i - j)) %= mo;
			}
			for(j = 1;j <= i;++j) ff[p][j] = 0;
		}
		print(ff[n & 1][k]);pc('\n');
		return 0;
	}
	if(n <= 100000 && k == n){
		init(17);
		ea[0] = 1;
		for(i = 1;i <= n;i += 2) ea[i] = ((i - 1 >> 1) & 1) ? mo - nj[i] : nj[i];
		for(i = 0;i <= n;i += 2) eb[i] = ((i >> 1) & 1) ? mo - nj[i] : nj[i];
		inv(eb,ec,n + 1);
		mul(ea,ec,eb,n,n);
		print(eb[n] * jc[n] % mo);
		return 0;
	}
	
	return 0;
}

