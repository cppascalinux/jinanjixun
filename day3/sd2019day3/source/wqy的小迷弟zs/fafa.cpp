#include<cstring>
#include<cstdio>
#include<iostream>
#include<vector>
#include<cctype>
#include<algorithm>
#define LL long long
#define pii pair<int,int>
#define mk make_pair
using namespace std;
const int N = 1e5 + 3;
LL n,k;
int f[N][2];
int num[N];
inline bool check(){
	for(int i = 1;i <= n;++i) f[i][1] = 1,f[i][0] = 0;
	for(int i = 2;i <= n;++i)
		for(int j = 1;j < i;++j){
			if(num[i] > num[j]) f[i][1] = max(f[i][1],f[j][0] + 1);
			else f[i][0] = max(f[i][0],f[j][1] + 1);
		}
	LL res = 0;
	for(int i = 1;i <= n;++i) res = max((int)res,max(f[i][0],f[i][1]));
//	cout << res << endl;
	return res == k; 
}
int main(){
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
//	ios::sync_with_stdio(false);
	cin >> n >> k;
	if(n <= 10){
		int ans = 0;
		for(int i = 1;i <= n;++i) num[i] = i;
		do{ if(check()) ans++; }while(next_permutation(num + 1,num + n + 1));
		cout << ans << endl;
	}
	return 0;	
}
