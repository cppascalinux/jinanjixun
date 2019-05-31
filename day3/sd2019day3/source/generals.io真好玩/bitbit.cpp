#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
int a[510][510];
char st[510];
int l[510],r[510],ans;
int main()
{
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",st+1);
		for(int j=1;j<=m;j++)
			a[i][j]=st[j]-'0';
	}
	if(n==1)
	{
		for(int i=1;i<=m+1;i++)
			if(a[1][i]==1&&a[1][i-1]==0)
				l[++ans]=i;
			else if(a[1][i]==0&&a[1][i-1]==1)
				r[ans]=i-1;
		printf("%d\n",ans);
		for(int i=1;i<=ans;i++)
		{
			putchar('+');
			putchar('\n');
			for(int j=1;j<l[i];j++)
				putchar('0');
			for(int j=l[i];j<=r[i];j++)
				putchar('1');
			for(int j=r[i]+1;j<=m;j++)
				putchar('0');
			putchar('\n');
		}
		return 0;
	}
	return 0;
}
