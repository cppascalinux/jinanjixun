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
const LL INF = 0x3f3f3f3f3f3f3f3f;
const db eps = 1e-8;

const int N = 550;

int n, m;
char s[N][N];

namespace subtask3 {
	
	int main() {
		int ans = 0;
		char *a = s[1];
		a[m + 1] = '0';
		rep(i, 1, m) if(a[i] == '1' && a[i + 1] == '0') ++ ans;
		printf("%d\n", ans);
		int l = 1;
		rep(i, 1, m) {
			if(a[i] == '0') ++ l;
			if(a[i] == '1' && a[i + 1] == '0') {
				puts("+");
				rep(j, 1, l - 1) putchar('0');
				rep(j, l, i) putchar('1');
				rep(j, i + 1, m) putchar('0');
				l = i + 1;
				putchar('\n');
			}
		}
		return 0;
	}
	
}

namespace subtask1 {
	
	int main() {
		return 0;
	}
	
}

int main() {
	freopen("bitbit.in", "r", stdin);
	freopen("bitbit.out", "w", stdout);
	scanf("%d%d", &n, &m);
	rep(i, 1, n) scanf("%s", s[i] + 1);
	if(n == 1) subtask3::main();
	if(n <= 3 && m <= 3) subtask1::main();
	
}
	

