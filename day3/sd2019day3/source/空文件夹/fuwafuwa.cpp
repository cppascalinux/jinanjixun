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
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int t;
li n,m,a,b,val[510];
int dep[510],rt,ls[510],rs[510];
inline int ins(int x,int y){
	if(!x) return y;
	if(val[x] > val[y]) ls[x] = ins(ls[x],y),dep[ls[x]] = dep[x] + 1;
	else rs[x] = ins(rs[x],y),dep[rs[x]] = dep[x] + 1;
	return x;
}
int dd[2000010],dy[2000010];
set<int> ss;
int main(){
	srand(time(0));rd();
	file();
	int i,j;
	t = read();
	while(t--){
		a = read();b = read();m = read();n = read();
		if(n == 1){
			pc('0');pc('\n');continue;
		}
		if(n <= 500){
			rt = 0;
			for(i = 1;i <= n;++i){
				val[i] = (a + i * b) % m;ls[i] = rs[i] = dep[i] = 0;
				rt = ins(rt,i);
			}
			print(dep[n]);pc('\n');
			continue;
		}
		if(m <= 1000000){
			int fg = 0;
			for(i = 0;i <= m + m;++i) dy[i] = dd[i] = 0;ss.clear();
			for(i = 1;i <= n;++i){
				int x = (a + i * b) % m * 2 + fg;
				if(dy[x]){
					if(fg) break;
					fg = 1;++x;
				}
				dy[x] = i;
				if(i == 1){
					ss.insert(x);
					continue;
				} 
				else{
					set<int>::iterator it = ss.lower_bound(x);
					if(it == ss.end()) dd[i] = dd[dy[*(--it)]] + 1;
					else if(it == ss.begin()){
						dd[i] = dd[dy[*it]] + 1;
					} 
					else{
						int u = *it,v = *(--it);
						dd[i] = max(dd[dy[u]],dd[dy[v]]) + 1;
					}
					ss.insert(x);
				}
				if(i == n){
					print(dd[n]);pc('\n');goto qwq;
				}
			}
			--i;i >>= 1;
			li p1 = n / i,p2 = n % i;
			print(p1 - 1 + dd[p2 + i]);pc('\n');continue;
		}
		qwq:;
	}
	return 0;
}

