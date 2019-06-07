#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int f[1005][1005],n;
char s[1000005];
int main()
{
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
	memset(f,0x3f,sizeof(f));
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		f[i][i]=s[i]-'0';
	for(int i=2;i<=n;i++)
		for(int l=1;l<=n-i+1;l++)
		{
			int r=l+i-1;
			for(int k=l+1;k<r;k++)
				f[l][r]=min(f[l][r],max(f[l][k-1],f[k+1][r])+s[k]-'0');
			f[l][r]=min(f[l][r],min(f[l][r-1]+s[r]-'0',f[l+1][r]+s[l]-'0'));
		}
	printf("%d",f[1][n]);
	return 0;
}
