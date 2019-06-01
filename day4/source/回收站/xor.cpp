#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,q,top,ans,idx;
int edge[(1<<11)][(1<<11)],s[(1<<11)];
int dfn[(1<<11)],low[(1<<11)];
bool v[(1<<11)];
void tarjan(int x)
{
	dfn[x]=low[x]=++idx;
	s[++top]=x;
	v[x]=true;
	for(int i=0;i<=n;i++)
	{
		if(edge[x][i]==0) continue;
		if(!dfn[i])
		{
			tarjan(i);
			low[x]=min(low[x],low[i]);
		}
		else if(v[i]) low[x]=min(low[x],dfn[i]);
	}
	if(dfn[x]==low[x])
	{
		int cnt=0;
		while(1)
		{
			int t=s[top];
			top--;
			v[t]=false;
			cnt++;
			if(t==x) break;
		}
		ans=max(ans,cnt);
	}
}
int main()
{
	//freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	scanf("%d%d",&m,&q);
	n=(1<<m)-1;
	while(q--)
	{
		int opt,x;
		scanf("%d%d",&opt,&x);
		if(opt==1)
		{
			for(int i=0;i<=n;i++)
			{
				edge[i][x^i]++;
				edge[x^i][i]++;
			}
		}
		else
		{
			for(int i=0;i<=n;i++)
			{
				edge[i][x^i]--;
				edge[x^i][i]--;
			}
		}
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(v,false,sizeof(v));
		top=ans=idx=0;
		for(int i=0;i<=n;i++)
			if(!dfn[i]) tarjan(i);
		printf("%d\n",ans);	
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
