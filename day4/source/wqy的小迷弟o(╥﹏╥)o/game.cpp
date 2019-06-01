#include<cstdio>
#include<cstring>
#include<iostream>
#include<cctype>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#define LL long long
#define pii pair<int,int>
#define mk make_pair
using namespace std;
const int N = 20;
int a[N];
int f[1 << N][21];
int sta[N];
int n,m;
inline int read(){
	int v = 0,c = 1;char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') c = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		v = v * 10 + ch - 48;
		ch = getchar();	
	}
	return v * c;
}
inline int count(int x){
	int res = 0;
	while(x){
		if(x & 1) res++;
		x >>= 1;
	}
	return res;
}
//1:奇数 0：偶数 
inline int dfs(int s,int who,int len){//0:小A 1：小B 
	if(f[s][len] != -1) return f[s][len];
	if(len == 1){
	//	cout << s << " "<< who <<  endl;
		if(!s) return 0; 
		return 1;
	} 
	if(who == 1) f[s][len] = 0;
	else f[s][len] = 1;
	for(int i = 0;i < len - 1;++i){
		int x = (s >> i) & 1;
		int y = (s >> (i + 1)) & 1;
		int xx = (i + 2 < len) ? (s >> (i + 2) << (i + 1)) : 0;
		int yy = (i - 1 >= 0) ? (s & sta[i - 1]) : 0;
		if(who == 1) {
			f[s][len] |= (dfs((xx | yy) | ((x & y) << i),who ^ 1,len - 1) | dfs(xx | yy | ((x ^ y) << i),who ^ 1,len - 1));
			if(f[s][len]) return 1;
		}
		else {
			f[s][len] &= (dfs((xx | yy) | ((x & y) << i),who ^ 1,len - 1) & dfs(xx | yy | ((x ^ y) << i),who ^ 1,len - 1));
			if(!f[s][len]) return 0;
		}
	}
	return f[s][len];
}
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	sta[0] = 1;
	for(int i = 1;i < 20;++i)
	sta[i] = sta[i - 1] | (1 << i);
	int T = read();
	while(T--){
		int w = 0;
		n = read(),m = read();
		if(n <= 20){
			for(int i = 0;i < n;++i){
				a[i] = read();
				if(a[i] & 1) w |= (1 << i);
			}
			memset(f,-1,sizeof(f));
			printf("%c\n",dfs(w,m,n) ? 'B' : 'A');	
		}
		else printf("A\n");
	}
	return 0;	
}
