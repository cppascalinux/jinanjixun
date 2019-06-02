#include<cctype>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#define mm(n) (n * (n - 1) / 2)
using namespace std;
typedef long long LL;
const LL mod = 1e9 + 7;
const int N = 15;
int s[1000001];LL book[1000001];
LL num[N];
int n,m,tot;
int a[N];
int gg[100001][6];
LL A[1005][1005];
inline LL quick(LL a,LL b){
	LL res = 1;	
	while(b){
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;	
	}
	return res;
}
void Gauss() {
    for(int i = 1; i < tot + 1; i ++) {
        int r = i;
        for(int j = i + 1; j < tot + 1; j ++)
            if(A[j][i] != 0) {r = j;break;}
        if(r != i) for(int j = 0; j <= tot + 1; j ++) std :: swap(A[r][j], A[i][j]);

        for(int j = tot + 1; j >= i; j --) {
            for(int k = i + 1; k < tot + 1; k ++)
                A[k][j] = (A[k][j] - (A[k][i] * quick((A[i][i] + mod) % mod,mod - 2) % mod * A[i][j]) % mod + mod)% mod;
        }
    }

    for(int i = tot; i >= 1; i --) {
        for(int j = i + 1; j < tot + 1; j ++)
            A[i][tot + 1] = (A[i][tot + 1] - A[j][tot + 1] * A[i][j] % mod + mod) % mod;
        A[i][tot + 1] = A[i][tot + 1] * quick(A[i][i],mod - 2) % mod;
    }
}
int main(){
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	int sum = 0;
	scanf("%d",&n);
	for(int i = 1;i <= n;++i) scanf("%d",&a[i]),sum = sum * 10 + a[i];
	for(int i = 1;i <= n;++i) num[i] = i;
	do{
		int w = 0;
		for(int i = 1;i <= n;++i) w = w * 10 + num[i];
		s[++tot] = w;
		book[w] = tot;
		for(int i = 1;i <= n;++i) gg[tot][i] = num[i];
	}while(next_permutation(num + 1,num + n + 1));
	int in = quick(mm(n),mod - 2);
	int in2 = quick(mm(n - 1),mod - 2);
	for(int i = 1;i <= tot;++i){
		bool flag = 0;
		for(int j = 1;j <= n;++j){
			for(int k = j + 1;k <= n;++k){
				swap(gg[i][j],gg[i][k]);
				int w = 0;for(int x = 1;x <= n;++x) w = w * 10 + gg[i][x];
				if(w != sum) flag = 1;
				swap(gg[i][j],gg[i][k]);
			}
		}
		for(int j = 1;j <= n;++j){
			for(int k = j + 1;k <= n;++k){
				swap(gg[i][j],gg[i][k]);
				LL chang = 0;
				int w = 0;for(int x = 1;x <= n;++x) w = w * 10 + gg[i][x];
				if(flag){
					if(w != sum) A[i][book[w]] = in2,A[i][tot + 1] = (A[i][tot + 1] - in2 + mod) % mod;
				}
				else A[i][book[w]] = in,A[i][tot + 1] = (A[i][tot + 1] - in + mod) % mod;
				swap(gg[i][j],gg[i][k]);
			}
		}
		A[i][i] = -1 + mod;
	}
	for(int i = 1;i <= tot;++i)
		A[book[sum]][i] = 0;
	A[book[sum]][book[sum]] = 1;
	A[book[sum]][tot + 1] = 0;
//	for(int i = 1;i <= tot + 1;++i){
//	for(int j = 1;j <= tot + 1;++j)
//		cout << A[i][j] << " ";
//		cout << endl;
//	}
	Gauss();
	printf("%lld\n",A[1][tot + 1]);
	return 0;	
}
