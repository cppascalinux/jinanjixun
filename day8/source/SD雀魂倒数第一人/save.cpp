#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int n,m,flag,l,r,x,ans;
int val[1000010];

int main()
{
	freopen("save.in","r",stdin);
	freopen("save.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i ++)
		scanf("%d",&val[i]);
	while(m --)
	{
		scanf("%d",&flag);
		if(flag == 1)
		{
			scanf("%d%d%d",&l,&r,&x);
			for(int i = l;i <= r;i ++)
				val[i] ^= x;
		}
		else if(flag == 2)
		{
			scanf("%d%d",&l,&r);
			sort(val + l,val + r + 1);
		}
		else
		{
			ans = 0;
			scanf("%d%d",&l,&r);
			for(int i = l;i <= r;i ++)
				ans ^= val[i];
			printf("%d\n",ans);
		}
	}
	
	fclose(stdin);
	fclose(stdout);
	return ~~ (0 - 0);
}
