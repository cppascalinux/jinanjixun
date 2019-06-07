#include<cstdio>
#include<vector>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=505050;
vector<int>s[N];
int a[N],f[N][182],mx[15];
char aa[N];
int main()
{
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
	
	int n,i,j,k,l,y,now;
	scanf("%s",aa+1);
	n=strlen(aa+1);
	for(i=1;i<=n;i++)
		a[i]=aa[i]-'0';
	for(i=1;i<=n+1;i++)
		f[i][0]=i;
	for(i=0;i<=180;i++)
	{
		if(f[1][i]>=n+1)
		{
			printf("%d\n",i);
			return 0;
		}
//		printf("%d\n",f[1][1]);
		for(j=1;j<=n+1;j++)
		{
			s[f[j][i]].push_back(j);
//			if(i==0)
//			printf("%d %d\n",j,f[j][i]);
			f[j][i]=max(f[j][i],f[j][i-1]);
//			if(i<=10)
//			printf("%d %d %d\n",i,j,f[j][i]);
		}
		for(j=1;j<=n;j++)
		{
			mx[a[j]]=max(mx[a[j]],f[j+1][i]);
			for(k=0;k<s[j].size();k++)
			{
				y=s[j][k];
//				if(i==0&&y==1)
//					printf("%d\n",mx[1]);
				now=0;
				for(l=1;l<=9&&i+l<=180;l++)
				{
					now=max(now,mx[l]);
					f[y][i+l]=max(f[y][i+l],now);
				}
			}
		}
		memset(mx,0,sizeof(mx));
	}
	for(i=1;i<=180;i++)
	{
		if(f[1][i]>=n+1)
		{
			printf("%d\n",i);
			return 0;
		}
	}
	return 0;
}

