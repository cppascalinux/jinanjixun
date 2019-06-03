#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long 
#define R register
using namespace std;

const int M = 2000;
const int P = 1e9+7;
int n,m,k,a[2][M],d[2][M],tot1,tot2,b[15],t;

int main()
{
	freopen("add.in","r",stdin);
	freopen("add.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(R int i=1;i<=n;i++) scanf("%d",&b[i]);
	k=1<<n; k--; 
	t=m&1;
	a[t][k]=1;
	d[t][k]=1;
	for(R int i=m-1;i>=0;i--)
	{
		t^=1;
		memset(a[t],0,sizeof(a[t]));
		int g=1<<i;
		for(R int j=0;j<=k;j++)
		{
			int B=1;
			for(R int l=1,w=1;l<=n;l++,w<<=1) if(!(b[l]&g) && (j&w)) B=0;
			if(!B) continue;
			for(R int s=0;s<=k;s++) if(a[!t][s]) 
			{
				int las=0,B=1;
				for(R int l=1,w=1;l<=n;l++,w<<=1)
				{
					if(las && (s&w) && ((j&w)==0)) B=0; 
					las=j&w;
				}
				if(!B) continue;
				int x=0; las=0;
				for(R int l=1,w=1;l<=n;l++,w<<=1)
				{
					if(las && (s&w)) x|=w;
					if(!las && (s&w) && ((j&w)==0)) x|=w;
					las=j&w;
				}
				a[t][x]=(a[t][x]+a[!t][s])%P;
			}
		}
	}
	b[0]=(1<<m)-1;
	t=m&1;
	for(R int i=m-1;i>=0;i--)
	{
		t^=1;
		memset(d[t],0,sizeof(d[t]));
		int g=1<<i;
		for(R int j=0;j<=k;j++)
		{
			int B=1;
			for(R int l=1,w=1;l<=n;l++,w<<=1) if((b[l]&g) && (j&w)) B=0;
			if(!B) continue;
			for(R int s=0;s<=k;s++) if(d[!t][s]) 
			{
				int las=1,B=1;
				for(R int l=1,w=1;l<=n;l++,w<<=1)
				{
					if(!las && (s&w) && ((j&w) | (b[l]&g))) B=0;  
					las=(j&w) | (b[l]&g);
				}
				if(!B) continue;
				int x=0; las=1;
				for(R int l=1,w=1;l<=n;l++,w<<=1)
				{
					if(!las && (s&w)) x|=w;
					if(las && (s&w) && ((j&w) | (b[l]&g))) x|=w;
					las=(j&w) | (b[l]&g);
				}
				d[t][x]=(d[t][x]+d[!t][s])%P;
			}
		}
	}
	for(R int i=0;i<=k;i++)
	{
		(tot1+=a[0][i])%=P;
		(tot2+=d[0][i])%=P;
	}
	printf("%d",(LL)tot1*tot2%P);
}
