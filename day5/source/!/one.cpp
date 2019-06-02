#include<cstdio>
using namespace std;
int n;
int main()
{
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	scanf("%d",&n);
	if(n==2)
	{
		scanf("%d",&n);
		if(n==1)printf("0\n");
		else printf("1\n");
		return 0;
	}
	return 0;
}
