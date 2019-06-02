#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
const int mod=1e9+7;
int fpow(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1) ans=1ll*ans*x%mod;
		x=1ll*x*x%mod;
		y/=2;
	}
	return ans;
}
struct pt
{
	int sz,val[22];
	pt(){memset(val,0,sizeof(val));}
	bool operator <(const pt x) const
	{
		if(sz!=x.sz) return sz<x.sz;
		for(int i=1;i<=sz;i++)
			if(val[i]!=x.val[i])
				return val[i]<x.val[i];
		return 0;
	}
};
map<pt,int> mp;
pt fst[100005];
int cnt=0,n,b[1005];
void dfs(int dep,int sum,int maxn)
{
	if(sum>n) return;
	if(sum==n)
	{
		pt x;
		x.sz=dep-1;
		for(int i=1;i<=x.sz;i++)
			x.val[i]=b[i];
		fst[++cnt]=x;
		mp[x]=cnt;
		return;
	}
	for(int i=1;i<=min(n-sum,maxn);i++)
	{
		b[dep]=i;
		dfs(dep+1,sum+i,i);
	}
}
int getid(pt a,int x)
{
	for(int k=1;k<=a.sz;k++)
	{
		x-=a.val[k];
		if(x<=0) return k;
	}
}
bool cmp(const int x,const int y)
{
	return x>y;
}
int addmod(int x)
{
	return x>=mod?x-mod:x;
}
int submod(int x)
{
	return x<0?x+mod:x;
}
int h[1005][1005],g[1005],m;
void gauss()
{
	for(int i=1;i<=m;i++)
	{
		int nw=i;
		while(nw<=m&&h[nw][i]==0) nw++;
		if(nw==m+1) continue;
		int inv=fpow(h[i][i],mod-2);
		for(int j=1;j<=m;j++)
		{
			if(j==i) continue;
			int mul=1ll*inv*h[j][i]%mod;
			for(int k=i;k<=m+1;k++)
				h[j][k]=submod(h[j][k]-1ll*h[i][k]*mul%mod);
		}
	}
	for(int i=1;i<=m;i++)
		g[i]=1ll*h[i][m+1]*fpow(h[i][i],mod-2)%mod;
}
pt f;
int d[1000005],vis[1000005],tans[1000005],tt=0;
int main()
{
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	scanf("%d",&n);
	if(n==1)
	{
		printf("0");
		return 0;
	}
	dfs(1,0,99999);
	/*for(int i=1;i<=cnt;i++)
	{
		printf("%d\n",fst[i].sz);
		for(int j=1;j<=fst[i].sz;j++)
			printf("%d ",fst[i].val[j]);
		printf("\n");
	}*/
	//printf("cnt=%d\n",cnt);
	int inv=fpow(n*(n-1)/2,mod-2);
	for(int i=2;i<=cnt;i++)
	{
		f=fst[i];
		for(int j=1;j<=n;j++)
		{
			int x=getid(f,j);
			for(int k=j+1;k<=n;k++)
			{
				int y=getid(f,k);
				if(x==y)
				{
					f.sz++;
					f.val[f.sz]=k-j;
					f.val[x]=f.val[x]-(k-j);
					//print(f,"f==");
					sort(f.val+1,f.val+f.sz+1,cmp);
				}
				else
				{
					f.val[x]+=f.val[y];
					f.val[y]=f.val[f.sz];
					f.sz--;
					sort(f.val+1,f.val+f.sz+1,cmp);
				}
				//print(f,"f=");
				int v=mp[f];
				//printf("i=%d,v=%d\n",i,v);
				if(v==1) 
				{
					f=fst[i];
					continue;
				}
				h[i-1][v-1]=(h[i-1][v-1]+inv)%mod;
				f=fst[i];
			}
		}
		h[i-1][i-1]=mod-1;
		h[i-1][cnt]=mod-1;
	}
	m=cnt-1;
	gauss();
	//for(int i=0;i<cnt;i++)
	//	printf("%d ",g[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&d[i]);
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			int nw=i,sum=0;
			while(!vis[nw])
			{
				sum++;
				vis[nw]=1;
				nw=d[nw];
			}
			tans[++tt]=sum;
		}
	}
	sort(tans+1,tans+tt+1,cmp);
	f.sz=tt;
	memset(f.val,0,sizeof(f.val));
	for(int i=1;i<=tt;i++)
		f.val[i]=tans[i];
	g[0]=0;
	printf("%d",g[mp[f]-1]);
	return 0;
}
