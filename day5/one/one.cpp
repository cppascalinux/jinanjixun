#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cassert>
#include<ctime>
#define bs 619
#define mod 1000000007
#define li long long
#define pii pair<int,int>
#define fi first
#define se second
#define modbs 1000003
using namespace std;
int n,m,tot;
int p[29],st[29],vis[29];
vector<int> v[1009];
int mat[1009][1009];
int hd[1000003],nxt[1000003];
pii eg[1000003];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
void gauss()
{
	// for(int i=1;i<=m;i++)
	// {
	// 	for(int j=1;j<=m+1;j++)
	// 		printf("%d ",mat[i][j]);
	// 	printf("\n");
	// }
	for(int i=1;i<=m;i++)
	{
		int t=i;
		for(int j=i+1;j<=m;j++)
			if(mat[j][i]>mat[t][i])
				t=j;
		if(t!=i)
			for(int k=i;k<=m+1;k++)
				swap(mat[i][k],mat[t][k]);
		int inv=qpow(mat[i][i],mod-2);
		for(int k=m+1;k>=i;k--)
			mat[i][k]=(li)mat[i][k]*inv%mod;
		for(int j=i+1;j<=m;j++)
			for(int k=m+1;k>=i;k--)
				mat[j][k]=(mat[j][k]-(li)mat[j][i]*mat[i][k]%mod+mod)%mod;
	}
	for(int i=m;i>=1;i--)
		for(int j=i+1;j<=m;j++)
			mat[i][m+1]=(mat[i][m+1]-(li)mat[i][j]*mat[j][m+1]%mod+mod)%mod;
	// for(int i=1;i<=m;i++)
	// {
	// 	for(int j=1;j<=m+1;j++)
	// 		printf("%d ",mat[i][j]);
	// 	printf("\n");
	// }
}
void dfs(int d,int val,int lst)
{
	if(val>=n)
	{
		if(val==n)
		{
			m++;
			for(int i=1;i<=d-1;i++)
				v[m].push_back(st[i]);
		}
		return;
	}
	for(int i=lst;i<=n;i++)
		st[d]=i,dfs(d+1,val+i,i);
}
int geths(vector<int> &v)
{
	int ans=0;
	for(int i=0;i<(int)v.size();i++)
		ans=((li)ans*bs+v[i])%mod;
	return ans;
}
void add(pii val)
{
	int rt=val.fi%modbs;
	eg[++tot]=val;
	nxt[tot]=hd[rt];
	hd[rt]=tot;
}
int fnd(int hs)
{
	int rt=hs%modbs;
	for(int i=hd[rt];i;i=nxt[i])
		if(eg[i].fi==hs)
			return eg[i].se;
	return 0;
}
void build()
{
	for(int i=1;i<=m;i++)
		add(pii(geths(v[i]),i));
}
void init(int x)
{
	int inv=qpow(n*(n-1)/2,mod-2);
	if(v[x].size()==n)
		return mat[x][x]=1,void();
	mat[x][x]=mod-1,mat[x][m+1]=mod-1;
	for(int i=0;i<(int)v[x].size();i++)
	{
		for(int j=i+1;j<(int)v[x].size();j++)
		{
			vector<int> nxt=v[x];
			nxt.erase(nxt.begin()+j);
			nxt.erase(nxt.begin()+i);
			nxt.push_back(v[x][i]+v[x][j]);
			sort(nxt.begin(),nxt.end());
			int id=fnd(geths(nxt));
			mat[x][id]=(mat[x][id]+(li)v[x][i]*v[x][j]%mod*inv)%mod;
		}
	}
	for(int i=0;i<(int)v[x].size();i++)
	{
		if(v[x][i]&1)
		{
			for(int j=1;j<=v[x][i]/2;j++)
			{
				vector<int> nxt=v[x];
				nxt[i]=j;
				nxt.push_back(v[x][i]-j);
				sort(nxt.begin(),nxt.end());
				int id=fnd(geths(nxt));
				mat[x][id]=(mat[x][id]+(li)v[x][i]*inv)%mod;
			}
		}
		else
		{
			for(int j=1;j<=v[x][i]/2;j++)
			{
				vector<int> nxt=v[x];
				nxt[i]=j;
				nxt.push_back(v[x][i]-j);
				sort(nxt.begin(),nxt.end());
				int id=fnd(geths(nxt));
				if(j<v[x][i]/2)
					mat[x][id]=(mat[x][id]+(li)v[x][i]*inv)%mod;
				else
					mat[x][id]=(mat[x][id]+(li)(v[x][i]/2)*inv)%mod;
			}
		}
	}
}
void getans()
{
	vector<int> tmp;
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			int x=i,sm=0;
			while(!vis[x])
				vis[x]=1,x=p[x],sm++;
			tmp.push_back(sm);
		}
	sort(tmp.begin(),tmp.end());
	// printf("tmp: ");
	// for(int i=0;i<(int)tmp.size();i++)
	// 	printf("%d ",tmp[i]);
	// printf("\n");
	int id=fnd(geths(tmp));
	// printf("id:%d\n",id);
	assert(id);
	printf("%d",mat[id][m+1]);
}
void dbg()
{
	for(int i=1;i<=m;i++)
	{
		printf("x:%d ",i);
		for(int j=0;j<(int)v[i].size();j++)
			printf("%d ",v[i][j]);
		printf("\n");
	}
	// for(int i=1;i<=m;i++)
	// 	printf("i:%d mat:%d\n",i,mat[i][m+1]);
}
int main()
{
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",p+i);
	dfs(1,0,1);
	// dbg();
	build();
	for(int i=1;i<=m;i++)
		init(i);
	gauss();
	getans();
	cerr<<clock();
	return 0;
}