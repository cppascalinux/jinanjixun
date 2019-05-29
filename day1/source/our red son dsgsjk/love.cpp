#include<cmath>
#include<set>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
struct node
{
	int to,next,w;
} e[10101001];
int n,m,tot,h[1010100];
inline void add(int from,int to,int w)
{
	e[++tot].next=h[from];
	h[from]=tot;
	e[tot].to=to;
	e[tot].w=w;
}
long long Ans=0;
namespace solve1
{
	long long f[3030][3030][2],tmp[3030][2];
	int sz[1010010];
	inline void DFS(int now,int fa)
	{
		int i,j,x;
		f[now][0][0]=0;
		f[now][1][1]=0;
		sz[now]=1;
		for(x=h[now]; x; x=e[x].next)
		{
			int to=e[x].to;
			if(to==fa) continue;
			DFS(to,now);
			memcpy(tmp,f[now],sizeof(tmp));
			for(i=0; i<=sz[now]; ++i)
			{
				for(j=0; j<=sz[to]; ++j)
				{
					if(i&&j)
						tmp[i+j-1][0]=max(tmp[i+j-1][0],f[now][i][1]+f[to][j][1]+e[x].w);
					if(i)
						tmp[i+j][1]=max(tmp[i+j][1],f[now][i][1]+f[to][j][0]);
					if(j)
						tmp[i+j][1]=max(tmp[i+j][1],f[now][i][0]+f[to][j][1]+e[x].w);
					tmp[i+j][0]=max(tmp[i+j][0],f[now][i][0]+f[to][j][0]);
				}
			}
			sz[now]+=sz[to];
			memcpy(f[now],tmp,sizeof(tmp));
		}
	}
	multiset<int> st;
	inline void mian()
	{
		int i,x;
		memset(f,-0x3f,sizeof(f));
		DFS(1,0);
		for(i=1; i<=m; ++i)
			f[1][i][0]=max(f[1][i-1][0],f[1][i][0]);
		long long Max=0,cnt=0,Sum=0;
		cout<<Ans-Max<<" ";
		for(i=1; i<=m; ++i)
		{
			scanf("%d",&x);
			if(cnt)
				if((*st.rbegin())>x)
				{
					st.insert(x);
					int y=*st.rbegin();
					Sum+=x-y;
					Max+=y-x;
					st.erase(st.find(y));
					swap(x,y);
				}
			if(Max<f[1][cnt+1][0]-Sum-x)
			{
				Max=f[1][cnt+1][0]-Sum-x;
				Sum+=x;
				cnt++;
				st.insert(x);
			}
			cout<<Ans-Max<<" ";
		}
	}
}
namespace solve2
{
	long long f[103000][5][2],tmp[5][2];
	int sz[1010010];
	inline void DFS(int now,int fa)
	{
		int x,i,j;
		f[now][0][0]=0;
		f[now][1][1]=0;
		sz[now]=1;
		for(x=h[now]; x; x=e[x].next)
		{
			int to=e[x].to;
			if(to==fa) continue;
			DFS(to,now);
			memcpy(tmp,f[now],sizeof(tmp));
			for(i=0; i<=min(sz[now],m); ++i)
			{
				for(j=0; j<=min(sz[to],m); ++j)
				{
					if(i&&j)
						tmp[i+j-1][0]=max(tmp[i+j-1][0],f[now][i][1]+f[to][j][1]+e[x].w);
					if(i)
						tmp[i+j][1]=max(tmp[i+j][1],f[now][i][1]+f[to][j][0]);
					if(j)
						tmp[i+j][1]=max(tmp[i+j][1],f[now][i][0]+f[to][j][1]+e[x].w);
					tmp[i+j][0]=max(tmp[i+j][0],f[now][i][0]+f[to][j][0]);
				}
			}
			sz[now]+=sz[to];
			memcpy(f[now],tmp,sizeof(tmp));
		}
	}
	multiset<int> st;
	inline void mian()
	{
		int i,x;
		memset(f,-0x3f,sizeof(f));
		DFS(1,0);
		for(i=1; i<=m; ++i)
			f[1][i][0]=max(f[1][i-1][0],f[1][i][0]);
		long long Max=0,cnt=0,Sum=0;
		cout<<Ans-Max<<" ";
		for(i=1; i<=m; ++i)
		{
			scanf("%d",&x);
			if(cnt)
				if((*st.rbegin())>x)
				{
					st.insert(x);
					int y=*st.rbegin();
					Sum+=x-y;
					Max+=y-x;
					st.erase(st.find(y));
					swap(x,y);
				}
			if(Max<f[1][cnt+1][0]-Sum-x)
			{
				Max=f[1][cnt+1][0]-Sum-x;
				Sum+=x;
				cnt++;
				st.insert(x);
			}
			cout<<Ans-Max<<" ";
		}
	}
}
multiset<int> st;
namespace solve3
{
	long long res[1101010];
	inline void mian()
	{
		res[0]=0;
		int i,j,x;
		for(i=1; i<=(n+1)/2; ++i)
		{
			res[i]=res[i-1];
			if(st.size()>=2)
			{
				int x=*st.rbegin();
				res[i]+=x;
				st.erase(st.find(x));
				x=*st.rbegin();
				res[i]+=x;
				st.erase(st.find(x));
			}
			else
			{
				int x=*st.rbegin();
				res[i]+=x;
				st.erase(st.find(x));
			}
		}
		for(i=1; i<=m; ++i)
			res[i]=max(res[i],res[i-1]);
		long long Max=0,cnt=0,Sum=0;
		cout<<Ans-Max<<" ";
		for(i=1; i<=m; ++i)
		{
			scanf("%d",&x);
			if(cnt)
				if((*st.rbegin())>x)
				{
					st.insert(x);
					int y=*st.rbegin();
					Sum+=x-y;
					Max+=y-x;
					st.erase(st.find(y));
					swap(x,y);
				}
			if(Max<res[cnt+1]-Sum-x)
			{
				Max=res[cnt+1]-Sum-x;
				Sum+=x;
				cnt++;
				st.insert(x);
			}
			cout<<Ans-Max<<" ";
		}
	}
}
int main()
{
	int u,v,w,i;
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1; i<n; ++i)
	{
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		Ans+=2*w;
		st.insert(w);
		add(v,u,w);
	}
	if(n<=3000)
	{
		solve1::mian();
		return 0;
	}
	if(m<=2)
	{
		solve2::mian();
		return 0;
	}
	solve3::mian();
	return 0;
}
