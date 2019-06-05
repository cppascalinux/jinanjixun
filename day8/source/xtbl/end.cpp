#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int INF=1000000007;
int n;
int f[2][1010][9][2][3][2],h[1010][3];
int a[10],g[10][4],b[10];
char aa[10101];
struct Node
{
	int a[130][130];
	int h,l;
}A,F;
Node mul(Node x,Node y)
{
    Node z;
    int i,j,k;
    for(i=0;i<=x.h;i++)
        for(j=0;j<=y.l;j++)
        {
            z.a[i][j]=0;
            for(k=0;k<=x.l;k++)
                z.a[i][j]=(z.a[i][j]+(long long)x.a[i][k]*y.a[k][j])%INF;
        }
    z.h=x.h,z.l=y.l;
    return z; 
}
Node ksm(Node a,Node f,int x)
{
    while(x>0)
    {
        if(x%2==1)
            a=mul(a,f);
        x/=2;
        f=mul(f,f);
    }
    return a;
}
void add(int &x,int y)
{
	x+=y;
	if(x>=INF)
		x-=INF;
}
int solve(int x,int y)
{
	int l,i,tmp;
	for(l=1;l<n;l++)
		b[l]=!!((1<<l-1)&x);
	tmp=y;
	for(l=1;l<n;l++)
	{
		a[l]=tmp%3;
		tmp/=3;
	}
	tmp=0;
	for(i=1;i<n;i++)
	{
//		printf("%d %d %d()\n",i,a[i],b[i]);
		if(b[i]==0)
		{
			if(a[i]==2)
				return -1;
			else
				tmp+=(1<<i-1)*a[i];
		}
		else
			tmp+=(1<<i-1)*b[i];
	}
	return tmp;
}
int calc(int x,int y)
{
	if(!y) return x;
	return x+(1<<n-1);
}
int main()
{
	int K,len,all,i,j,k,l,x,y,nj,nx,tmp,X,Y,ans;
	freopen("end.in","r",stdin);
	freopen("end.out","w",stdout);
	scanf("%d%d",&n,&K);
	scanf("%s",aa+1);
	len=strlen(aa+1);
	all=1;
	for(i=1;i<n;i++)
	{
		for(j=1;j<=2;j++)
			g[i][j]=all*j;
		all*=3;
	}
//	cerr<<all<<endl;
//	printf("%d %d\n",g[2][2]);
	f[0][0][n][0][1][0]=1;
	for(i=1;i<=len;i++)
	{
//		if(i%1000==0)
//		cerr<<i<<endl;
		memset(f[i&1],0,sizeof(f[i&1]));
		for(j=0;j<all;j++)
		{
			for(l=0;l<=2;l++)
				f[i&1][j][1][0][l][0]=f[i&1][j][1][1][l][1]=(f[i-1&1][j][n][0][l][1]+f[i-1&1][j][n][0][l][0])%INF;
		}
		for(k=1;k<n;k++)
		{
			for(j=0;j<all;j++)
			{
				tmp=j;
				for(l=1;l<n;l++)
				{
					a[l]=tmp%3;
					tmp/=3;
				}
				for(l=0;l<=1;l++)
				{
					if(k==n-1)
					{
						for(y=0;y<=1;y++)
						{
							if(y==0)
								nj=j;
							else if(a[k]==0)
								nj=j-g[k][a[k]]+g[k][2];
							add(f[i&1][nj][k+1][l][0][0],f[i&1][j][k][l][0][y]);
							if(aa[i]=='1')
								nx=0;
							else
								nx=1;
							add(f[i&1][nj][k+1][l][nx][0],f[i&1][j][k][l][1][y]);
							add(f[i&1][nj][k+1][l][2][0],f[i&1][j][k][l][2][y]);
							
							if(y==1)
								nj=j;
							else if(a[k]==0)
								nj=j-g[k][a[k]]+g[k][1];
							add(f[i&1][nj][k+1][l^1][0][1],f[i&1][j][k][l][0][y]);
							if(aa[i]=='1')
								add(f[i&1][nj][k+1][l^1][1][1],f[i&1][j][k][l][1][y]);
							else
								add(f[i&1][nj][k+1][l^1][2][1],f[i&1][j][k][l][1][y]);
							add(f[i&1][nj][k+1][l^1][2][1],f[i&1][j][k][l][2][y]);
						}
					}
					else
					{
						for(x=0;x<=2;x++)
						{
							for(y=0;y<=1;y++)
							{
//								if(f[i&1][j][k][l][x][y]!=0)
//								{
									if(y==0)
										nj=j;
									else if(a[k]==0)
										nj=j-g[k][a[k]]+g[k][2];
									add(f[i&1][nj][k+1][l][x][0],f[i&1][j][k][l][x][y]);
									if(y==1)
										nj=j;
									else if(a[k]==0)
										nj=j-g[k][a[k]]+g[k][1];
									add(f[i&1][nj][k+1][l^1][x][1],f[i&1][j][k][l][x][y]);
//								}
							}
						}
					}
				}
			}
		}
	}
//	printf("%d|||\n",f[1][0][1][1][1][1]);
//	printf("%d|||\n",f[len&1][8][2][1][0][0]);
//	printf("%d\n",g[2][2]);
	for(i=0;i<all;i++)
		for(j=0;j<=2;j++)
		{
			for(k=0;k<=1;k++)
			{
//				printf("%d %d %d %d\n",i,j,k,f[len&1][i][n][0][j][k]);
				add(h[i][j],f[len&1][i][n][0][j][k]);
			}
//			printf("%d %d %d\n",i,j,h[i][j]);
		}
	for(i=0;i<(1<<n-1);i++)
		for(j=0;j<all;j++)
			for(k=0;k<=1;k++)
				for(l=0;l<=2;l++)
				{
					tmp=solve(i,j);
					if(tmp==-1)
						continue;
					X=calc(i,k);
					if(l<=1)
						Y=calc(tmp,k&l);
					else if(k==1)
						continue;
					else
						Y=calc(tmp,0);
//					printf("%d\n",solve(3,2));
//					if(X==3&&Y==3&&h[j][l])
//					printf("%d %d %d %d %d %d %d %d\n",i,j,tmp,X,Y,h[j][l],k,l);
					add(F.a[X][Y],h[j][l]);
				}
	F.h=F.l=(1<<n-1)*2-1;
//	cerr<<F.l;
	A.a[1][1<<n-1]=1;
	A.h=1,A.l=F.l;
//	printf("%d %d\n",F.h,F.l);
//	for(i=0;i<=F.h;i++)
//	{
//		for(j=0;j<=F.l;j++)
//			printf("%d ",F.a[i][j]);
//		puts("");
//	}
	A=ksm(A,F,K);
	ans=0;
	add(ans,A.a[1][(1<<n-1)-1]);
	printf("%d\n",ans);
	return 0;
}

