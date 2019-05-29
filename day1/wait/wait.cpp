//2019.05.29
//有若干个区间,进行黑白染色,使得每个点被黑区间和白区间覆盖次数差绝对值<=1
//从区间左端点向右端点连边,转化成混合图欧拉回路,用网络流解决
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,tot;
int l[30009],r[30009],w[30009];
int v[60009];
int deg[60009];
void init()
{
	for(int i=1;i<=m;i++)
		v[++n]=l[i],v[++n]=r[i];
	sort(v+1,v+2*n+1);
	n=unique(v+1,v+2*n+1)-v-1;
	for(int i=1;i<=m;i++)
	{
		l[i]=lower_bound(v+1,v+n+1,l[i])-v;
		r[i]=lower_bound(v+1,v+n+1,r[i])-v;
	}
}
int main()
{
	freopen("wait.in","r",stdin);
	freopen("wait.out","w",stdout);
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",l+i,r+i,w+i);
	init();
	return 0;
}