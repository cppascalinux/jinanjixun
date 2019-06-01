#include<cstdio>
#define N 120000
int a[N],pf[2][N],sf[2][N];
inline int read(){
	int n=0;char a;bool z=false;
	while(a=getchar())
	{
		if (a>'9'||a<'0')
			if (z) break;
			else continue;
		if (!z) z=true;
		n=(n<<1)+(n<<3)+(a^48);
	}
	return n;
}
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int T=read(),n,m,c0;
	while(T--)
	{
		n=read();m=read();c0=0;
		for (int i=1;i<=n;++i) a[i]=read()&1;
		if (((n^m)&1)==0) goto WA;
		if (!m)
		{
			for (int i=1;i<=n;++++i) if (~a[i]&1) goto WA;
			goto WB;
		}else
		{
			for (int i=1;i<n;++i)
			{
				if (a[i]==0&&a[i+1]==0) ++c0;
				if (c0==2) goto WA;
			}
			pf[1][1]=a[1]==1;pf[0][0]=1;
			for (int i=2;i<=n;++i) pf[i&1][i]=pf[i&1][i-2]&a[i]==1;
			sf[n&1][n]=a[n]==1;sf[n&1^1][n-1]=a[n-1]==1;
			for (int i=n-2;i;--i) sf[i&1][i]=sf[i&1][i+2]&a[i]==1;
			for (int i=1;i<=n;++i) 
				if (a[i]==0&&a[i+1]==0)
				{
				//	if (i&1&&(pf[1][i-2]||i==1)&&(sf[0][i+3]||i+3>n)) goto WB;
					if (~i&1&&pf[1][i-1]&&(sf[0][i+2]||i+2>n)) goto WB;
				}else 
				{
					if (i&1&&(pf[1][i-2]||i==1)&&(sf[0][i+3]||i+3>n)) goto WB;
					if (~i&1&&pf[1][i-1]&&(sf[0][i+2]||i+2>n)) goto WB;
				}
			goto WA;
		}
		WB:printf("B\n");continue;
		WA:printf("A\n");continue;
	}
	return 0;
}
