#include <cstdio>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <bitset>
#include <iostream>
#include <queue>

using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef unsigned long long ULL;
typedef double db;
typedef pair <int, int> pii;
typedef vector <int> vi;

#define Fi first
#define Se second
#define pb push_back
#define mp make_pair

#define rep(i, x, y) for(int i = (x); i <= (y); ++ i)
#define rop(i, x, y) for(int i = (x); i < (y); ++ i)
#define per(i, x, y) for(int i = (x); i >= (y); -- i)
#define por(i, x, y) for(int i = (x); i > (y); -- i)

int A[21][1 << 21];
int B[21][1 << 21];
int n, m;

int dfs(int len, int now, int p) {
	if(p == 0) if(A[len][now] != -1) return A[len][now];
	if(p == 1) if(B[len][now] != -1) return B[len][now];
	rop(i, 0, len - 1) {
		int a1 = (now >> i) & 1;
		int a2 = (now >> (i + 1)) & 1;
		if(a1 != 0 || a2 != 0) {
			int to = now & ((1 << i) - 1);
			to |= (1 << i);
			to |= (((1 << len) - 1) ^ ((1 << (i + 2)) - 1)) >> 1;
			int can = dfs(len - 1, to, p ^ 1);
			if(can == 0) {
				if(p == 0) return A[len][now] = 1;
				if(p == 1) return B[len][now] = 1;
			}
		}
		int to = now & ((1 << i) - 1);
		to |= (((1 << len) - 1) ^ ((1 << (i + 2)) - 1)) >> 1;
		int can = dfs(len - 1, to, p ^ 1);
		if(can == 0) {
			if(p == 0) return A[len][now] = 1;
			if(p == 1) return B[len][now] = 1;
		}
	}
	if(p == 0) return A[len][now] = 0;
	if(p == 1) return B[len][now] = 0;
}

int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	int T; scanf("%d", &T);
	memset(A, 0xff, sizeof A);
	memset(B, 0xff, sizeof B);
	A[1][0] = 1;
	A[1][1] = 0;
	B[1][1] = 1;
	B[1][0] = 0;
	while(T --) {
		scanf("%d%d", &n, &m);
		int now = 0, len = 0, a;
		rep(i, 1, n) scanf("%d", &a), now |= (a & 1) << len, ++ len;
		if(n > 20) { puts("A"); continue; }
		if(len % 2 == 0 && m == 0) puts("A");
		else if(len % 2 == 1 && m == 1) puts("A");
		else if(m == 0 && dfs(len, now, m)) puts("A");
		else if(m == 0 && (dfs(len, now, m) == 0)) puts("B");
		else if(m == 1 && dfs(len, now, m)) puts("B");
		else if(m == 1 && (dfs(len, now, m) == 0)) puts("A");
	}
}
	
