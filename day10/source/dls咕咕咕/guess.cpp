#include<cstdio>
#include<iostream>
#include<cctype>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
using namespace std;
const int N = 1e3 + 3;
char s[N];
int f[N][N];
int n;
int main(){
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
	scanf("%s",s + 1);
	n = strlen(s + 1);
	memset(f,0x3f,sizeof(f));
	for(int i = 1;i <= n + 1;++i) f[i][i] = f[i][i - 1] = 0;
	for(int len = 1;len <= n + 1;++len){
		for(int l = 1;l + len <= n + 1;++l){
			int	r = l + len;
			for(int k = l;k < r;++k){
				f[l][r] = min(f[l][r],max(f[l][k - 1] , f[k + 1][r]) + s[k] - '0');	
			}
		}
	}
	cout << f[1][n + 1];
	return 0;	
}
