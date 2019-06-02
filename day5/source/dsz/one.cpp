#include <cstdio>

int N, z[23];

int main() {
	freopen("one.in", "r", stdin);
	freopen("one.out", "w", stdout);
	scanf("%d%d%d", &N, &z[1], &z[2]);
	puts(z[1] < z[2] ? "0" : "1");
	return 0;
}

