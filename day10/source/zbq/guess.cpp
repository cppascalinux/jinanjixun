
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
char s[M];
int n, f[M][M], v[M];
int main() {
	freopen("guess.in", "r", stdin); freopen("guess.out", "w", stdout);
	scanf("%s", s + 1);
	n = strlen(s + 1) + 1;
	for(int i = 1; i <= n; i++) v[i] = s[i] - '0';
	memset(f, 0x3e, sizeof(f));
	for(int i = 1; i <= n; i++) f[i][i] = 0;
	for(int len = 2; len <= n; len++) {
		for(int i = 1; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			for(int k = i; k < j; k++) {
				f[i][j] = min(f[i][j], max(f[i][k], f[k + 1][j]) + v[k]);
			}
		}
	}
	cout << f[1][n] << "\n";

	return 0;
}


