#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<random>
#include<cassert>
#define li long long
using namespace std;
random_device sd;
mt19937 rnd(sd());
int n;
int e[39][39];
int vis[39];
li judge()
{
	li ans=0;
	for(li s=1;s<1LL<<n;s++)
	{
		memset(vis,0,sizeof(vis));
		int sm1=0,sm2=0;
		for(int i=1;i<=n;i++)
			if((s>>(i-1))&1)
			{
				sm1++;
				for(int j=1;j<=n;j++)
					vis[j]|=e[i][j];
			}
		for(int i=1;i<=n;i++)
			if(vis[i])
				sm2++;
		if(sm1>sm2)
			ans++;
	}
	return ans;
}
int main()
{
	for(n=1;n<=32;n++)
		for(int j=1;j<=10;j++)
		{
			li k=rnd()%(1LL<<n);
			FILE *in=fopen("circle.in","w");
			fprintf(in,"%d %lld",n,k);
			fclose(in);
			system("./circle");
			FILE *out=fopen("circle.out","r");
			for(int a=1;a<=n;a++)
				for(int b=1;b<=n;b++)
					fscanf(out,"%d",e[a]+b);
			fclose(out);
			if(judge()==k)
				printf("AC n:%d j:%d\n",n,j);
			else
				printf("WA n:%d j:%d\n",n,j),exit(-1);
		}
	return 0;
}