#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

struct qwq{
	int from,to,nxt,ion;
};
qwq edge[200010];

int cnt,colour,m,q,n,flag,x,max_col;
int head[1100],num[1100],col[1100];

void addedge(int f,int t)
{
	edge[++ cnt].from = f;
	edge[cnt].to = t;
	edge[cnt].nxt = head[f];
	edge[cnt].ion = 1;
	head[f] = cnt;
}

void dfs(int now,int fa)
{
	num[colour] ++;
	col[now] = colour;
	for(int i = head[now];i;i = edge[i].nxt)
	{
		int to = edge[i].to;
		if(to == fa || edge[i].ion == 0 || col[to]) continue;
		dfs(to,now);
	}
}

int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout); 
	
	scanf("%d%d",&m,&q);
	n = (1 << m) - 1;
	while(q --)
	{
		scanf("%d%d",&flag,&x);
		if(flag == 1)
		{
			for(int i = 0;i <= n;i ++)
			{
				for(int j = i;j <= n;j ++)
				{
					if((i ^ j) == x) addedge(i,j),addedge(j,i);
				}
			}
		}
		else
		{
			for(int i = 0;i <= n;i ++)
			{
				for(int j = i;j <= n;j ++)
				{
					if((i ^ j) == x)
					{
						for(int k = head[i];k;k = edge[k].nxt)
							if(edge[k].to == j) edge[k].ion = 0;
						for(int k = head[j];k;k = edge[k].nxt)
							if(edge[k].to == i) edge[k].ion = 0;
					}
				}
			}
		}
		memset(num,0,sizeof(num));
		memset(col,0,sizeof(col));
		colour = 0;
		max_col = 0;
		for(int i = 0;i <= n;i ++)
		{
			if(!col[i]) 
			{
				colour ++;
				dfs(i,-1);
				max_col = max(max_col,num[colour]);
			}
		}
		printf("%d\n",max_col);
	}
	
	fclose(stdin);
	fclose(stdout);
	return ~~ (0 - 0);
}
