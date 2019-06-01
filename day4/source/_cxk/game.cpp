#include <iostream>
#include <cstdio>
#include <cctype>
#define maxn 100010
#define gc getchar
using namespace std;

int read() {
	int x = 0; char c = gc(); 
	while (!isdigit(c)) c = gc(); 	
	while (isdigit(c)) { x = x * 10 + c - '0'; c = gc(); } 
	return x;
}

int n, m; 

int a[maxn];

void work() {
	n = read(); m = read(); 
	for (int i = 1; i <= n; ++i) a[i] = read() & 1;
	if (n == 1) return (void) (puts(a[1] ? "B" : "A"));
	if (!m && n % 2 == 0) return (void) (puts("A"));
	if (m && n % 2 == 1) return (void) (puts("A"));
	int s = 0, S = 0; 
	for (int i = 1; i <= n; ++i) s += a[i] ^ 1; 
	S = m ? (n - 2 + 1) / 2 : (n - 2) / 2;
	puts(S >= s - 1 ? "B" : "A");
}

int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	int T; cin >> T; 
	while (T--) work(); 
	return 0; 
}
