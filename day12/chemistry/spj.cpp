#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cassert>
#include<cstdlib>
using namespace std;
int n,k;
int w[100009];
int main()
{
	freopen("result.out","w",stdout);
	for(int t=1;t<=102;t++)
	{
		printf("test %d: ",t);
		FILE *in,*out,*ans;
		char s[100];
		sprintf(s,"cp chemistry%d.in chemistry.in; ./chemistry",t);
		system(s);
		sprintf(s,"chemistry%d.in",t);
		in=fopen(s,"r");
		sprintf(s,"chemistry%d.out",t);
		ans=fopen(s,"r");
		out=fopen("chmistry.out","r");
		fscanf(in,"%d%d",&n,&k);
		int m1,m2;
		fscanf(ans,"%d",&m1);
		fscanf(out,"%d",&m2);
		if(m1==-1)
		{
			if(m2!=-1)
				printf("WA expected -1 read %d\n",m2);
			else
				printf("AC expected -1 read -1\n");
			continue;
		}
		if(m2>3*n)
		{
			printf("WA too many operations\n");
			continue;
		}
		int fg=0;
		for(int i=1;i<=n;i++)
			w[i]=1;
		for(int i=1,a,b;i<=m2;i++)
		{
			fscanf(out,"%d%d",&a,&b);
			if(a>n||b>n)
			{
				printf("WA %d or %d is greater than n\n",a,b);
				fg=1;break;
			}
			if(w[a]<w[b])
			{
				printf("WA %d is less than %d\n",a,b);
				fg=1;break;
			}
			w[a]-=w[b],w[b]*=2;
		}
		if(fg)
			continue;
		if(w[1]!=k)
		{
			printf("WA 1 is %d while k is %d\n",w[1],k);
			continue;
		}
		printf("AC 1 is %d while k is %d\n",k,k);
	}
	return 0;
}