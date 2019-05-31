#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
namespace abc
{
	typedef long long ll;
	int t,n,m,a,b,val[1005],c[1005],len,ls[1005],rs[1005],rt=0,f[1005];
	int vis[5000005],vt,tval[5000005];
	int ins(int x,int y)
	{
		if(!x) return y;
		if(val[x]>val[y]) 
		{
			ls[x]=ins(ls[x],y);
			f[ls[x]]=x;
		}
		else 
		{
			rs[x]=ins(rs[x],y);
			f[rs[x]]=x;
		}
		return x;
	}
	int getd(int x)
	{
		int ans=0;
		while(x!=rt)
		{
			x=f[x];
			ans++;
		}
		return ans;
	}
	void soe()
	{
		freopen("fuwafuwa.in","r",stdin);
		freopen("fuwafuwa.out","w",stdout);
		scanf("%d",&t);
		while(t--)
		{
			scanf("%d%d%d%d",&a,&b,&m,&n);
			/*if(n<=500)
			{
				rt=0;
				memset(c,0,sizeof(c));
				memset(val,0,sizeof(val));
				memset(ls,0,sizeof(ls));
				memset(rs,0,sizeof(rs));
				for(int i=1;i<=n;i++)
				{
					val[i]=(a+1ll*b*i%m)%m;
					c[i]=val[i];
				}
				sort(c+1,c+n+1);
				len=unique(c+1,c+n+1)-c-1;
				for(int i=1;i<=n;i++)
					val[i]=lower_bound(c+1,c+len+1,val[i])-c;
				for(int i=1;i<=n;i++)
					rt=ins(rt,i);
				printf("%d\n",getd(n));
			}*/
			if(n<=500)
			{
				memset(val,0,sizeof(val));
				for(int i=1;i<=n;i++)
					val[i]=(a+1ll*b*i%m)%m;
				int l=0,r=m,ans=-1;
				for(int i=1;i<=n;i++)
					if(val[i]>=l&&val[i]<r)
					{
						ans++;
						if(val[n]>=val[i]) l=val[i];
						else r=val[i];
					}
				printf("%d\n",ans);
				continue;
			}
			if(m<=1000000)
			{
				vt=n;
				for(int i=1;i<=n;i++)
				{
					int nw=(a+1ll*b*i%m)%m;
					if(vis[nw])
					{
						vt=i-1;
						break;
					}
					vis[nw]=1;
					tval[i]=nw;
				}
				//printf("vt=%d\n",vt);
				for(int i=1;i<=vt;i++)
					vis[tval[i]]=0;
				int l=0,r=m,ans=-1,nval=(a+1ll*b*n%m)%m;
				for(int i=1;i<=vt;i++)
					if(tval[i]>=l&&tval[i]<r)
					{
						ans++;
						if(nval>=tval[i]) l=tval[i];
						else r=tval[i];
					}
				printf("%d\n",ans+(n-1)/vt);
			}
		}
	}
}
int main()
{
	abc::soe();
	return 0;
}
