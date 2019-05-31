#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct node
{
	int x,y,c;
};
queue<node> q;
int n,m,ans;
int a[503][503],s[503],l,r;
char c[503];
int main()
{
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	memset(a,-1,sizeof(a));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",c+1);
		for(int j=1;j<=m;j++)
			a[i][j]=(c[j]^48);
	}
	int l,r;
	for(int i=1;i<=m;i++)
		if(a[1][i])
		{
			l=i;
			break;
		}
	for(int i=m;i;i--)
		if(a[1][i])
		{
			r=i;
			break;
		}
	for(int i=1;i<=m;i++) 
	{
		if(a[1][i]==1&&s[1]==0&&ans==0) s[++ans]=i;
		else if(a[1][i]==0&&a[1][i-1]==1&&i<r) s[++ans]=i;
	}
	printf("%d\n",ans);
	if(!ans) return 0;
	printf("+\n");
	for(int i=1;i<=m;i++)
	{	
		if(l<=i&&r>=i) putchar('1');
		else putchar('0');
	}
	putchar('\n');
	for(int i=2;i<=ans;i++)
	{
		bool flag=true;
		printf("-\n");
		for(int j=1;j<=m;j++)
		{
			if(j<s[i]) putchar('0');
			else if(j>=s[i]&&flag&&a[1][j]==a[1][s[i]]) putchar('1');
			else
			{
				flag=false;
				putchar('0');
			}
		}
		putchar('\n');	
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
