#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,k,p[15],f[15][2],res;
bool flag[15];
void check()
{
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		f[i][0]=1,f[i][1]=-1000000000;
		for(int j=1;j<i;j++)
		{
			if(p[j]<p[i])f[i][0]=max(f[i][0],f[j][1]+1);
			else f[i][1]=max(f[i][1],f[j][0]+1);
		}
		ans=max(ans,f[i][1]);
		ans=max(ans,f[i][0]);
	}
	if(ans==k)res++;
}
void dfs(int step)
{
	if(step>n)return check();
	for(int i=1;i<=n;i++)
	{
		if(flag[i])continue;
		flag[i]=1;
		p[step]=i;
		dfs(step+1);
		flag[i]=0;
	}
}
int main()
{
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	scanf("%d%d",&n,&k);
	dfs(1);
	printf("%d\n",res);
	return 0;
}
