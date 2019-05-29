#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cctype>
#include<vector>
#include<queue>
#include<cmath>
#define pii pair<int,int>
#define mk make_pair
#define LL long long
using namespace std;
int n,m,tot,cnt;
const int N = 3e4 + 3;
int b[N << 1];
struct line{
	int li;
	int ri;	
	int type;
}a[N];
line c[N];
int check[N];
int book[N];
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
inline void work1(){
	int maxri = 0;
	sort(b + 1,b + tot + 1);
	b[0] = unique(b + 1,b + tot + 1) - b - 1;
	for(int i = 1;i <= m;++i){
		a[i].li = lower_bound(b + 1,b + b[0] + 1,a[i].li) - b;
		a[i].ri = lower_bound(b + 1,b + b[0] + 1,a[i].ri + 1) - b;
		maxri = max(maxri,a[i].ri);
	}
//	cout << maxri << endl;
	for(int i = 0;i < (1 << m);++i){
		for(int j = 1;j <= maxri;++j) book[j] = 0;
		for(int j = 0;j < m;++j){
			if(a[j + 1].type == 1) book[a[j + 1].li]++,book[a[j + 1].ri]--;
			if(a[j + 1].type == 0) book[a[j + 1].li]--,book[a[j + 1].ri]++;
			if(a[j + 1].type == -1){
				if(i & (1 << j)) book[a[j + 1].li]++,book[a[j + 1].ri]--;
				else book[a[j + 1].li]--,book[a[j + 1].ri]++;
			}
		}
		bool flag = 1;
		for(int j = 1;j <= maxri;++j) {
			book[j] += book[j - 1];
			if(abs(book[j]) > 1) {flag = 0;break;} 
		}
	//	for(int j = 1;j <= maxri;++j) cout << book[j] << " ";cout << endl;
		if(flag){
			for(int j = 0;j < m;++j){
				if(a[j + 1].type != -1) printf("%d ",a[j + 1].type);
				else printf("%d ",(i >> j) & 1);
			}
			return ;
		}
	}
	puts("-1");
}
int main(){
	freopen("wait.in","r",stdin);
	freopen("wait.out","w",stdout);
	tot = 0,cnt = 0;
	m = read(),n = read();
	for(int i = 1;i <= m;++i){
		b[++tot] = a[i].li = read();
		b[++tot] = a[i].ri = read();
		b[tot]++;
		a[i].type = read();
	}
	if(m <= 20) work1();
	return 0;	
}
