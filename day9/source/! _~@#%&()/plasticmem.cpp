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
	freopen("plasticmem.in","r",stdin);
	freopen("plasticmem.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m;
bool a[1000010];
int main(){
	srand(time(0));rd();
	file();
	int i,j,op,u,v;
	n = read();m = read();
	for(i = 1;i <= n;++i) a[i] = read();
	for(i = 1;i <= m;++i){
		op = read();u = read();v = read();
		if(op == 1){
			for(j = u;j <= v;++j) a[j] = 0;
		}
		else if(op == 2){
			for(j = u;j <= v;++j) a[j] = 1;
		}
		else if(op == 3){
			for(j = u;j <= v;++j) a[j] |= a[j + 1];
		}
		else if(op == 4){
			for(j = v;j >= u;--j) a[j] |= a[j - 1];
		}
		else if(op == 5){
			for(j = u;j <= v;++j) a[j] &= a[j + 1];
		}
		else if(op == 6){
			for(j = v;j >= u;--j) a[j] &= a[j - 1];
		}
		else{
			int as = 0;
			for(j = u;j <= v;++j) as += a[j];
			print(as);pc('\n');
		}
	} 
	return 0;
}

