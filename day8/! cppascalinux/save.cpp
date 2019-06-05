#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m;
int s[100009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
namespace part1
{
	int buc0[256],buc8[256],buc16[256],buc24[256];
	int np[100009];
	void srt(int l,int r)
	{
		int *p=s+l-1,len=r-l+1;
		memset(buc0,0,sizeof(buc0));
		memset(buc8,0,sizeof(buc8));
		memset(buc16,0,sizeof(buc16));
		memset(buc24,0,sizeof(buc24));
		for(int i=1;i<=len;i++)
		{
			buc0[p[i]&255]++;
			buc8[p[i]>>8&255]++;
			buc16[p[i]>>16&255]++;
			buc24[p[i]>>24&255]++;
		}
		for(int i=1;i<=255;i++)
		{
			buc0[i]+=buc0[i-1];
			buc8[i]+=buc8[i-1];
			buc16[i]+=buc16[i-1];
			buc24[i]+=buc24[i-1];
		}
		for(int i=len;i>=1;i--)
			np[buc0[p[i]&255]--]=p[i];

		for(int i=len;i>=1;i--)
			p[buc8[np[i]>>8&255]--]=np[i];
			
		for(int i=len;i>=1;i--)
			np[buc16[p[i]>>16&255]--]=p[i];
			
		for(int i=len;i>=1;i--)
			p[buc24[np[i]>>24&255]--]=np[i];
	}
	void solve()
	{
		for(int i=1,a,b,c,d;i<=m;i++)
		{
			rd(a),rd(b),rd(c);
			if(a==1)
			{
				rd(d);
				for(int j=b;j<=c;j++)
					s[j]^=d;
			}
			else if(a==2)
				srt(b,c);
				// sort(s+b,s+c+1);
			else
			{
				int ans=0;
				for(int j=b;j<=c;j++)
					ans^=s[j];
				printf("%d\n",ans);
			}
		}
	}
}
namespace part2
{
	int c[2][100009];
	void add(int x,int val)
	{
		int d=x&1;
		for(;x<=n+1;x+=x&-x)
			c[d][x]^=val;
	}
	int ask(int x)
	{
		if(!x)
			return 0;
		int ans=0,d=x&1;
		for(;x;x-=x&-x)
			ans^=c[d][x];
		return ans;
	}
	void solve()
	{
		for(int i=1;i<=n;i++)
			add(i,s[i]^s[i-1]);
		for(int i=1,a,b,c,d;i<=m;i++)
		{
			rd(a),rd(b),rd(c);
			if(a==1)
			{
				rd(d);
				add(b,d),add(c+1,d);
			}
			else
			{
				int ans=ask(c)^ask(b-1);
				printf("%d\n",ans);
			}
		}
	}
}
int main()
{
	freopen("save.in","r",stdin);
	freopen("save.out","w",stdout);
	rd(n),rd(m);
	for(int i=1;i<=n;i++)
		rd(s[i]);
	if(n<=10000)
		part1::solve();
	else
		part2::solve();
	cerr<<clock();
	return 0;
}