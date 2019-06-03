#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;
namespace abc
{
	typedef long long ll;
	typedef struct pt
	{
		ll x,y;
		pt(ll x=0,ll y=0):x(x),y(y){}
	}vec;
	inline vec operator +(vec a,vec b)
	{
		return pt(a.x+b.x,a.y+b.y);
	}
	inline vec operator -(vec a,vec b)
	{
		return pt(a.x-b.x,a.y-b.y);
	}
	inline long long getcs(vec a,vec b)
	{
		return 1ll*a.x*b.y-1ll*a.y*b.x;
	}
	pt a[100005];
	int b[100005],q[100005],head,tail,tans[100005],cnt,vis[100005];
	pt c[100005],h[100005];
	inline bool cmp(const int xx,const int yy)
	{
		return h[xx].x<h[yy].x;
	}
	inline bool cmp2(const int xx,const int yy)
	{
		return a[xx].x<a[yy].x;
	}
	/*void gettb()
	{
		for(int i=1;i<=cnt;i++)
			b[i]=i;
		sort(b+1,b+cnt+1,cmp);
		for(int i=2;i<=cnt;i++)
			a[b[i]]=a[b[i]]-a[b[1]];
		sort(b+2,b+cnt+1,cmp2);
		for(int i=2;i<=cnt;i++)
			a[b[i]]=a[b[i]]+a[b[1]];
		q[1]=b[1];
		head=1,tail=1;
		b[cnt+1]=cnt+1;
		a[cnt+1]=a[b[1]];
		for(int i=2;i<=cnt+1;i++)
		{
			while(head<tail&&getcs(a[q[tail]]-a[q[tail-1]],a[b[i]]-a[q[tail]])<0) tail--;
			q[++tail]=b[i];
		}
		for(int i=1;i<=cnt+1;i++)
			vis[i]=0;
		for(int i=head;i<tail;i++)
			vis[q[i]]=1;
	}*/
	void gettb()
	{
		for(int i=1;i<=cnt;i++)
			b[i]=i;
		//ort(b+1,b+cnt+1,cmp2);
		q[1]=b[1];
		head=1,tail=1;
		for(int i=2;i<=cnt;i++)
		{
			while(head<tail&&getcs(a[q[tail]]-a[q[tail-1]],a[b[i]]-a[q[tail]])<0) tail--;
			q[++tail]=b[i];
		}
		//printf("cnt=%d\n",cnt);
		for(int i=1;i<=cnt;i++)
			vis[i]=0;
		//for(int i=1;i<=tail;i++)
		//	printf("%d ",q[i]);
		//printf("\n");
		for(int i=head+1;i<tail;i++)
			vis[q[i]]=1;
		q[1]=b[1];
		head=1,tail=1;
		for(int i=2;i<=cnt;i++)
		{
			while(head<tail&&getcs(a[q[tail]]-a[q[tail-1]],a[b[i]]-a[q[tail]])>0) tail--;
			q[++tail]=b[i];
		}
		//for(int i=1;i<=tail;i++)
		//	printf("%d ",q[i]);
		//printf("\n");
		for(int i=head+1;i<tail;i++)
			vis[q[i]]=1;
		vis[q[head]]=vis[q[tail]]=1;
	}
	int n,m,sum[2000005],f[2000005],ttans[2000005],g[100005],tg[100005];
	void soe()
	{
		freopen("but.in","r",stdin);
		freopen("but.out","w",stdout);
		memset(ttans,0x3f,sizeof(ttans));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%lld%lld%d",&c[i].x,&c[i].y,&g[i]),h[i]=c[i],tg[i]=g[i];
		for(int i=1;i<=n;i++)
			b[i]=i;
		sort(b+1,b+n+1,cmp);
		for(int i=1;i<=n;i++)
		{
			c[i]=h[b[i]];
			g[i]=tg[b[i]];
		}
		sum[0]=0;
		for(int i=1;i<(1<<n);i++)
		{
			sum[i]=sum[i/2]+(i%2);
			if(sum[i]<3) continue;
			cnt=0;
			for(int j=1;j<=n;j++)
				if((1<<(j-1))&i)
					a[++cnt]=c[j];
			gettb();
			int nw=0,nw2=1,nww=0,vsum=0;
			for(int j=1;j<=n;j++)
				if((1<<(j-1))&i)
				{
					nw++;
					if(vis[nw])	nww|=(1<<(j-1));
					vsum+=g[j];
				}
			//printf("i=%d,nww=%d\n",i,nww);
			f[nww]=max(f[nww],vsum);
		}
		for(int i=1;i<(1<<n);i++)
			if(f[i]!=0)
			{
				ttans[sum[i]]=min(ttans[sum[i]],f[i]);
			}
		for(int i=3;i<=n;i++)
			if(ttans[i]!=0x3f3f3f3f) printf("%d ",ttans[i]);
			else printf("-1 ");
		return;
	}
}
int main()
{
	abc::soe();
	return 0;
}
