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



int main() {
	freopen("fuwafuwa.in", "r", stdin);
	freopen("fuwafuwa.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while(T --> 0) {
		cerr << T << endl;
		int a, b, m;
		LL n;
		scanf("%d%d%d%lld", &a, &b, &m, &n);
		a %= m;
		b %= m;
		int vis = 0;
		int p = (a + n % m * b) % m;
		int L = 0, R = m;
		int now = a;
		int dep = 0;
		int loop = m / __gcd(m, b);
		LL len = n;
		rep(i, 1, m << 1) {
			now += b;
			-- len;
			if(now >= m) now -= m;
			if(now == p) ++ vis;
			if(now >= L && now < R) {
				++ dep;
				if(now <= p) L = now;
				else R = now;
			}
			if(vis == 2) break;
		}
		printf("%lld\n", dep + len / loop - 1);	
	}
}


