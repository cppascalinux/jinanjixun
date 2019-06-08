#include <cstdio>
#include <cctype>
#include <algorithm>
#define maxn 100005
#define M 1000000007
typedef long long ll;
inline int read() {
	int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return d;
}

inline int ksm(int x, int y) {
	int ans = 1;
	for(; y; y >>= 1) {
		if(y&1) ans = 1ll*ans*x%M;
		x = 1ll*x*x%M;
	}
	return ans;
}

int n;
int xa[maxn], ya[maxn], xb[maxn], yb[maxn];
int a[5][5];
int cnt, sum;

int g[5] = {1, 2, 3};

inline int getsi() {
	int cnt = 0;
	for(int i = 0; i < n; ++i)
		for(int j = i+1; j < n; ++j)
			if(g[i] > g[j]) ++cnt;
	return cnt;
}

inline int getval() {
	int sum = 1;
	for(int i = 0; i < n; ++i)
		sum = 1ll*sum*a[i+1][g[i]]%M;
	return sum;
}

inline int getdet() {
	int now = 0;
	do {
		int sg = (getsi()&1) ? -1 : 1;
		now = (now+1ll*sg*getval()%M+M)%M;
	}while(std::next_permutation(g, g+n));
	return now;
}

void dfs(int stp) {
	if(stp > n) {
		++cnt;
		sum = (sum+getdet())%M;
		return;
	}
	for(int i = xa[stp]; i <= xb[stp]; ++i)
		for(int j = ya[stp]; j <= yb[stp]; ++j) {
			++a[i][j];
			dfs(stp+1);
			--a[i][j];
		}
}

namespace solve2 {
	int per[maxn];
	int b[maxn], visb[maxn];
	
	inline bool cmp(const int& x, const int& y) {
		return xa[x] < xa[y];
	}
	
	inline bool cmpy(const int& x, const int& y) {
		return ya[x] < ya[y];
	}
	
	ll c[maxn];
	
	inline void add(int x) {for(; x <= n; x += x&-x) ++c[x];}
	inline ll query(int x) {ll s = 0; for(; x; x -= x&-x) s += c[x]; return s;}
	
	void work() {
		for(int i = 1; i <= n; ++i) per[i] = i;
		std::sort(per+1, per+n+1, cmpy);
		for(int i = 1; i <= n; ++i)
			if(ya[per[i]] != i) {
				puts("0");
				return;
			}
		std::sort(per+1, per+n+1, cmp);
		for(int i = 1; i <= n; ++i)
			if(xa[per[i]] != i) {
				puts("0");
				return;
			}
		ll sum = 0;
		for(int i = 1; i <= n; ++i) b[i] = ya[per[i]], c[i] = 0;
		for(int i = 1; i <= n; ++i) {
			sum += i-1-query(b[i]);
			add(b[i]);
		}
		printf("%d\n", (sum&1) ? M-1 : 1);
	}
}

void work() {
	n = read();
	for(int i = 1; i <= n; ++i)
		xa[i] = read(), xb[i] = read(), ya[i] = read(), yb[i] = read();
	if(n <= 3) {
		cnt = sum = 0;
		dfs(1);
		printf("%lld\n", 1ll*sum*ksm(cnt, M-2)%M);
		return;
	}
	solve2::work();
}

int main() {
	freopen("determinant.in", "r", stdin);
	freopen("determinant.out", "w", stdout);
	for(int q = read(); q; --q) work();
	return 0;
}
