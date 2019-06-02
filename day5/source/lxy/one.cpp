#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define il inline
#define re register
#define gc getchar
#define LL long long
using namespace std;
void rd(int &s)
{
	s = 0;
	bool p = 0;
	char ch;
	while (ch = gc(), p |= ch == '-', !isdigit(ch));
	while (s = s * 10 + ch - '0', ch = gc(), isdigit(ch));
	s *= (p ? -1 : 1);
}
const int MOD = 1000000007;
int A[100];
int qpow(int a, int b)
{
	int ans = 1;
	for (; b; b >>= 1, a = a * 1ll * a % MOD)
		if (b & 1)
			ans = ans * 1ll * a % MOD;
	return ans;
}
const int FAC[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880}; 
int cantor(int *a, int n)
{
    int x = 0;
    for (int i = 0; i < n; ++i)
    {
        int smaller = 0;
        for (int j = i + 1; j < n; ++j)
        {
            if (a[j] < a[i])
                smaller++;
        }
        x += FAC[n - i - 1] * smaller;
    }
    return x;
}
namespace solve
{
const int maxn = 200;
int a[maxn][maxn];
void gauss_jordan(int n)
{
    for (int i = 0; i < n; ++i)
    {
        int idx = i; 
        for (int j = i + 1; j < n; ++j)
            if (a[j][i] > a[idx][i])
                idx = j;
        if (idx != i)
            for (int j = i; j <= n; ++j)
                swap(a[i][j], a[idx][j]);
        for (int j = 0; j < n; ++j)
        {
            if (i != j)
            {
            	int temp = qpow(a[i][i] % MOD, MOD - 2) * 1ll * a[j][i] % MOD;
                for (int k = n; k >= i; --k) 
                    a[j][k] -= a[i][k] * 1ll * temp % MOD,
                    a[j][k] %= MOD,
                    a[j][k] = (a[j][k] < 0 ? a[j][k] + MOD : a[j][k]);
			}
		}
    }
}
int sum[20], temp[20];
void run(int n)
{
	for (int i = 0; i < n; ++i)
		sum[i] = i;
	a[0][0] = 1;
	a[0][FAC[n]] = 0;
	while (next_permutation(sum, sum + n))
	{
		int x = cantor(sum, n);
		a[x][x] = MOD - 1;
		a[x][FAC[n]] = MOD - 1;
		for (int i = 0; i < n; ++i)
			temp[i] = sum[i];
		int p = n * 1ll * (n - 1) % MOD * 1ll * qpow(2, MOD - 2) % MOD;
		p = qpow(p, MOD - 2);
		for (int i = 0; i < n; ++i)
		{
			for (int j = i + 1; j < n; ++j)
			{
				swap(temp[i], temp[j]);
				int y = cantor(temp, n);
				a[x][y] = p;
				swap(temp[i], temp[j]);
			}
		}
	};
	gauss_jordan(FAC[n]);
	int z = cantor(A + 1, n);
	int ans = a[z][FAC[n]] * 1ll * qpow(a[z][z], MOD - 2) % MOD;
	printf("%d", ans);
}
}
int main()
{
//	freopen("one.in", "r", stdin);
//	freopen("one.out", "w", stdout);
	int n;
	rd(n);
	for (int i = 1; i <= n; ++i)
		rd(A[i]);
	if (n == 1)
		puts("0");
	else
		if (n == 2)
			puts(A[1] == 1 ? "0" : "1");
		else
			solve::run(n);
	return 0;
}

