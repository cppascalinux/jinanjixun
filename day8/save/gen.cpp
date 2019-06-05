#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
using namespace std;
int main()
{
	freopen("save.in","w",stdout);
	mt19937 rnd(time(0));
	int n=10000,m=5000;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
		printf("%d ",rnd()%100000000+1);
	printf("\n");
	for(int i=1;i<=m;i++)
	{
		printf("2 %d %d\n",i,i+m);
	}
	// for(int i=1;i<=m;i++)
	// {
	// 	int a=rnd()%3+1,l=rnd()%n+1,r=rnd()%n+1;
	// 	if(l>r)
	// 		swap(l,r);
	// 	printf("%d %d %d",a,l,r);
	// 	if(a==1)
	// 		printf(" %d\n",rnd()%100000000+1);
	// 	else
	// 		printf("\n");
	// }
	return 0;
}