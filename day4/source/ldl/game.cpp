#include<iostream>
#include<cstdio>
using namespace std;
int n,m,zero,czb;
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int T;cin>>T;
	while(T--){
		cin>>n>>m; zero=0;
		for(int a,i=1;i<=n;i++)
			cin>>a,zero+=(a&1==0);
		czb=(n-2)/2+(n-2&1&m);
		if(!((n&1)^(m)))puts("A");
		else if(zero-czb>=2)puts("A");
		else puts("B");
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
