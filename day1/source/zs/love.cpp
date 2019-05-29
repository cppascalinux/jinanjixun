#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cctype>
#include<vector>
#include<queue>
#include<cmath>
#define pii pair<int,LL>
#define mk make_pair
#define LL long long
using namespace std;
const int N = 3005;
int size[N],fa[N];
LL a[N],fa[N];
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
int main(){
	freopen("wait.in","r",stdin);
	freopen("wait.out","w",stdout);
	return 0;	
}
