#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
namespace abc
{
	int n,m,qn,vis[1000005],a[1000005],mp[1000005],t=0,q[1000005],head,tail,ans=0;
	int c[1000005][2],f[1000005];
	void ins(int x)
	{
		for(int i=m-1;i>=0;i--)
			if(x&(1<<i))
			{
				if(!a[i]) 
				{
					a[i]=x;
					ans++;
					return;
				}
				else x^=a[i];
			}
	}
	void bfs(int s)
	{
		head=0,tail=1;
		q[1]=s;
		vis[s]=1;
		while(head<tail)
		{
			head++;
			int u=q[head];
			for(int i=1;i<=t;i++)
			{
				int v=(u^a[i]);
				if(vis[v]) continue;
				vis[v]=1;
				q[++tail]=v;
			}
		}
		ans=max(ans,tail);
	}
	void soe()
	{
		freopen("xor.in","r",stdin);
		freopen("xor.out","w",stdout);
		scanf("%d%d",&m,&qn);
		if(m<=10)
		{
			n=(1<<m);
			for(int i=1;i<=qn;i++)
			{
				int op,x;
				scanf("%d%d",&op,&x);
				if(op==1) 
				{
					a[++t]=x;
					mp[x]=t;
				}
				else
				{
					swap(a[mp[x]],a[t]);
					t--;
				}
				for(int i=0;i<n;i++)
					vis[i]=0;
				ans=0;
				for(int i=0;i<n;i++)
					if(!vis[i])
						bfs(i);
				printf("%d\n",ans);
			}
			return;
		}
		int fl1=1;
		for(int i=1;i<=qn;i++)
		{
			scanf("%d%d",&c[i][0],&c[i][1]);
			if(c[i][0]==2) fl1=0;
		}
		if(fl1)
		{
			for(int i=1;i<=qn;i++)
			{
				ins(c[i][1]);
				printf("%d\n",(1<<ans));
			}
			return;
		}
		else
		{
			for(int i=1;i<=qn;i++)
			{
				for(int j=0;j<=m;j++)
					a[j]=0;
				if(c[i][0]==1)
					f[++t]=c[i][1];
				else
				{
					for(int j=1;j<=t;j++)
						if(f[j]==c[i][1])
						{
							swap(f[j],f[t]);
							break;
						}
					t--;
				}
				ans=0;
				for(int j=1;j<=t;j++)
					ins(f[j]);
				printf("%d\n",(1<<ans));
			}
		}
	}
}
int main()
{
	abc::soe();
	return 0;
}
