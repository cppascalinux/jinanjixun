#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;
struct edge
{
	int v,nxt;
}e[500005];
int n,m,a[100005],h[100005],t,c[100005];
//int bl,b[100005],bt=0,f[105][100005];
void add(int u,int v)
{
	e[++t].v=v;
	e[t].nxt=h[u];
	h[u]=t;
	c[u]++;
}
int main()
{
	freopen("busy.in","r",stdin);
	freopen("busy.out","w",stdout);
	scanf("%d%d",&n,&m);
	//bl=pow(n,2.0/3.0);
	//if(bl<1) bl=1;
	if(m==0) return 0;
	if(n==0)
	{
		for(int i=1;i<=m;i++)
		{
			int op,x,y;
			scanf("%d%d%d",&op,&x,&y);
			if(op==2)
			{
				printf("Chtholly\n");
			}
		}
		return 0;
	}
	//if(n<=1000&&m<=1000)
	{
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		int las=0;
		for(int i=1;i<=m;i++)
		{
			int op,x,y;
			scanf("%d%d%d",&op,&x,&y);
			x^=las,y^=las;
			if(op==1)
			{
				for(int i=1;i<=n;i++)
					if(a[i]==x) a[i]=y;
			}
			else
			{
				int p1=-1,p2=-1,ans=-1;
				for(int i=1;i<=n;i++)
				{
					if(a[i]==x) p1=i;
					if(a[i]==y) p2=i;
					if(p1!=-1&&p2!=-1) 
					{
						if(ans==-1) ans=abs(p1-p2);
						else ans=min(ans,abs(p1-p2));
					}
				}
				if(ans!=-1) printf("%d\n",ans),las=ans;
				else printf("Chtholly\n"),las=0;
			}
		}
		return 0;
	}
	return 0;
}
