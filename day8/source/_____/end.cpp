#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define maxn 51
using namespace std;

const int p = 1000000007;

int n, m, K, d[maxn];

char s[maxn];

struct _ {

    int a, b, c, e;
    int Main() {
        int M = 1 << n * m, ans = 0;
        for (int i = 1; i <= m; ++i) e |= (1 << m - i) * d[i];
        for (int st = 0; st < M; ++st) {
            a = b = c = 0; bool F = 1; 
            for (int i = 1; i <= m; ++i) {
                int s = (st >> i - 1 & 1) + (st >> i + m - 1 & 1) + (st >> i + 2 * m - 1 & 1); 
                a |= (st >> i - 1 & 1) << i - 1; 
                b |= (st >> i + m - 1 & 1) << i - 1; 
                c |= (st >> i + 2 * m - 1 & 1) << i - 1;
                if (s & 1) F = 0; 
            }
            if (a == b || a == c || b == c || !F) continue ;
            if (a >= e || b >= e || c >= e) continue ;
            ++ans; 
        } cout << ans / 6 << endl; 
        return 0; 
    }
} _;

int main() {
	freopen("end.in", "r", stdin); 
	freopen("end.out", "w", stdout); 
    cin >> n >> K; scanf("%s", s + 1); m = strlen(s + 1); 
    for (int i = 1; i <= m; ++i) d[i] = s[i] - '0';
    if (n == 3 && K == 1) return _.Main(); 
    return 0; 
}
