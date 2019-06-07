#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
int main()
{
	srand(time(0));
	freopen("guess.in","w",stdout);
	int n=500;
	for(int i=1;i<=n;i++)
		printf("%d",rand()%9+1);
	return 0;
}
