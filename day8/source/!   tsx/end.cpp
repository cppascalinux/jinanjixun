#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int m,n,kk,f[2][3005][3005],lim=1,mod=1e9+7;
char s[100005];
int main()
{
	freopen("end.in","r",stdin);
	freopen("end.out","w",stdout);
	scanf("%d%d%s",&m,&kk,s);
	if(kk==1&&strlen(s)<=11)
	{
		for(int i=0;s[i];i++)
			n=n*2+s[i]-'0';
		lim=1;
		while(lim<=n) lim<<=1;
		for(int i=0;i<=n;i++)
			f[0][0][i]=1;
		for(int i=1;i<=m;i++)
		{
			int nw=i%2;
			for(int j=0;j<lim;j++)
				for(int k=1;k<=n;k++)
				{
					f[nw][j][k]=f[nw^1][j^(k-1)][k-1];
					//printf("f[%d][%d][%d]=%d\n",i,j,k,f[nw][j][k]);
				}
			for(int j=0;j<=lim;j++)
				f[nw][j][0]=0;
			for(int j=0;j<=lim;j++)
				for(int k=1;k<=n;k++)
					f[nw][j][k]=(f[nw][j][k]+f[nw][j][k-1])%mod;
		}
		printf("%d",f[m%2][0][n]);
		return 0;
	}
	return 0;
}
