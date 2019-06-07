#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define li long long
#define mod 1000000007
using namespace std;
int n,tot1,tot2,cnt1,cnt2;
int hd1[100009],eg1[200009],nxt1[200009],len1[200009];
int hd2[100009],eg2[200009],nxt2[200009],len2[200009];
li st1[200009],st2[200009];
int pos1[100009],pos2[100009];
li dep1[100009],dep2[100009];
int lg[200009];
li f1[21][200009],f2[21][200009];
void ins1(int a,int b,int c)
{
	eg1[++tot1]=b;
	len1[tot1]=c;
	nxt1[tot1]=hd1[a];
	hd1[a]=tot1;
}
void ins2(int a,int b,int c)
{
	eg2[++tot2]=b;
	len2[tot2]=c;
	nxt2[tot2]=hd2[a];
	hd2[a]=tot2;
}
void dfs1(int x,int fa)
{
	st1[++cnt1]=dep1[x];
	pos1[x]=cnt1;
	for(int i=hd1[x];i;i=nxt1[i])
		if(eg1[i]!=fa)
		{
			dep1[eg1[i]]=dep1[x]+len1[i];
			dfs1(eg1[i],x);
			st1[++cnt1]=dep1[x];
		}
}
void dfs2(int x,int fa)
{
	st2[++cnt2]=dep2[x];
	pos2[x]=cnt2;
	for(int i=hd2[x];i;i=nxt2[i])
		if(eg2[i]!=fa)
		{
			dep2[eg2[i]]=dep2[x]+len2[i];
			dfs2(eg2[i],x);
			st2[++cnt2]=dep2[x];
		}
}
void init()
{
	for(int i=1;i<=cnt1;i++)
		f1[0][i]=st1[i],f2[0][i]=st2[i];
	for(int k=1;k<=19;k++)
		for(int i=1;i<=cnt1-(1<<k)+1;i++)
		{
			f1[k][i]=min(f1[k-1][i],f1[k-1][i+(1<<(k-1))]);
			f2[k][i]=min(f2[k-1][i],f2[k-1][i+(1<<(k-1))]);
		}
	for(int i=2;i<=cnt1;i++)
		lg[i]=lg[i>>1]+1;
}
int getl1(int a,int b)
{
	int pa=pos1[a],pb=pos1[b];
	if(pa>pb)
		swap(pa,pb);
	int k=lg[pb-pa+1];
	li dl=min(f1[k][pa],f1[k][pb-(1<<k)+1]);
	return (dep1[a]+dep1[b]-2*dl)%mod;
}
int getl2(int a,int b)
{
	int pa=pos2[a],pb=pos2[b];
	if(pa>pb)
		swap(pa,pb);
	int k=lg[pb-pa+1];
	li dl=min(f2[k][pa],f2[k][pb-(1<<k)+1]);
	return (dep2[a]+dep2[b]-2*dl)%mod;
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,a,b,c;i<=n-1;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		ins1(a,b,c),ins1(b,a,c);
	}
	for(int i=1,a,b,c;i<=n-1;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		ins2(a,b,c),ins2(b,a,c);
	}
	dfs1(1,0),dfs2(1,0);
	init();
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			ans=(ans+(li)getl1(i,j)*getl2(i,j))%mod;
	printf("%d",ans*2%mod);
	cerr<<clock();
	return 0;
}