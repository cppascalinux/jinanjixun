
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#include<map>
#define ll long long
#define M 5000100
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
int n, k;
const int mod = 1000000007;
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
map<pair<int, int>, int> note[11];
char s[M];
map<pair<int, int>, int>::iterator it;

int f[11][1026][1026];
int sum[1026];
int main() {
	freopen("end.in", "r", stdin); freopen("end.out", "w", stdout);
//	freopen("sample2.in", "r", stdin);
	//freopen("sample.out", "w", stdout);
	n = read(), k = read();
	scanf("%s", s + 1);
	int len = strlen(s + 1), up = 0;
	for(int i = 1; i <= len; i++) {
		up <<= 1;
		up += (s[i] == '1');
	}
	if(n <= -3) {
		note[0][mmp(0, up)] = 1;
		for(int i = 0; i < n; i++) {
			for(it = note[i].begin(); it != note[i].end(); it++) {
				int a = it->first.first, b = it->first.second, v = it->second;
			//	cerr << a << " " << b << "\n";
				for(int c = 0; c < b; c++) {
					add(note[i + 1][mmp(a ^ c, c)], v);
				}
			}
		}
		int ans = 0;
		for(it = note[n].begin(); it != note[n].end(); it++) {
			if(it->first.first == 0) add(ans, it->second);
		}
		cout << ans << "\n";
	} else {
		f[0][0][up] = 1;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j <= 1023; j++) {
				memset(sum, 0, sizeof(sum));
				for(int k = 1023; k >= 0; k--) {
					sum[k] = sum[k + 1];
					add(sum[k], f[i][j][k]);
				}
				for(int c = 0; c < up; c++) {
					add(f[i + 1][j ^ c][c], sum[c + 1]);
				}
			}
		}
		int ans = 0;
		for(int j = 0; j <= 1023; j++) {
			add(ans, f[n][0][j]);
		}
		cout << ans << "\n";
	}
	return 0;
}


