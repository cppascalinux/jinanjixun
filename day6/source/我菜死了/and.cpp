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

int f[32][1 << 10][1 << 10];
int xxx[32][1 << 10], yyy[32][1 << 10];
int tx[1 << 10][1 << 10], ty[1 << 10][1 << 10];
int val[32][1 << 20];
int b[155];
vi tot[32];
const int mod = 1e9 + 7;
int main() {
	freopen("and.in", "r", stdin);
	freopen("and.out", "w", stdout);
//	double t = clock();
	int n, m; scanf("%d%d", &n, &m);
	rep(i, 1, n) scanf("%d", &b[i]);
//	printf("Read : %.10f\n", clock() - t);
//	t = clock();/
	f[m][0][0] = 1;
	rop(p, 0, 1 << n) {
		rop(t, 0, m) {
			int o = p;
			rep(i, 1, n) {
				xxx[t][p] |= (((o & 1) & ((b[i] >> t) & 1)) << (i - 1));
				yyy[t][p] |= (((o & 1) | ((b[i] >> t) & 1)) << (i - 1));
				o >>= 1;
			}
		}
	}
//	printf("init xxx : %.10f\n", clock() - t);
//	t = clock();
	rop(f1, 0, 1 << (n - 1)) rop(x, 0, (1 << n)) {
		int flag = 1;
		int t1 = f1;
		rop(i, 1, n) {
			if(!((f1 >> (i - 1)) & 1)) {	
				if(((x >> (i - 1)) & 1) > ((x >> i) & 1)) { flag = 0; break; };
				if(((x >> (i - 1)) & 1) < ((x >> i) & 1)) t1 ^= (1 << (i - 1));
			}
		}
		if(flag == 0) tx[f1][x] = -1;
		else tx[f1][x] = t1;
	}
	rop(f1, 0, 1 << (n - 1)) rop(x, 0, (1 << n)) {
		int flag = 1;
		int t1 = f1;
		rop(i, 1, n) {
			if(!((f1 >> (i - 1)) & 1)) {	
				if(((x >> (i - 1)) & 1) < ((x >> i) & 1)) { flag = 0; break; };
				if(((x >> (i - 1)) & 1) > ((x >> i) & 1)) t1 ^= (1 << (i - 1));
			}
		}
		if(flag == 0) ty[f1][x] = -1;
		else ty[f1][x] = t1;
	}
//	printf("init txty : %.10f\n", clock() - t);
//	t = clock();

	rop(t, 0, m) {
		rop(p, 0, 1 << n) {
			int x = xxx[t][p];
			int y = yyy[t][p];
			int mer = x << 10 | y;
			++ val[t][mer];
			if(val[t][mer] == 1) tot[t].pb(mer);
		}
	}
	
	per(t, m - 1, 0) {
		rop(f1, 0, 1 << (n - 1)) {
			rop(f2, 0, 1 << (n - 1)) {
				if(f[t + 1][f1][f2] == 0) continue;
				int PP = f[t + 1][f1][f2];
				rop(p, 0, (int)tot[t].size()) {
					int now = tot[t][p];
					int x = now >> 10;
					int y = now & ((1 << 10) - 1);
					int t1 = tx[f1][x];
					int t2 = ty[f2][y];
					if(t1 == -1 || t2 == -1) continue;
					f[t][t1][t2] = (1ll * PP * val[t][now] + f[t][t1][t2]) % mod;
				}
			}
		}
	}
	
//	printf("dp : %.10f\n", clock() - t);
//	t = clock();
	long long ans = 0;
	rop(f1, 0, 1 << (n - 1)) rop(f2, 0, 1 << (n - 1)) ans = ans + f[0][f1][f2];
	printf("%lld\n", ans % mod);
	
//	printf("write : %.10f\n", clock() - t);
//	t = clock();
	
	
}
				
	

