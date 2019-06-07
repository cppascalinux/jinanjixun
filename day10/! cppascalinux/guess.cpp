#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
int n;
char s[100009];
int f[1009][1009],g[1009][1009];
void dp()
{
	memset(f,0x7F,sizeof(f));
	for(int i=1;i<=n+1;i++)
		f[i][i]=0;
	for(int i=2;i<=n+1;i++)
		for(int j=1;j<=n+1-i+1;j++)
		{
			int l=j,r=j+i-1;
			for(int k=l;k<=r-1;k++)
			{
				int nv=max(f[l][k],f[k+1][r])+s[k];
				if(nv<f[l][r])
					f[l][r]=nv,g[l][r]=k;
			}
		}
	printf("%d",f[1][n+1]);
}
void output(int l,int r)
{
	printf("l:%d r:%d\n",l,r);
	if(l<r)
		output(l,g[l][r]),output(g[l][r]+1,r);
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
	// output(1,n+1);
	cerr<<clock();
	return 0;
}