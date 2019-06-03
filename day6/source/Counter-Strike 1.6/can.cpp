#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;

template <class nmsl> inline void read(nmsl &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}
char mp[10][10];
int color[10][10], n, m, k, xa[4]={0, 1, -1, 0}, ya[4]={1, 0, 0, -1}, visited[10][10];
ll ans;
inline int abs(int a){return a>0? a: -a;}
struct abc{
	int x, y;
}tp, tmp;
queue <abc> q;
inline int check(int anum, int bnum)
{
	if(abs(anum-bnum)>k)return 0;
	if(!anum || !bnum)return 0;
	int nmsl=0;
	for(R int i=1; i<=n; i++)
		for(R int j=1; j<=m; j++)
		{
			if(color[i][j] && color[i+1][j]==color[i][j] && color[i][j+1]==color[i][j] && color[i+1][j+1]==color[i][j])nmsl=1;
			visited[i][j]=0;
		}
	if(nmsl)return 0;
	int flag1=0, flag2=0;
	for(R int i=1; i<=n; i++)
	{
		for(R int j=1; j<=m; j++)
		{
			if(color[i][j]==1 && !flag1)
			{
				while(q.size())q.pop();
				tp.x=i, tp.y=j;
				q.push(tp);
				visited[i][j]=1;
				while(q.size())
				{
					tp=q.front(); q.pop();
					flag1++;
					for(R int i=0; i<=3; i++)
					{
						int gox=tp.x+xa[i], goy=tp.y+ya[i];
						if(gox<1 || gox>n || goy<1 || goy>m)continue;
						if(color[gox][goy]==1 && !visited[gox][goy])
						{
							tmp.x=gox, tmp.y=goy;
							visited[gox][goy]=1;
							q.push(tmp);
						}
					}
				}
			}
			if(color[i][j]==2 && !flag2)
			{
				while(q.size())q.pop();
				tp.x=i, tp.y=j;
				q.push(tp);
				visited[i][j]=1;
				while(q.size())
				{
					tp=q.front(); q.pop();
					flag2++;
					for(R int i=0; i<=3; i++)
					{
						int gox=tp.x+xa[i], goy=tp.y+ya[i];
						if(gox<1 || gox>n || goy<1 || goy>m)continue;
						if(color[gox][goy]==2 && !visited[gox][goy])
						{
							tmp.x=gox, tmp.y=goy;
							visited[gox][goy]=1;
							q.push(tmp);
						}
					}
				}
			}
		}
	}
	if(flag1!=anum || flag2!=bnum)return 0;
	return 1;
}
inline void dfs(int x, int y, int anum, int bnum)
{
	if(x==n+1){ans+=check(anum, bnum); return;}
	if(y==m)
	{
		if(mp[x][y]!='A')
		{
			color[x][y]=1;
			dfs(x+1, 1, anum+1, bnum);
		}
		if(mp[x][y]!='B')
		{
			color[x][y]=2;
			dfs(x+1, 1, anum, bnum+1);
		}
	}
	else 
	{
		if(mp[x][y]!='A')
		{
			color[x][y]=1;
			dfs(x, y+1, anum+1, bnum);
		}
		if(mp[x][y]!='B')
		{
			color[x][y]=2;
			dfs(x, y+1, anum, bnum+1);
		}
	}
}
int main()
{
	freopen("can.in", "r", stdin);
	freopen("can.out", "w", stdout);
	read(n), read(m), read(k);
	for(R int i=1; i<=n; i++)scanf("%s", mp[i]+1);
	dfs(1, 1, 0, 0);
	cout<<ans;
	return 0;
}
