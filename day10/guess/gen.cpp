#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
using namespace std;
int main()
{
	freopen("guess.in","w",stdout);
	mt19937 rnd(time(0));
	int n=1000;
	for(int i=1;i<=n;i++)
		printf("%d",rnd()%9+1);
	return 0;
}