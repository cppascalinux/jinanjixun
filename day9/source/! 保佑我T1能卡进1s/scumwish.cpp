#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define rg register
#define li long long
#define mod 100000007
using namespace std;
int n,m;
int mat1[21][21],mat2[21][21];
int f[2][21][1050009];
void dp()
{
	f[0][m][(1<<m)-1]=1;
	for(int i=1;i<=n;i++)
	{
		int cur=i&1;
		for(int s=0;s<1<<m;s++)
			f[cur][0][s]=f[cur^1][m][s];
		for(int j=1;j<=m;j++)
		{
			int *lst1=f[cur][j-1],*lst2,*now=f[cur][j];
			if(j>=2)
				lst2=f[cur][j-2];
			bool m1=mat1[i-1][j],m2=mat2[i-1][j],m3=mat1[i][j-1];
			int t1=1<<(j-1),t2=1<<j,t3=0;
			if(j>=2)
				t3=1<<(j-2);
			int *lp1=lst1-t1,*lp11=lst1-t1-t2,*lp2=lst2-t1;
			int mx=1<<m;
			bool fg=j>=2;
			for(rg int s=0;s<mx;s++)
			{
				if(!(s&t1))
					now[s]=lst1[s|t1];
				else
				{
					int p1=0,p2=0;
					p1=lst1[s];
					if(m2)
					{
						p1+=lp1[s];
						// if(m1&&(s&t2))
						p2+=m1&&(s&t2)?lp11[s]:0;
					}
					if(fg&&m3&&(s&t3))
					{
						p1+=lst2[s];
						// if(m2)
						p2+=m2?lp2[s]:0;
					}
					now[s]=(p1+p2)%mod;
					// while(p>=mod)
					// 	p-=mod;
				}
			}
		}
	}
	printf("%d\n",f[n&1][m][(1<<m)-1]);
}
int main()
{
	freopen("scumwish.in","r",stdin);
	freopen("scumwish.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m-1;j++)
			scanf("%d",&mat1[i][j]);
	for(int i=1;i<=n-1;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&mat2[i][j]);
	dp();
	cerr<<clock()<<endl;
	return 0;
}