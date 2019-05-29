#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#define maxn 300005
inline int read() {
	int f=1,d=0;char ch=getchar();while(!isdigit(ch)){if(ch=='-'){f=0;}ch=getchar();}
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return f?d:-d;
}

int m, n;
int lt[maxn], rt[maxn], co[maxn];
int fd[maxn], totf;
int ind[maxn], tots;
#define val(x) (std::lower_bound(ind+1, ind+tots+1, x)-ind)

int fin[maxn];

bool check() {
	for(int i = 1; i <= n; ++i) fin[i] = 0;
	for(int p = 1; p <= m; ++p) {
		if(co[p]) for(int i = lt[p]; i <= rt[p]; ++i) ++fin[i];
		else for(int i = lt[p]; i <= rt[p]; ++i) --fin[i];
	}
	for(int i = 1; i <= n; ++i)
		if(fin[i] > 1 || fin[i] < -1) return 0;
	return 1;
}

void dfs(int stp) {
	if(stp > m) {
		if(check()) {
			for(int i = 1; i <= m; ++i)
				printf("%d ", co[i]);
			exit(0);
		}
		return;
	}
	if(co[stp] != -1) return dfs(stp+1);
	co[stp] = 0, dfs(stp+1), co[stp] = 1, dfs(stp+1);
}

int main() {
	freopen("wait.in", "r", stdin);
	freopen("wait.out", "w", stdout);
	m = read(), n = read();
	for(int i = 1; i <= m; ++i) {
		lt[i] = read(), rt[i] = read(), co[i] = read();
		fd[++totf] = lt[i], fd[++totf] = rt[i];
	}
	std::sort(fd+1, fd+totf+1); totf = std::unique(fd+1, fd+totf+1)-fd-1;
	ind[tots = 1] = fd[1];
	for(int i = 2; i <= totf; ++i) {
		if(fd[i] > ind[tots]+1) ++tots, ind[tots] = ind[tots-1];
		ind[++tots] = fd[i];
	}
	for(int i = 1; i <= m; ++i)
		lt[i] = val(lt[i]), rt[i] = val(rt[i]);
	n = tots;
	dfs(1);
	printf("-1");
	return 0;
}
