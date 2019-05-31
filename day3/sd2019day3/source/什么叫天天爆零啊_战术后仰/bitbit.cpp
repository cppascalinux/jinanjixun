#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int n,m,l,r,ans;
int a[55][510];
int bgn[510];

void work_n1()
{
	for(int i = 1;i <= m;i ++)
		if(a[1][i] == 1)
		{
			l = i;
			break;
		}
	for(int i = m;i >= 1;i --)
		if(a[1][i] == 1)
		{
			r = i;
			break;
		}
	for(int i = l;i <= r;i ++)
		if(a[1][i] && a[1][i] != a[1][i - 1])
		{
			ans ++;
			bgn[ans] = i;
		}
	printf("%d\n",ans);
	for(int cnt = 1;cnt <= ans;cnt ++)
	{
		printf("+\n");
		int flag = 0;
		for(int i = 1;i < bgn[cnt];i ++)
		{
			printf("0");
		}
		for(int i = bgn[cnt];i <= m;i ++)
		{
			if(a[1][i] == 0) flag = 1;
			if(!flag) printf("1");
			else printf("0");
		}
		printf("\n");
	}
}

int main()
{
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i ++)
		for(int j = 1;j <= m;j ++)
			scanf("%1d",&a[i][j]);
	if(n == 1)
	{
		work_n1();
	}
	else
	{
		
	}
	
	fclose(stdin);
	fclose(stdout);
	return ~~ (0 - 0);
}
