#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define li long long
#define mod 998244353
#define inf 0x7F7F7F7F
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,k,w;
int mat[69][69][69],v[69][69][69];
int up[69][69][69],dn[69][69][69];
int mup[69][69],mdn[69][69];
int sm[69][69];
int ans[69][69][69];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
void init()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			for(int l=1;l<=k;l++)
			{
				dn[l][i][j]=dn[l-1][i][j]+1;
				if(!mat[i][j][l])
					dn[l][i][j]=0;
			}
			for(int l=k;l>=1;l--)
			{
				up[l][i][j]=up[l+1][i][j]+1;
				if(!mat[i][j][l])
					up[l][i][j]=0;
			}
		}
	// for(int i=1;i<=n;i++)
	// 	for(int j=1;j<=m;j++)
	// 		for(int l=1;l<=k;l++)
	// 			printf("i:%d j:%d l:%d up:%d dn:%d\n",i,j,l,up[i][j][l],dn[i][j][l]);
}
void solve()
{
	li nsum=0;
	for(int l=1;l<=k;l++)
	{
		for(int sx=1;sx<=n;sx++)
			for(int sy=1;sy<=m;sy++)
			{
				for(int ex=sx-1;ex<=n;ex++)
					mup[ex][sy-1]=mdn[ex][sy-1]=inf;
				for(int ey=sy-1;ey<=m;ey++)
					mup[sx-1][ey]=mdn[sx-1][ey]=inf;
				for(int ex=sx-1;ex<=n;ex++)
					for(int ey=sy-1;ey<=m;ey++)
						sm[ex][ey]=0;
				for(int ex=sx;ex<=n;ex++)
					for(int ey=sy;ey<=m;ey++)
					{
						mup[ex][ey]=min(up[l][ex][ey],min(mup[ex-1][ey],mup[ex][ey-1]));
						mdn[ex][ey]=min(dn[l][ex][ey],min(mdn[ex-1][ey],mdn[ex][ey-1]));
						int tmp=mup[ex][ey]*mdn[ex][ey];
						nsum+=mup[ex][ey];
						if(!tmp)
							break;
						sm[sx][sy]+=tmp;
						sm[ex+1][ey+1]+=tmp;
						sm[sx][ey+1]-=tmp;
						sm[ex+1][sy]-=tmp;
					}
				for(int ex=sx;ex<=n;ex++)
					for(int ey=sy;ey<=m;ey++)
						ans[l][ex][ey]+=(sm[ex][ey]+=sm[ex-1][ey]+sm[ex][ey-1]-sm[ex-1][ey-1]);
			}
	}
	// for(int i=1;i<=n;i++)
	// 	for(int j=1;j<=m;j++)
	// 		for(int l=1;l<=k;l++)
	// 			printf("i:%d j:%d l:%d ans:%d v:%d\n",i,j,l,ans[i][j][l],v[i][j][l]);
	nsum%=mod;
	int out=0;
	int sum=(li)n*(n+1)*m*(m+1)*k*(k+1)%mod;
	sum=(li)sum*qpow(8,mod-2)%mod;
	sum=qpow(sum,w);
	int inv=qpow(sum,mod-2);
	// printf("inv:%d\n",inv);
	// printf("sum:%d nsum:%d\n",sum,nsum);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int l=1;l<=k;l++)
				ans[l][i][j]%=mod,out=(out+(li)(qpow(nsum,w)-qpow(nsum+mod-ans[l][i][j],w)+mod)*inv%mod*v[i][j][l])%mod;
	printf("%d",out);
}
int main()
{
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&k,&w);
	// printf("n:%d m:%d k:%d w:%d\n",n,m,k,w);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int l=1;l<=k;l++)
				rd(mat[i][j][l]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int l=1;l<=k;l++)
				rd(v[i][j][l]);
	init();
	solve();
	cerr<<clock();
	return 0;
}