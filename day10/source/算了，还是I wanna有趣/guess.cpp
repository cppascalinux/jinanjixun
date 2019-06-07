#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int f[181][500010],a[500010];
int pre[500010][10];
int n;char st[500010];
const int M=180;
int main()
{
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
	scanf("%s",st+1);
	n=strlen(st+1);
	for(int i=1;i<=n;i++)
	{
		a[i]=st[i]-'0';
		for(int j=1;j<=9;j++)
			pre[i][j]=(a[i]==j)?i:pre[i-1][j];
	}
	for(int i=0;i<=M;i++)
		f[i][n+1]=n+1;
	for(register int i=n;i>=1;i--)
	{
		f[0][i]=i;
		for(int j=1;j<=M;j++)
		{
			f[j][i]=f[j-1][i];
			for(int k=1;k<=min(9,j);k++)
			{
				int pos=pre[f[j-k][i]][k];
				if(pos<i)continue;
				f[j][i]=max(f[j][i],f[j-k][pos+1]);
			}
//			if(j<=20)printf("%d %d:%d\n",i,j,f[j][i]);
		}
	}
	for(int i=0;i<=M;i++)
		if(f[i][1]==n+1){
			printf("%d\n",i);
			fclose(stdin);fclose(stdout);
			return 0;
		}
	fclose(stdin);fclose(stdout);
	return 0;
}
