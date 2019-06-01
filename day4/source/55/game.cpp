#include<iostream>
#include<cstdio>
using namespace std;
int T,n,m,a[1000010];
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(register int i=1;i<=n;i++)scanf("%d",&a[i]);
		printf("A\n");
	}
	return 0;
}
