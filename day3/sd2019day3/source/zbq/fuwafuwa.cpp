
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ll long long
#define M 1010
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
struct T {
	int ch[1010][2], deep[1010], cnt, ver[1010];
	void clear() {
		memset(ch, 0, sizeof(ch));
		cnt = 0;
	}

	void insert(int x) {
		if(cnt == 0) {
			cnt++;
			deep[cnt] = 0;
			ver[1] = x;
			return;
		}
		int now = 1, f = 0;
		while(1) {
			if(now == 0) {
				cnt++;
				ch[f][ver[f] <= x] = cnt;
				ver[cnt] = x;
				deep[cnt] = deep[f] + 1;
				return;
			}
			f = now;
			now = ch[now][ver[now] <= x];
		}
	}
} t;
void work1(int a, int b, int m, int n) {
	t.clear();
	for(int i = 1; i <= n; i++) {
		t.insert((1ll * i * b + a) % m);
	}
	cout << t.deep[t.cnt]<< "\n";
}

void work2(int a, int b, int m, int n)
{
	
}


int main() {
//	freopen("2.in", "r", stdin);
//	freopen("2.out", "w", stdout);
	freopen("fuwafuwa.in", "r", stdin); freopen("fuwafuwa.out", "w", stdout);
	int T = read();
	while(T--) {
		int a = read(), b = read(), m = read(), n = read();
		if(n <= 500) work1(a, b, m, n);
		else work2(a, b, m, n);
	}
	return 0;
}


/*
1
1 0 2 10

*/
