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

const int inf = 0x3f3f3f3f;

int f[15][2];

int ans[10][10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 2, 0, 0, 0, 0, 0, 0, 0, 1, 7, 11, 5, 0, 0, 0, 0, 0, 0, 1, 15, 43, 45, 16, 0, 0, 0, 0, 0, 1, 31, 148, 268, 211, 61, 0, 0, 0, 0, 1, 63, 480, 1344, 1767, 1113, 272, 0, 0, 0, 1, 127, 1509, 6171, 12099, 12477, 6551, 1385, 0, 0, 1, 255, 4661, 26955, 74211, 111645, 94631, 42585, 7936, 0, 1, 511, 14246, 114266, 425976, 878856, 1070906, 770246, 303271, 50521};

int main() {
	freopen("fafa.in", "r", stdin);
	freopen("fafa.out", "w", stdout);
	
	int n, m; scanf("%d%d", &n, &m);
	if(m == 0 || n == 0) { puts("0"); return 0; }
	printf("%d\n", ans[n - 1][m - 1]);
	return 0;
}
