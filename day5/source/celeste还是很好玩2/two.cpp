#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#define il inline
#define re register
#define gc getchar
#define LL long long
using namespace std;
const int MOD = 1000000007;
int nxt[10000];
char c1[10000];
LL hs[10000];
int _p[10000];
int k, l1;

struct Hash_Table {
	int head[3335500];
	int nxt[5000050];
	int key[5000050];
	bool val[5000050];
	int tot;
	int mod;
	Hash_Table() { mod = 3333331; tot = 0; }
	int Hash(int p) { return p % mod; }
	bool& operator[] (int p) {
		int np = Hash(p);
		for(int i = head[np]; i; i = nxt[i]) {
			if(key[i] == p) return val[i];
		}
		key[++ tot] = p;
		nxt[tot] = head[np];
		head[np] = tot;
		return val[tot] = 0;
	}
} ht;

il int qpow(re int a, re int b)
{
	re int as = 1;
	for (; b; b >>= 1, a = a * 1ll * a % MOD)
		if (b & 1)
			as = as * 1ll * a % MOD;
	return as;
}
il void hs_init(char* ch, re int len)
{
	for (re int i = 1; i <= len; ++i)
		hs[i] = (hs[i - 1] * 131ll + ch[i]) % MOD;
}
il int hs_get(re int l, re int r)
{
	re int q = (hs[r] - hs[l - 1] * 1ll * _p[r - l + 1]) % MOD;
	if (q < 0)
		q += MOD;
	return q;
}
il void kmp_init(char *c2, re int l2)
{
	re int p;
    for (re int i = 2; i <= l2; ++i)
    {
        p = nxt[i - 1];
        while (c2[p + 1] != c2[i] && p)
            p = nxt[p];
        if (c2[p + 1] == c2[i])
            nxt[i] = p + 1;
        else
            nxt[i] = 0;
    }	
}
il bool kmp(char* c2, re int l2)
{
	re int kn = 0, r = -100000;
    re int j = 0;
    for (re int i = 1; i <= l1; ++i)
    {
        while ((c1[i] != c2[j + 1]) && j)
            j = nxt[j];
        if (c1[i] == c2[j + 1])
            ++j;
        if (j == l2)
        {
        	if (i - l2 > r)
        		++kn;
        	r = i;
            j = nxt[j];
            if (kn > k)
            	return 0;
        }
    }
    return kn == k;
}
int main()
{
	freopen("two.in", "r", stdin);
	freopen("two.out", "w", stdout);
	re int as = 0;
	scanf("%s", c1 + 1);
	scanf("%d", &k);
	l1 = strlen(c1 + 1);
	hs_init(c1, l1);
	_p[0] = 1;
	for (re int i = 1; i <= l1; ++i) _p[i] = 1ll * _p[i - 1] * 131 % MOD;
	for (re int i = 1; i <= l1; ++i)
	{
		kmp_init(c1 + i - 1, l1 - i + 1);
		for (re int j = 1; i + j - 1 <= l1; ++j)
		{
			int p = hs_get(i, i + j - 1);
			if (ht[p])
				continue;
			ht[p] = 1;
			as += kmp(c1 + i - 1, j);
		}
	}
	printf("%d", as);
	return 0;
}

