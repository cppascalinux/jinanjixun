#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

struct qwq{
	int nxt,to;
	qwq()
	{
		nxt = to = 0;
	}
};
qwq edge[2000010];

struct qaq{
	int val,fa,dep;
	qaq()
	{
		val = fa = dep = 0;
	}
};
qaq p[1000010];

int head[1000010],ls[1000010];
int cnt,n,m,f,t,x,y,z,flag;

void addedge(int f,int t)
{
	edge[++ cnt].nxt = head[f];
	edge[cnt].to = t;
	head[f] = cnt;
}

void dfs(int now,int fa)
{
	p[now].fa = fa;
	p[now].dep = p[fa].dep + 1;
	for(int i = head[now];i;i = edge[i].nxt)
	{
		int to = edge[i].to;
		if(to == fa) continue;
		dfs(to,now);
	}
}

void LCA(int x,int y,int z)
{
	if(p[x].dep > p[y].dep) swap(x,y);
	while(p[y].dep > p[x].dep)
	{
		p[y].val += z;
		y = p[y].fa;
	}
	while(x != y)
	{
		p[x].val += z;
		p[y].val += z;
		x = p[x].fa;
		y = p[y].fa;
	}
	p[x].val += z;
}

int main()
{
	freopen("yuki.in","r",stdin);
	freopen("yuki.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i ++)
		scanf("%d",&p[i].val);
	for(int i = 1;i < n;i ++)
	{
		scanf("%d%d",&f,&t);
		addedge(f,t);
		addedge(t,f);
	}
	if(n <= 1000 && m <= 1000)
	{
		dfs(1,0);
		for(int i = 1;i <= m;i ++)
		{
			scanf("%d",&flag);
			if(flag == 1)
			{
				scanf("%d%d%d",&x,&y,&z);
				LCA(x,y,z);
			}
			else
			{
				scanf("%d%d",&y,&z);
				int num = 0;
				ls[++ num] = p[y].val;
				for(int j = head[y];j;j = edge[j].nxt)
				{
					int to = edge[j].to;
					ls[++ num] = p[to].val;
				}
				sort(ls + 1,ls + num + 1);
				printf("%d\n",ls[z]);
			}
		}
	}
	else
	{
		
	}
	
	fclose(stdin);
	fclose(stdout);
	return ~~ (0 - 0);
}
