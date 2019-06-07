#include<cstdio>
#include<vector>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int INF=1000000007;
const int N=201010;
int dis2[N],col[N],dis[N],viss[N],l[N],ans,n;
struct Tree2
{
	vector<int>s[N],w[N],S[N],W[N];
	int g[N],xl[N],dfsx[N],fir[N],dep[N],f1[N][2],f2[N][2],g1[N][2],g2[N][2],up[N][21],pll[N][21],fa[N],d[N],q[N];
	int len,cnt,RT,WW,ans;
	long long D[N];
	void add(int x,int y)
	{
		s[x].push_back(y),s[y].push_back(x);
		long long dd=abs(D[x]-D[y]);
//		printf("%d %d %lld\n",x,y,dd);
		w[x].push_back(dd%INF),w[y].push_back(dd%INF);
	}
	void dfs(int x)
	{
		int c,i,y;
		xl[++len]=x,fir[x]=len,dep[len]=d[x];
		dfsx[x]=++cnt;
		c=S[x].size();
		for(i=0;i<c;i++)
		{
			y=S[x][i];
			if(fa[x]==y)
				continue;
			fa[y]=x;
			d[y]=d[x]+1;
			D[y]=D[x]+W[x][i];
			dfs(y);
			xl[++len]=x,dep[len]=d[x];
		}
	}
	int lca(int x,int y)
	{
		int l,r,tmp;
		l=fir[x],r=fir[y];
		if(l>r) swap(l,r);
		tmp=log2(r-l+1);
		if(up[l][tmp]<up[r-(1<<tmp)+1][tmp])
			return pll[l][tmp];
		return pll[r-(1<<tmp)+1][tmp];
	}
	void st()
	{
		int i,j;
		for(i=1;i<=len;i++)
			up[i][0]=dep[i],pll[i][0]=xl[i];
		for(j=1;j<=20;j++)
			for(i=1;i+(1<<j)-1<=len;i++)
				up[i][j]=min(up[i+(1<<j-1)][j-1],up[i][j-1]),
				pll[i][j]=(up[i][j]==up[i][j-1]?pll[i][j-1]:pll[i+(1<<j-1)][j-1]);
	}
	void cl(int n)
	{
		for(int i=1;i<=n;i++)
		{
			s[g[i]].clear();
			w[g[i]].clear();
			viss[g[i]]=0,dis2[g[i]]=0;
			col[g[i]]=0,dis[g[i]]=0;
			f1[g[i]][0]=f1[g[i]][1]=0;
			f2[g[i]][0]=f2[g[i]][1]=0;
			g1[g[i]][0]=g1[g[i]][1]=0;
			g2[g[i]][0]=g2[g[i]][1]=0;
		}
	}
	void dp(int x)
	{
		int c,i,y,j;
		c=s[x].size();
		for(i=0;i<c;i++)
		{
			y=s[x][i];
			if(fa[x]==y)
				continue;
			fa[y]=x;
			dp(y);
			for(j=0;j<2;j++)
			{
				f1[x][j]=(f1[x][j]+f1[y][j])%INF,f2[x][j]=(f2[x][j]+f2[y][j])%INF;
				g1[x][j]=(g1[x][j]+(long long)w[x][i]*f1[y][j]+g1[y][j])%INF;
				g2[x][j]=(g2[x][j]+(long long)w[x][i]*f2[y][j]+g2[y][j])%INF;
			}
//		printf("%d %d %d %d %d %d %d %d!%d\n",x,y,ans,dis[x],f1[y][0],f1[y][1],f2[y][0],f2[y][1],w[x][i]);
		}
		f1[x][col[x]]=(f1[x][col[x]]+dis[x])%INF,f2[x][col[x]]=(f2[x][col[x]]+dis2[x])%INF;
	}
	void dp2(int x,int w1,int w2,int w3,int w4)
	{
		int c,i,y,nw1,nw2,nw3,nw4;
		c=s[x].size();
		if(viss[x])
		{
			if(col[x]==1)
			{
				ans=(ans+(long long)WW*(g2[x][0]+w3))%INF;
				ans=(ans+(long long)dis[x]*(g2[x][0]+w3))%INF;
				ans=(ans+(long long)g1[x][0]+w1)%INF;
			}
			else
			{
				ans=(ans+(long long)WW*(g2[x][1]+w4))%INF;
				ans=(ans+(long long)dis[x]*(g2[x][1]+w4))%INF;
				ans=(ans+(long long)g1[x][1]+w2)%INF;
			}
		}
		for(i=0;i<c;i++)
		{
			y=s[x][i];
			if(fa[x]==y)
				continue;
			fa[y]=x;
			nw1=((long long)w1-g1[y][0]-(long long)f1[y][0]*w[x][i]%INF+INF+INF+(long long)(f1[RT][0]-f1[y][0]+INF)*w[x][i]+g1[x][0])%INF;
			nw2=((long long)w2-g1[y][1]-(long long)f1[y][1]*w[x][i]%INF+INF+INF+(long long)(f1[RT][1]-f1[y][1]+INF)*w[x][i]+g1[x][1])%INF;
			nw3=((long long)w3-g2[y][0]-(long long)f2[y][0]*w[x][i]%INF+INF+INF+(long long)(f2[RT][0]-f2[y][0]+INF)*w[x][i]+g2[x][0])%INF;
			nw4=((long long)w4-g2[y][1]-(long long)f2[y][1]*w[x][i]%INF+INF+INF+(long long)(f2[RT][1]-f2[y][1]+INF)*w[x][i]+g2[x][1])%INF;
			dp2(y,nw1,nw2,nw3,nw4);
		}
	}
	int build(int n,int w)
	{
		ans=0;
//		if(n==0) return;
		int h=0,i,pl=l[1],L,cnt=0;
//		long long mx=1000000000000000000;
		int mx=100000;
		sort(l+1,l+n+1,[&](int x,int y){return dfsx[x]<dfsx[y];});
		g[++cnt]=l[1];
		q[++h]=l[1];
//		vis[l[1]]=1;
		for(i=2;i<=n;i++)
		{
			L=lca(l[i],l[i-1]);
//			printf("%d %d %d\n",gg[i],gg[i-1],L); 
			g[++cnt]=l[i];
			if(d[L]<mx)
				mx=d[L],pl=L;
			while(h>0&&d[L]<d[q[h]])
			{
				if(d[L]>d[q[h-1]]||h==1)
					add(L,q[h]);
				else
					add(q[h],q[h-1]);
				h--;
			}
			if(q[h]!=L)
				g[++cnt]=L,q[++h]=L;
			q[++h]=l[i];
//			vis[gg[i]]=1;
		}
		while(h>1)
		{
			add(q[h],q[h-1]);
			h--;
		}
//		ans=-1000000000000000000;
		dp(pl);
		RT=pl;
		WW=w;
		dp2(pl,0,0,0,0);
		cl(cnt);
		return ans;
	}
}t2;
struct Tree1
{
	vector<int>s[N],w[N],pl[N];
	int X[N],Y[N],L[N],sz[N],z[N],fa[N],now,vis[N],pll[N],cntt;
	void add(int x,int y,int l)
	{
//		printf("%d %d %d||\n",x,y,l);
		now++;
		X[now]=x,Y[now]=y,L[now]=l;
		s[x].push_back(y),s[y].push_back(x);
		w[x].push_back(l),w[y].push_back(l);
		pl[x].push_back(now),pl[y].push_back(now);
	}
	void dfs(int x)
	{
		int c,i,y,mx=0;
		c=s[x].size();
		sz[x]=1;
//		printf("%d\n",x);
		for(i=0;i<c;i++)
		{
			y=s[x][i];
			if(fa[x]==y||vis[pl[x][i]])
				continue;
			fa[y]=x;
			dfs(y);
			sz[x]+=sz[y];
			if(sz[y]>=mx)
				mx=sz[y],z[x]=y,pll[x]=pl[x][i]; 
		}
		fa[x]=0;
	}
	int find_zx(int x,int n)
	{
		while(sz[z[x]]>n/2)
			x=z[x];
		return pll[x];
	}
	void dfs2(int x,int d,int co)
	{
		int c,i,y;
		c=s[x].size();
		if(x<=n)
			l[++cntt]=x,dis[x]=d,col[x]=co,dis2[x]=1,viss[x]=1;
		for(i=0;i<c;i++)
		{
			y=s[x][i];
			if(fa[x]==y||vis[pl[x][i]])
				continue;
			fa[y]=x;
			dfs2(y,(d+w[x][i])%INF,co);
		}
		fa[x]=0;
	}
	void bfz(int x)
	{
		int zx;
//		if(zx)
		dfs(x);
		if(sz[x]==1)
			return;
		zx=find_zx(x,sz[x]);
		vis[zx]=1;
		cntt=0;
//		printf("%d %d\n",X[zx],Y[zx]); 
		dfs2(X[zx],0,0),dfs2(Y[zx],0,1);
//		printf("%d\n",cntt);
		ans+=t2.build(cntt,L[zx]),ans%=INF;
//		printf("%d %d %d %d %d %d\n",x,zx,sz[x],X[zx],Y[zx],ans);
		bfz(X[zx]),bfz(Y[zx]);
	}
}t1;
struct Tree3
{
	vector<int>s[N],w[N];
	int fa[N],cnt;
	void build(int x)
	{
		int now=x,sum=0,c,i,y;
		c=s[x].size();
		for(i=0;i<c;i++)
		{
			y=s[x][i];
			if(fa[x]==y)
				continue;
			fa[y]=x;
			if(!sum)
				t1.add(now,y,w[x][i]);
			else
			{
				t1.add(now,++cnt,0);
				now=cnt;
				t1.add(now,y,w[x][i]);
			}
			sum++;
			build(y);
		}
	}
}t3;
int main()
{
	int i,x,y,l;
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d",&n);
	for(i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&l);
		t3.s[x].push_back(y);
		t3.s[y].push_back(x);
		t3.w[x].push_back(l);
		t3.w[y].push_back(l);
	}
	for(i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&l);
		t2.S[x].push_back(y);
		t2.S[y].push_back(x);
		t2.W[x].push_back(l);
		t2.W[y].push_back(l);
	}
	t3.cnt=n;
	t3.build(1);
//	printf("%d\n",t3.cnt);
	t2.dfs(1);
	t2.st();
//	puts("NO RE"); 
	t1.bfz(1);
	printf("%d\n",ans);
	return 0;
}

