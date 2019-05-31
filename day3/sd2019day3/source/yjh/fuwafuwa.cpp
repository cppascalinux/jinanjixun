#include <cstdio>
#include <cctype>
#define maxn 505
typedef long long ll;
inline int read() {
	int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return d;
}

ll a, b, m;
int n;
int val[maxn];
int ch[maxn][2], dep[maxn];

int ins(int x, int y) {
	if(!x) return y;
	if(val[x] > val[y]) ch[x][0] = ins(ch[x][0], y);
	else ch[x][1] = ins(ch[x][1], y);
	return x;
}

void dfs(int x) {
	if(ch[x][0]) dep[ch[x][0]] = dep[x]+1, dfs(ch[x][0]);
	if(ch[x][1]) dep[ch[x][1]] = dep[x]+1, dfs(ch[x][1]);
}

void work() {
	a = read(), b = read(), m = read(), n = read();
	for(int i = 1; i <= n; ++i) val[i] = (a+i*b)%m, ch[i][0] = ch[i][1] = 0;
	for(int i = 2; i <= n; ++i) ins(1, i);
	dfs(1);
	printf("%d\n", dep[n]);
}

int main() {
	freopen("fuwafuwa.in", "r", stdin);
	freopen("fuwafuwa.out", "w", stdout);
	for(int q = read(); q; --q) work();
	return 0;
}
