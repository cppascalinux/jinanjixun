#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
using namespace std;
int main()
{
	freopen("tree.in","w",stdout);
	random_device sd;
	mt19937 rnd(sd());
	int n=1000;
	printf("%d\n",n);
	for(int i=2;i<=n;i++)
		printf("%d %lu %lu\n",i,rnd()%(i-1)+1,rnd()%1000000000+1);
	for(int i=2;i<=n;i++)
		printf("%d %lu %lu\n",i,rnd()%(i-1)+1,rnd()%1000000000+1);
	return 0;
}