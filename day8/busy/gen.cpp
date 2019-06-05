#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
using namespace std;
int main()
{
	freopen("busy.in","w",stdout);
	mt19937 rnd(time(0));
	int n=100000,m=100000;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
		printf("%d ",rnd()%50000+1);
	printf("\n");
	for(int i=1;i<=m;i++)
	{
		int l=rnd()%50000+1,r=rnd()%50000+1;
		if(l>r)
			swap(l,r);
		printf("%d %d %d\n",2,l,r);
	}
	return 0;
}