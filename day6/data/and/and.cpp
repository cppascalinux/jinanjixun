//2019.06.03
//山东省队一轮集训 day6 T1 数 与和或相对独立,分别计算;再用轮廓线优化dp,即可,O(2^n*n*m)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<cassert>
#define li long long
#define mod 1000000007
using namespace std;
int n,m;
int sp[11];
int f1[31][11][1059][2],f2[31][11][1059][2];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
int dp1()
{
	f1[m][n-1][0][0]=1;
	for(int i=m-1;i>=0;i--)
	{
		for(int s=0;s<1<<(n-1);s++)
		{
			f1[i][0][s][0]=(f1[i+1][n-1][s][0]+f1[i+1][n-1][s][1])%mod;
			if((sp[1]>>i)&1)
				f1[i][0][s][1]=f1[i][0][s][0];
		}
		for(int j=0;j<=n-2;j++)
			for(int s=0;s<1<<(n-1);s++)
			{
				if(!((sp[j+2]>>i)&1))
				{
					if((s>>j)&1)
						f1[i][j+1][s][0]=((li)f1[i][j+1][s][0]+f1[i][j][s][0]+f1[i][j][s][1])%mod;
					else
						f1[i][j+1][s][0]=(f1[i][j+1][s][0]+f1[i][j][s][0])%mod;
				}
				else
				{
					if((s>>j)&1)
					{
						f1[i][j+1][s][0]=((li)f1[i][j+1][s][0]+f1[i][j][s][0]+f1[i][j][s][1])%mod;
						f1[i][j+1][s][1]=((li)f1[i][j+1][s][1]+f1[i][j][s][0]+f1[i][j][s][1])%mod;
					}
					else
					{
						f1[i][j+1][s][0]=(f1[i][j+1][s][0]+f1[i][j][s][0])%mod;
						f1[i][j+1][s][1]=(f1[i][j+1][s][1]+f1[i][j][s][1])%mod;
						int ns=s+(1<<j);
						// printf("ns:%d\n",ns);
						f1[i][j+1][ns][1]=(f1[i][j+1][ns][1]+f1[i][j][s][0])%mod;
						// printf("i:%d j:%d ns:%d lstf:%d nf:%d\n",i,j,ns,f1[i][j][s][0],f1[i][j+1][ns][1]);
					}
				}
			}
	}
	int ans=0;
	for(int s=0;s<1<<(n-1);s++)
		for(int i=0;i<=1;i++)
			ans=(ans+f1[0][n-1][s][i])%mod;
	// for(int i=m-1;i>=0;i--)
	// 	for(int j=0;j<=n-1;j++)
	// 		for(int k=0;k<1<<(n-1);k++)
	// 			for(int l=0;l<=1;l++)
	// 				printf("i:%d j:%d k:%d l:%d f:%d\n",i,j,k,l,f1[i][j][k][l]);
	return ans;
}
int dp2()
{
	f2[m][n-1][0][0]=1;
	for(int i=m-1;i>=0;i--)
	{
		for(int s=0;s<1<<(n-1);s++)
		{
			f2[i][0][s][1]=(f2[i+1][n-1][s][0]+f2[i+1][n-1][s][1])%mod;
			if(!((sp[1]>>i)&1))
				f2[i][0][s][0]=f2[i][0][s][1];
		}
		for(int j=0;j<=n-2;j++)
			for(int s=0;s<1<<(n-1);s++)
			{
				if((sp[j+2]>>i)&1)
				{
					if((s>>j)&1)
						f2[i][j+1][s][1]=((li)f2[i][j+1][s][1]+f2[i][j][s][0]+f2[i][j][s][1])%mod;
					else
						f2[i][j+1][s][1]=(f2[i][j+1][s][1]+f2[i][j][s][1])%mod;
				}
				else
				{
					if((s>>j)&1)
					{
						f2[i][j+1][s][0]=((li)f2[i][j+1][s][0]+f2[i][j][s][0]+f2[i][j][s][1])%mod;
						f2[i][j+1][s][1]=((li)f2[i][j+1][s][1]+f2[i][j][s][0]+f2[i][j][s][1])%mod;
					}
					else
					{
						f2[i][j+1][s][0]=(f2[i][j+1][s][0]+f2[i][j][s][0])%mod;
						f2[i][j+1][s][1]=(f2[i][j+1][s][1]+f2[i][j][s][1])%mod;
						int ns=s+(1<<j);
						f2[i][j+1][ns][0]=(f2[i][j+1][ns][0]+f2[i][j][s][1])%mod;
					}
				}
			}
	}
	int ans=0;
	for(int s=0;s<1<<(n-1);s++)
		for(int i=0;i<=1;i++)
			ans=(ans+f2[0][n-1][s][i])%mod;
	return ans;
}
int main()
{
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",sp+i);
	int v1=dp1();
	int v2=dp2();
	// printf("v1:%d v2:%d\n",v1,v2);
	printf("%lld\n",(li)v1*v2%mod);
	cerr<<clock();
	return 0;
}