#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
char s[500005];
int n,a[500005],f[205][500005],last[500005][15],*ff;
int main()
{
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
	scanf("%s",s+1);
	n=(int)strlen(s+1);
	for(int i=1;i<=n;i++)
	{
		a[i]=s[i]-'0';
		f[0][i]=i-1;
		for(int j=1;j<=9;j++)last[i][j]=last[i-1][j];
		last[i][a[i]]=i;
		for(int j=2;j<=9;j++)last[i][j]=max(last[i][j],last[i][j-1]);
	}
	f[0][n+1]=n;
	for(int i=1;i<=180;i++)
	{
		ff=f[i];
//		printf("i=%d:",i);
		for(int j=1;j<=n;j++)
		{
			ff[j]=max(f[i-1][j],ff[j-1]);
			if(i<9)
			{
				for(int k=1;k<=i;k++)
				{
					ff[j]=max(ff[j],f[i-k][last[f[i-k][j]+1][k]+1]);
//					printf("p=%d,f=%d\n",p+1,f[j][i]);
				}
			}
			else
			{
				ff[j]=max(ff[j],f[i-1][last[f[i-1][j]+1][1]+1]);
				ff[j]=max(ff[j],f[i-2][last[f[i-2][j]+1][2]+1]);
				ff[j]=max(ff[j],f[i-3][last[f[i-3][j]+1][3]+1]);
				ff[j]=max(ff[j],f[i-4][last[f[i-4][j]+1][4]+1]);
				ff[j]=max(ff[j],f[i-5][last[f[i-5][j]+1][5]+1]);
				ff[j]=max(ff[j],f[i-6][last[f[i-6][j]+1][6]+1]);
				ff[j]=max(ff[j],f[i-7][last[f[i-7][j]+1][7]+1]);
				ff[j]=max(ff[j],f[i-8][last[f[i-8][j]+1][8]+1]);
				ff[j]=max(ff[j],f[i-9][last[f[i-9][j]+1][9]+1]);
			}
//			printf("%d ",f[j][i]);
		}
		ff[n+1]=max(ff[n+1],ff[n]);
//		printf("\n");
		if(ff[1]>=n)
		{
			printf("%d\n",i);
			return 0;
		}
	}
	return 0;
}
