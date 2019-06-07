
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ll long long
#define M  10010
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
int n;

double ab(double x) {
	return x > 0 ? x : -x;
}
int ab(int x) {
	return x > 0 ? x : -x;
}
double a[M], p, tot;
long double c[111][111];
long double f[111][111];
double check(int n) {
	double ans = 0, pp = p * n;
	if(n <= 100) {
		for(int i = 0; i <= n; i++) {
			ans += c[n][i] * ab(pp - i) * f[n][i];
		}
		ans /= 1 << n;
//		for(int i = 0; i <= n; i++) {
//			for(int j = -5; j <= 5; j++) {
//				ans += 1.0 / 11  * c[n][i] *  ab(1.0 * i + 0.1 * j - pp) * f[n][i];
//			}
//		}
//		ans /= 1 << n;
		for(int i = -5; i <= 5; i++) {
			ans -= 0.1 * ab(i) / 11;
		}
		return ab(ans );
	} else {

	}
}


void work() {
	n = read();
	for(int i = 1; i <= n; i++) scanf("%lf", &a[i]), tot += ab(a[i]);
	tot /= n;
	double ans = pow(2, 100);
	int pl = 0;
	for(int i = 1; i <= 100; i++) {
		double q = sqrt(p * (1 - p) * i);
		//	cerr <<check(i) << " " << q << "\n";
		double zz = check(i) / q;
		//	cerr << zz << "!\n";
		if(ab(tot - zz) < ans) ans = ab(tot - zz), pl = i;
	}
	tot = 0;
	if(pl == 1 || pl == 100) pl = 50;
	cout << pl << "\n";
}

void dp() {
	f[0][0] = 1;
	for(int i = 0; i < 100; i++) {
		for(int j = 0; j <= i; j++) {
			f[i + 1][j + 1] += f[i][j] * p;
			f[i + 1][j] += f[i][j] * (1 - p);
		}
	}
}

int main() {
	freopen("distribution.in", "r", stdin); freopen("distribution.out", "w", stdout);
	c[0][0] = 1;
	for(int i = 1; i <= 100; i++) {
		c[i][0] = 1;
		for(int j = 1; j <= 100; j++) {
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
		}
	}
	int T = read();
	scanf("%lf", &p);
	dp();
	while(T--) {
		work();
	}
	return 0;
}


