
#include<cstdio>
#include<algorithm>
#include<queue>
#include<stack>
#include<cmath>
#include<cstring>
#define ll long long
#define maxn 505
#define re(i,a,b) for(int i=a;i<=b;i++)
#define for_edge(x) for(int i=head[x];i;i=e[i].nxt)
using namespace std;
inline int read(){char c=getchar();int f=1;int ans = 0;while(c>'9'||c<'0'){if(c=='-')f=-f;c=getchar();}while(c<='9'&&c>='0'){ans =ans*10+c-'0';c=getchar();}return ans*f;}
int head[maxn*maxn],TOT=1;
struct edge{int nxt,to;}e[maxn*maxn*2];
inline void add(int x,int y)
{//printf("%d %d\n",x,y);
e[++TOT].to = y ;e[TOT].nxt = head[x];head[x] = TOT; }

//_____________________________________________________________________________________________________
int n,m,a[maxn][maxn],tot,col[maxn][maxn],id[maxn][maxn],c[maxn*maxn];
pair<int,int> stand[maxn*maxn];
stack<int> st;
int dis[maxn*maxn],time[maxn*maxn],now=0,vis[maxn*maxn],able[maxn*maxn];
bool ans[maxn][maxn][maxn];
int mx=0 , mv = 1e9;
int exi[maxn*maxn];
const int x_to[4]{0,0,1,-1};
const int y_to[4]{1,-1,0,0};
#define xx x+x_to[i]
#define yy y+y_to[i]
#define fit (xx>=1&&xx<=n&&yy>=1&&yy<=m)
void build(int x,int y)
{
	re(i,0,3)
	if( fit&&col[x][y]==col[xx][yy]&&!id[xx][yy])
		{
			id[xx][yy] = id[x][y];
			build(xx,yy);
		}
}
int _vis[maxn][maxn];
void add_edge(int x,int y)
{
	_vis[x][y] = 1;
	re(i,0,3)
	if(fit)
	{
		if(id[x][y]==id[xx][yy])
		{
			if(!_vis[xx][yy])
				add_edge(xx,yy);
		}
		else if(!exi[id[xx][yy]])
		{
			st.push(id[xx][yy]);
			exi[id[xx][yy]] = 1;
			add(id[x][y],id[xx][yy]);
		}
	}
}
queue<int>q,Q;
inline void bfs(int s)
{
	
	/*TOT = _TOT;
	memcpy( head,_head,(tot+5)*sizeof(int));*/
	time[s]=++now;dis[s]=1; 
	/*re(i,1,tot)
		if(c[i])
		{
			if((i>>k)&1) add(0,i);
			else add(i,tot+1);
		}*/
	while(!q.empty() ) q.pop();
	q.push(s); 
	int M = 0;
	while(!q.empty() )
	{
		int x = q.front() ;q.pop() ;
		for_edge(x)
		{
			int y = e[i].to ;
			if(time[y]!=now)
			{
				q.push(y); 
				time[y] = now;
				dis[y] = dis[x] + 1 ;
				if(c[y]==1)M = max( M,dis[y] );
				if(c[y]==1&&dis[y]>=mv) return ;
			}
		}
	}
	mx = s ; mv = M;
		
}
int main()
{
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	n=read(),m=read();
	re(i,1,n)
		re(j,1,m)
		{
			char ch = getchar();
			while(ch!='0'&&ch!='1') ch = getchar();
			col[i][j] = (ch == '1');
			
		}
	re(i,1,n)
		re(j,1,m)
		if(!id[i][j]) 
		{
			id[i][j] = ++tot;
			c[tot] = col[i][j];
			stand[tot] = make_pair(i,j);
			build(i,j);
		}
		//return 0;
	re(i,1,tot)
	{
		add_edge(stand[i].first ,stand[i].second );
		while(!st.empty())
		{
			exi[st.top()] = 0;
			st.pop();
		}
	}/*
	re(i,1,n)
	{
		re(j,1,m)printf("%d ",id[i][j]);
		printf("\n");
	}*/
//	re(i,1,tot) printf("%d ",c[i]);
	re(i,1,tot)
		bfs(i);
	while(!q.empty() ) q.pop();
	q.push(mx);able[mx] = 1;
	printf("%d\n",mv);
	re(step,1,mv)
	{
		re(i,1,n)
		{
			re(j,1,m)
				ans[step][i][j] = able[id[i][j]];//printf("%d",);
			
			
		}
	//	re(i,1,tot)printf("%d",able[i]);	printf("\n");
		while(!q.empty() )
		{
			int x = q.front() ; q.pop() ;
		//	printf("%d\n",x);
			for_edge(x)
			{
				int y = e[i].to ;
				if(!able[y])
				{
				//	printf("	%d\n",y);
					able[y] = 1;
					Q.push(y); 
				}
			}
				// ;
		}
		swap(q,Q);
	}
	for(int step = mv;step;step--)
	{
		printf("%c\n",(mv-step)&1?'-':'+');
		re(i,1,n)
		{
			
			re(j,1,m) printf("%d",ans[step][i][j]);
			printf("\n");
		}
			
	}
		
	return 0;
}

