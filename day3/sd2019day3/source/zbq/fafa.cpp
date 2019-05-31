
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ll long long
#define M 100010
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
const int mod = 998244353;
void add(int &x, int y) {
	x += y;
	x -= x >= mod ? mod : 0;
}
int mul(int a, int b) {
	return 1ll * a * b % mod;
}
int poww(int a, int b) {
	int ans = 1, tmp = a;
	for(; b; b >>= 1, tmp = mul(tmp, tmp)) if(b & 1) ans = mul(ans, tmp);
	return ans;
}
int n, k;
int vis[11], sta[11], ans;

void check() {
	int cnt = 0, ver = 0;
	for(int i = 1; i <= n; i++) {
		if(cnt & 1) {
			if(sta[i] < ver) {
				cnt++;
			}
			ver = sta[i];
		} else {
			if(sta[i] > ver) {
				cnt++;
			}
			ver = sta[i];
		}
	}
	if(cnt == k) ans++;
}

void dfs(int now) {
	if(now == n + 1) {
		check();
		return;
	}
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			sta[now] = i;
			vis[i] = true;
			dfs(now + 1);
			vis[i] = false;
		}
	}
}

void work1() {
	dfs(1);
	cout << ans << "\n";
}
void work2() {

	
}


int main() {
	freopen("fafa.in", "r", stdin); freopen("fafa.out", "w", stdout);
	n = read(), k = read();
	if(n <= 10) {
		work1();
	} else {
		work2();
	}
	return 0;
}



