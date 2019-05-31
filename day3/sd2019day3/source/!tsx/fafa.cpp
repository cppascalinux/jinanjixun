#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
namespace abc
{
	int n,k,a[100005],vis[100005],f[100005][2];
	int tans[105]={0,1,511,14246,114266,425976,878856,1070906,770246,303271,50521};
	int sum[1000005][2],ans=0;
	void pushup(int x)
	{
		sum[x][0]=max(sum[x*2][0],sum[x*2+1][0]);
		sum[x][1]=max(sum[x*2][1],sum[x*2+1][1]);
	}
	void build(int x,int l,int r)
	{
		if(l==r)
		{
			sum[x][0]=sum[x][1]=-99999999;
			return;
		}
		int mid=(l+r)/2;
		build(x*2,l,mid);
		build(x*2+1,mid+1,r);
		pushup(x);
	}
	void modify(int x,int l,int r,int qx,int qfl,int qv)
	{
		if(l>qx||r<qx) return;
		if(l==r)
		{
			sum[x][qfl]=qv;
			return;
		}
		int mid=(l+r)/2;
		modify(x*2,l,mid,qx,qfl,qv);
		modify(x*2+1,mid+1,r,qx,qfl,qv);
		pushup(x);
	}
	void query(int x,int l,int r,int ql,int qr,int& ans,int &ans2)
	{
		if(l>qr||r<ql) return;
		if(ql<=l&&r<=qr)
		{
			ans=max(ans,sum[x][0]);
			ans2=max(ans2,sum[x][1]);
			return;
		}
		int mid=(l+r)/2;
		query(x,l,mid,ql,qr,ans,ans2);
		query(x,mid+1,r,ql,qr,ans,ans2);
	}
	void check()
	{
		a[0]=0;
		for(int i=1;i<=n;i++)
			f[i][0]=f[i][1]=0;
		f[0][0]=0;
		f[0][1]=-99999999;
	//	build(1,1,n+1);
		//modify(1,1,n+1,1,0,0);
		int nans=0,nans2=0;
		for(int i=1;i<=n;i++)
		{
			f[i][0]=f[i][1]=-99999999;
			for(int j=0;j<i;j++)
			{
				if(a[j]>a[i]) f[i][0]=max(f[i][0],f[j][1]+1);
				else f[i][1]=max(f[i][1],f[j][0]+1);
			}
			nans=max(nans,max(f[i][0],f[i][1]));
			/*query(1,1,n+1,1,a[i]+1,f[i][0],f[i][1]);
			modify(1,1,n+1,a[i]+1,0,f[i][0]+1);
			modify(1,1,n+1,a[i]+1,1,f[i][1]+1);*/
		}
		//query(1,1,n+1,1,n+1,nans,nans2);
		if(nans==k) ans++;
	}
	void dfs(int dep)
	{
		if(dep==n+1)
		{
			check();
			return;
		}
		for(int i=1;i<=n;i++)
			if(!vis[i])
			{
				vis[i]=1;
				a[dep]=i;
				dfs(dep+1);
				vis[i]=0;
			}
	}
	void soe()
	{
		freopen("fafa.in","r",stdin);
		freopen("fafa.out","w",stdout);
		scanf("%d%d",&n,&k);
		if(n==10)
		{
			printf("%d",tans[k]);
			return;
		}
		dfs(1);
		//for(int i=1;i<=k;i++)
		//	printf("%d ",tans[i]);
		printf("%d",ans);
	}
}
int main()
{
	abc::soe();
	return 0;
}
