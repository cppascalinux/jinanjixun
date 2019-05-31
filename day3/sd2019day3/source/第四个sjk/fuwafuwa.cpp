#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int lc[1010],rc[1010],dep[1010],val[1010];
int ins(int x,int y,int d)
{
	dep[y]=d;
	if(!x) return y;
	if(val[x]>val[y])
		lc[x]=ins(lc[x],y,d+1);
	else
		rc[x]=ins(rc[x],y,d+1);
	return x;
}
int main()
{
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
	int T,a,b,n,m,i,rt;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&a,&b,&m,&n);
		rt=0;
		for(i=1;i<=n;i++)
		{
			val[i]=(a+(long long)b*i)%m;
			rt=ins(rt,i,0);
		}
		printf("%d\n",dep[n]);
		memset(lc,0,sizeof(lc));
		memset(dep,0,sizeof(dep));
		memset(rc,0,sizeof(rc));
	}
	return 0;
}

