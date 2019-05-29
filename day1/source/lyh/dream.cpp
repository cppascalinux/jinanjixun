#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define Mod 998244353
using namespace std;
inline void re(int& x)
{
	x=0;char c=getchar();
	while(c<'0'&&c>'9')c=getchar();
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c^'0');
		c=getchar();
	}
	return ;
}
int t[110][110][110];
int a[110][110][110],b[110][110][110];
int A[110][110][110];
int n,m,k,w;
int fpow(int a,int b)
{
	int ans=1,t=a;
	while(b)
	{
		if(b&1)ans=(long long)ans*t%Mod;
		t=(long long)t*t%Mod;
		b>>=1;
	}
	return ans;
}
inline void add(int& x,int y)
{
	x+=y;
	if(x>=Mod)x-=Mod;
	return ;
}
inline void dec(int& x,int y)
{
	x-=y;
	if(x<0)x+=Mod;
}
inline void Add(int x,int xx,int y,int yy,int z,int ad)
{
	add(t[x][y][z],ad);
	dec(t[xx+1][y][z],ad);
	dec(t[x][yy+1][z],ad);
	add(t[xx+1][yy+1][z],ad);
	return ;
}
int tmp[110];
int l[110],r[110];
int cnt=0;
void sol(int x,int xx,int y,int yy)
{
	for(int i=1;i<=k;i++)
	{
		tmp[i]=A[xx][yy][i]-A[x-1][yy][i]-A[xx][y-1][i]+A[x-1][y-1][i];
		if(!tmp[i])l[i]=l[i-1]+1;
		else l[i]=0;
		add(cnt,l[i]);
	}	
	r[k+1]=0;
	for(int i=k;i>=1;i--)
	{
		if(!tmp[i])r[i]=r[i+1]+1;
		else r[i]=0;
		Add(x,xx,y,yy,i,l[i]*r[i]);
	}
	return ;
}
int main()
{
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	scanf("%d %d %d %d",&n,&m,&k,&w);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int l=1;l<=k;l++)
			{
				scanf("%d",&a[i][j][l]),a[i][j][l]^=1;
				A[i][j][l]=A[i-1][j][l]+A[i][j-1][l]-A[i-1][j-1][l]+a[i][j][l];
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int l=1;l<=k;l++)
				scanf("%d",&b[i][j][l]);
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			for(int p=1;p<=m;p++)
				for(int q=p;q<=m;q++)
					sol(i,j,p,q);
	int all=((long long)n*(n+1)*m*(m+1)*k*(k+1)/8)%Mod;
	int ans=0;
//	printf("%d\n",cnt);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int l=1;l<=k;l++)
			{
				dec(t[i][j][l],t[i-1][j-1][l]);
				add(t[i][j][l],t[i-1][j][l]);
				add(t[i][j][l],t[i][j-1][l]);
				if(!a[i][j][l])add(ans,(long long)b[i][j][l]*(1-fpow((long long)(cnt-t[i][j][l]+Mod)%Mod*fpow(cnt,Mod-2)%Mod,w)+Mod)%Mod);
			}
	printf("%lld\n",(long long)ans*fpow((long long)cnt*fpow(all,Mod-2)%Mod,w)%Mod);
	return 0;
}
