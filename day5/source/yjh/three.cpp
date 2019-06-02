#include <cstdio>
#include <cmath>
#include <algorithm>
const double Pi = acos(-1);
const double eps = 1e-7;
inline double fabs(double x) {return x < 0 ? -x : x;}
inline int sgn(double x) {return x > eps ? 1 : x < -eps ? -1 : 0;}

int n;
char s[1000005];
double a[1000005];
int tots;
double x[105], y[105];

inline double getlen(double xa, double ya, double xb, double yb) {
	return sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb));
}

inline double getans(int i, int j, int k) {
	double a = getlen(x[i], y[i], x[j], y[j]);
	double b = getlen(x[j], y[j], x[k], y[k]);
	double c = getlen(x[k], y[k], x[i], y[i]);
	double p = (a+b+c)/2;
	return sqrt(p*(p-a)*(p-b)*(p-c));
}

int main() {
	freopen("three.in", "r", stdin);
	freopen("three.out", "w", stdout);
	scanf("%d%s", &n, s);
	if(n <= 3) {
		printf("0");
		return 0;
	}
	int fl0 = 1;
	for(int i = 0; i < n; ++i)
		if(s[i] == '1') {
			fl0 = 0; break;
		}
	if(fl0) {
		printf("0");
		return 0;
	}
	for(int i = 0; i < n; ++i) x[i] = cos(2*Pi*i/n), y[i] = sin(2*Pi*i/n);
	for(int i = 0; i < n; ++i)
		for(int j = i+1; j < n; ++j)
			for(int k = j+1; k < n; ++k) if(s[i] == '1' || s[j] == '1' || s[k] == '1')
				a[++tots] = getans(i, j, k);
	std::sort(a+1, a+tots+1);
	long long ans = 0;
	for(int i = 1; i <= tots; ++i) {
		int cnt = 1;
		while(i+1 <= tots && !sgn(a[i]-a[i+1])) ++cnt, ++i;
		ans += 1ll*cnt*(cnt-1)/2;
	}
	printf("%lld", ans);
	return 0;
}
