#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int t,n,m,a[100005],f[100005];
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			a[i]&=1;
			f[i]=f[i-1];
			if(a[i])f[i]=max(f[i],f[i-2]+1);
		}
		if(n==1)printf("%c\n",a[1]==0?'A':'B');
		else if(m==0)
		{
			if(n&1)printf("%c\n",f[n]==(n+1)/2?'B':'A');
			else printf("A\n");
		}
		else
		{
			if(n&1)printf("A\n");
			else printf("%c\n",f[n]==n/2?'B':'A');
		}
	}
	return 0;
}
