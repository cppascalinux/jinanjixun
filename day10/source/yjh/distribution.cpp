#include <cstdio>
#include <cstdlib>
#include <ctime>

int main() {
	freopen("distribution.in", "r", stdin);
	freopen("distribution.out", "w", stdout);
	int q; scanf("%d", &q);
	srand(time(0));
	for(int i = 1; i <= q; ++i)
		printf("%d\n", rand()%100+1);
	return 0;
}
