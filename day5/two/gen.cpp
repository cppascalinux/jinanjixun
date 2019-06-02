#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
#include<cstdlib>
#include<ctime>
using namespace std;
int main()
{
	freopen("two.in","w",stdout);
	mt19937 rnd(time(0));
	int n=100000,k=rnd()%10+1;
	for(int i=1;i<=n;i++)
		printf("%c",rnd()%2+'a');
	// for(int i=1;i<=n-1;i++)
	// 	printf("a");
	// printf("b");
	printf("\n%d",k);
	return 0;
}