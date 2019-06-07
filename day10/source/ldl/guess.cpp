#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=2019;
int n,a[N],f[N][N]; char s[N];
int main()
{
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
	scanf("%s",s); n=strlen(s);
	for(int i=1;i<=n;i++)a[i]=s[i-1]-'0';
	memset(f,0x3f,sizeof f);
	for(int i=1;i<=n+1;i++)f[i][i]=0;
	for(int len=1;len<=n+1;len++)
		for(int l=1;l+len-1<=n+1;l++){
			int r=l+len-1;
			for(int k=l;k<=r;k++)
				f[l][r]=min(f[l][r],max(f[l][k],f[k+1][r])+a[k]);
		}
	cout<<f[1][n+1];
	fclose(stdin); fclose(stdout);
	return 0;
}
