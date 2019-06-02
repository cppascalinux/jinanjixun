#include<cctype>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#define LL unsigned long long
#define mk make_pair
#define pii pair<int,int>
#include<map>
using namespace std;
const int N = 1e3 + 3;
const int base = 233;
LL ha[N][N];
char s[N];
int n,kk;
map <LL,int> m;
inline LL ha1(int l,int r){
	LL res = 0;
	for(int i = l;i <= r;++i) res = res * base + s[i];
	return res;
}
int main(){
	freopen("two.in","r",stdin);
	freopen("two.out","w",stdout);
	scanf("%s",s + 1);
	scanf("%d",&kk);
		n = strlen(s + 1);
	for(int i = 1;i <= n;++i)
		for(int j = i;j <= n;++j){
		 ha[i][j] = ha1(i,j);}
	int ans = 0;
	for(int i = 1;i <= n;++i){
		for(int j = i;j <= n;++j){
			if(m[ha[i][j]]) continue;
		//	printf("%d %d\n",i,j);
			int len = j - i + 1;
			int last = -1,now = 0;
			for(int k = 1;k <= n - len + 1;++k){
				if(ha[k][k + len - 1] == ha[i][j]){
					if(k > last + 1) now++;
					last = k + len - 1;
				//	now++;
					k = k + len - 1;
				}
				
			}
		//	printf("%d\n",now);
			if(now == kk) ans++;//cout << i << " "<<j << endl;
			m[ha[i][j]] = 1;
		}
	}
	printf("%d\n",ans);
	return 0;	
}
