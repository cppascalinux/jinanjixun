#include<bits/stdc++.h>
using namespace std;
#define li long long
//char buf[100010],*buff = buf + 100000;
//#define gc (((buff == buf + 100000) ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
#define gc getchar()
//char bfu[50000010],*bfuu = bfu;
//#define pc(x) (*(bfuu++) = (x))
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
	freopen("end.in","r",stdin);
	freopen("end.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m,k,nw;
char s[10010];
const int mo = 1000000007;
struct mtx{
	li a[8][8];
	mtx(){memset(a,0,sizeof(a));}
	inline void init(){
		memset(a,0,sizeof(a));
		for(int i = 0;i <= nw;++i) a[i][i] = 1;
	}
}zy[8][2],tp,tp2,zz[8],an[8];
int zh[8][8];
li jc[8],nj[8];
li nn,aa[8],as;
inline mtx operator * (mtx x,mtx y){
	mtx as;
	register int i,j,k;
	for(i = 0;i <= nw;++i) for(k = 0;k <= nw;++k) for(j = 0;j <= nw;++j) as.a[i][j] += x.a[i][k] * y.a[k][j];
	for(i = 0;i <= nw;++i) for(j = 0;j <= nw;++j) as.a[i][j] %= mo;
	return as;
}
inline li ksm(li q,li w){
	li as = 1;
	while(w){
		if(w & 1) as = as * q % mo;
		q = q * q % mo;
		w >>= 1;
	}
	return as;
}
int dx[10];

void dfs(int q,int w,int e){
	if(w < 0) return;
	if(w == 0){
		dx[q] = 0;
		int p1 = 0,p2 = 0,lst = 1;
		li xs = 1;
		for(int i = 1;i < q;++i){
			(xs *= jc[dx[i] - 1] * nj[dx[i]]) %= mo;
			if(dx[i] != dx[i + 1]) (xs *= nj[i - lst + 1]) %= mo,lst = i + 1;
			if(dx[i] & 1) ++p1;else ++p2;
			//cerr<<i<<":"<<xs * jc[n] % mo<<" "<<lst<<endl;
		}
		//for(int i = 1;i < q;++i) cerr<<dx[i]<<" ";cerr<<":"<<p1<<" "<<p2<<" "<<xs * jc[n] % mo<<endl;
		(xs *= aa[p1] * ksm(nn,p2) % mo) %= mo;
		if(n - q & 1) (as += xs) %= mo;
		else (as += mo - xs) %= mo;
		return;
	}
	for(int i = 1;i <= e;++i){
		dx[q] = i;
		dfs(q + 1,w - i,i);
	}
}
int main(){
	srand(time(0));rd();
	file();
	int i,j,l;
	n = read();k = read();scanf("%s",s + 1);m = strlen(s + 1);
	zh[0][0] = 1;
	for(i = 1;i <= n;++i){
		zh[i][0] = 1;
		for(j = 1;j <= i;++j) zh[i][j] = zh[i - 1][j] + zh[i - 1][j - 1];
	}
	jc[0] = 1;for(i = 1;i <= n;++i) jc[i] = jc[i - 1] * i % mo;
	nj[n] = ksm(jc[n],mo - 2);
	for(i = n - 1;i >= 0;--i) nj[i] = nj[i + 1] * (i + 1) % mo;
	li q0 = 1,q1 = 0,q2 = 0,q3 = 1;
	for(i = 1;i <= m;++i){
		if(s[i] == '0') (q1 += q1) %= mo,(q3 += q3) %= mo;
		else (q1 += q0 + q1) %= mo,(q3 += q2 + q3) %= mo;
	}
	tp.a[0][0] = q0;tp.a[1][0] = q1;tp.a[0][1] = q2;tp.a[1][1] = q3;
	nw = 1;i = k;tp2.init();
	while(i){
		if(i & 1) tp2 = tp2 * tp;
		tp = tp * tp;
		i >>= 1;
	}
	nn = tp2.a[1][0];
	//cerr<<nn<<endl;
	aa[0] = 1;
	for(nw = 1;nw <= n;++nw){
		for(i = 0;i <= nw;++i){
			for(j = 0;j <= i;++j){
				for(l = 0;l <= nw;l += 2){
					if(nw - l >= i && j == i) (zy[nw][0].a[j][i] += zh[nw - i][l]) %= mo;
					if(nw - l >= i - j && l >= j) (zy[nw][1].a[j][i] += zh[i][j] * zh[nw - i][l - j]) %= mo;
				}
			}
		}
		/*for(i = 0;i <= nw;++i){
			for(j = 0;j <= nw;++j) cerr<<zy[nw][0].a[i][j]<<" ";cerr<<endl;
		}
		for(i = 0;i <= nw;++i){
			for(j = 0;j <= nw;++j) cerr<<zy[nw][1].a[i][j]<<" ";cerr<<endl;
		}*/
		zz[nw].init();
		for(i = 1;i <= m;++i){
			if(s[i] == '0') zz[nw] = zy[nw][0] * zz[nw];
			else zz[nw] = zy[nw][1] * zz[nw];
		} 
		j = k;
		an[nw].init();
		while(j){
			if(j & 1) an[nw] = an[nw] * zz[nw];
			zz[nw] = zz[nw] * zz[nw];
			j >>= 1;
		}
		aa[nw] = an[nw].a[0][nw];
		//cerr<<nw<<":"<<aa[nw]<<endl<<endl;
	}
	dfs(1,n,n);
	print(as);pc('\n');
	//fwrite(bfu,1,bfuu - bfu,stdout);
	return 0;
}

