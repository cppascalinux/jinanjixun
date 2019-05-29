#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<cstdlib>
using namespace std;
int main()
{
	freopen("dream.in","w",stdout);
	srand(time(0));
	int n=60,m=60,k=60,w=1000000000;
	printf("%d %d %d %d\n",n,m,k,w);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			for(int l=1;l<=k;l++)
				printf("%d ",rand()%2);
			printf("\n");
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			for(int l=1;l<=k;l++)
				printf("%d ",rand());
			printf("\n");
		}
	return 0;
}