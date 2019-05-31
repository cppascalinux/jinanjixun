#include<cstring>
#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#include<cstdlib>
#include<cctype>
#include<algorithm>
#define LL long long
#define pii pair<int,int>
#define mk make_pair
using namespace std;
const int N = 5000005;
LL n,m,a,b;
struct tree{
	int dep;
	LL val;
	int lc,rc;	
}t[N];
int cnt = 0;
int root;
inline LL read(){
    LL v = 0,c = 1;char ch = getchar();
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
inline int ins(int &x,int f,LL v){
	if(!x) {
		x = ++cnt;
		t[x].val = v;
		t[x].dep = t[f].dep + 1;
		return x;
	}	
	if(t[x].val > v) return ins(t[x].lc,x,v);
	else return ins(t[x].rc,x,v);
}
int main(){
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
	int T = read();
	while(T--){
		memset(t,0,sizeof(t));cnt = 0,root = 0;
		a = read(),b = read(),m = read(),n = read();
		for(int i = 1;i <= n;++i){
			LL w = (a + i * b) % m;	
			int x = ins(root,0,w);
			if(i == n) printf("%d\n",t[x].dep - 1);
		}
	}
	return 0;	
}
