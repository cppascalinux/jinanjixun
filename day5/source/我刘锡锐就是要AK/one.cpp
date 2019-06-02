#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++)
	{
		scanf("%d",&line[i]);
	}
	if(n == 0 || n == 1) printf("0");
	else if(n == 2)
	{
		if(line[1] <= line[2]) printf("0");
		else printf("1");
	}
	
	
	fclose(stdin);
	fclose(stdout);
	return ~~ (0 - 0);
}
