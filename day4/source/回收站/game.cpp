#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int t,n,m;
int a[100003];
char c[2];
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		if(m==0) c[0]='A',c[1]='B';
		else c[0]='B',c[1]='A';
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		int l=0,r=0;
		for(int i=1;i<=n;i++)
			if(a[i]&1)
			{
				l=i;
				break;
			}
		if(l==0)
		{
			if(n&1) printf("%c\n",c[0]);
			else printf("%c\n",c[1]);
			continue;
		}
		for(int i=n;i;i--)
			if(a[i]&1)
			{
				r=i;
				break;
			}
		int cnt=0,k=0;
		for(int i=l;i<=r;i++)
		{	
			if((a[i]&1)==0) k++; 
			else cnt++;
		}
		if(cnt==1)
		{
			if(n&1) printf("%c\n",c[0]);
			else printf("%c\n",c[1]);
			continue;
		}
		if(k&1)
		{
			if(n&1) printf("%c\n",c[1]);
			else printf("%c\n",c[0]);
		}
		else printf("%c\n",c[0]);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
