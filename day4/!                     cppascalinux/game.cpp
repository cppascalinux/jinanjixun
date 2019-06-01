#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m;
int s[100009];
int pre1[100009],suf2[100009];
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			scanf("%d",s+i),s[i]&=1;
		if(n==1)
		{
			if(s[1]==1)
				printf("B\n");
			else
				printf("A\n");
			continue;
		}
		int stp=(n&1)^m;//the last step
		if(stp==0)
		{
			printf("A\n");
			continue;
		}
		if(n&1)
		{
			int fg=1;
			for(int i=1;i<=n;i+=2)
				if(!s[i])
					fg=0;
			if(fg)
				printf("B\n");
			else
				printf("A\n");
			continue;
		}
		memset(pre1,0,sizeof(pre1));
		memset(suf2,0,sizeof(suf2));
		for(int i=1;i<=n;i+=2)
		{
			if(!s[i])
				break;
			pre1[i]=1;
		}
		for(int i=n;i>=1;i-=2)
		{
			if(!s[i])
				break;
			suf2[i]=1;
		}
		if(pre1[n-1]||suf2[2])
		{
			printf("B\n");
			continue;
		}
		int fg=0;
		for(int i=1;i<=n-3;i++)
			if((pre1[i]&&suf2[i+3]))
				fg=1;
		if(fg)
			printf("B\n");
		else
			printf("A\n");
	}
	return 0;
}