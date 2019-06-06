#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<vector>
#include<cmath>
#include<cstring>
#define LL long long
using namespace std;
const int N = 1e6 + 3;
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
namespace zs{
	int a[N],b[N];
	inline void work(){
		for(int i = 1;i <= n;++i) b[i] = a[i] = read();
		for(int i = 1;i <= m;++i){
			int opt = read(),l = read(),r = read(),ans = 0;
			if(opt == 1)
				for(int i = l;i <= r;++i) b[i] = 0;
			if(opt == 2)
				for(int i = l;i <= r;++i) b[i] = 1;	
			if(opt == 3)
				for(int i = l;i < r;++i) b[i] = a[i] | a[i + 1];	
			if(opt == 4)
				for(int i = l + 1;i <= r;++i) b[i] = a[i] | a[i - 1];
			if(opt == 5) 
				for(int i = l;i < r;++i) b[i] = a[i] & a[i + 1];
			if(opt == 6)
				for(int i = l + 1;i <= r;++i) b[i] = a[i] & a[i - 1];
			if(opt == 7) {
				for(int i = l;i <= r;++i) ans += b[i];
				printf("%d\n",ans);
			}
			for(int i = 1;i <= n;++i) a[i] = b[i];
		}
	}
}
int main(){
	freopen("plasticmem.in","r",stdin);
	freopen("plasticmem.out","w",stdout);
	n = read(),m = read();
	if(n <= 150000) zs::work();
	return 0;	
}
