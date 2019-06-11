#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
char s[500009];
int fl[209][500009],fr[209][500009];
void dp()
{
	for(int i=1;i<=n+1;i++)
		fl[0][i]=fr[0][i]=i;
	for(int i=1;i<=200;i++)
	{
		for(int j=1;j<=n+1;j++)
			fl[i][j]=fl[i-1][j],fr[i][j]=fr[i-1][j];
		for(int j=1;j<=n;j++)
		{
			if(s[j]<=i)
			{
				int lm=fl[i-s[j]][j],rm=fr[i-s[j]][j+1];
				fr[i][lm]=max(fr[i][lm],rm),fl[i][rm]=min(fl[i][rm],lm);
			}
		}
		for(int j=2;j<=n+1;j++)
			fr[i][j]=max(fr[i][j],fr[i][j-1]);
		for(int j=n;j>=1;j--)
			fl[i][j]=min(fl[i][j],fl[i][j+1]);
	}
	// for(int i=0;i<=4;i++)
	// 	for(int j=1;j<=n+1;j++)
	// 		printf("i:%d j:%d fl:%d fr:%d\n",i,j,fl[i][j],fr[i][j]);
	for(int i=0;i<=200;i++)
		if(fr[i][1]==n+1)
		{
			printf("%d",i);
			break;
		}
}
int main()
{
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		s[i]-='0';
	dp();
	return 0;
}