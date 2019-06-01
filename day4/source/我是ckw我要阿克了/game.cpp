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
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int t,n,a[100010];
bool xs;

int main(){
	srand(time(0));rd();
	file();
	int i,j,k,l;
	t = read();
	while(t--){
		n = read();xs = read();for(i = 1;i <= n;++i) a[i] = read() & 1;a[i + 1] = 0;
		if(n == 1){
			pc(a[1] ? 'B' : 'A');pc('\n');continue;
		}
		if(!((n & 1) ^ xs)){
			puts("A");continue;
		}
		int sl = 0;
		for(i = 1;i <= n;++i){
			if(a[i] == 1){
				if(a[i + 1] == 1) ++i;
				else --sl;
			}
			else ++sl;
		}
		pc(sl > 0 ? 'A' : 'B');pc('\n');
	}
	return 0;
}
