#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
using namespace std;
int main()
{
	freopen("game.in","w",stdout);
	mt19937 rnd(time(0));
	int t=10000;
	printf("%d\n",t);
	while(t--)
	{
		int n=rnd()%2+9,m=rnd()%2;
		printf("%d %d\n",n,m);
		for(int i=1;i<=n;i++)
			printf("%d ",rand()%2);
		printf("\n");
	}
	return 0;
}