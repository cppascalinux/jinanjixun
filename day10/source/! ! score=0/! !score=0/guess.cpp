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
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,a[100010];
char c[100010];
int f[1010][1010];

int main(){
	srand(time(0));rd();
	file();
	int i,j,k,l;
	scanf("%s",c + 1);n = strlen(c + 1);
	for(i = 1;i <= n;++i) a[i] = c[i] - '0';
	if(n <= 1000){
		for(i = 2;i <= n + 1;++i){
			for(j = 1;j + i - 1 <= n + 1;++j){
				k = i + j - 1;
				f[j][k] = n * 10;
				for(l = j;l < k;++l) f[j][k] = min(f[j][k],max(f[j][l],f[l + 1][k]) + a[l]);
			}
		}
		print(f[1][n + 1]);pc('\n');
		return 0;
	}
	
	return 0;
}

