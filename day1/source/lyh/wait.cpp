#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
struct Seg{
	int l,r,id,col;
}seg[30010];
int a[30010];
int	c[30010];
void check()
{
	for(int i=1;i<=2*m;i++)
		c[i]=0;
	for(int i=1;i<=m;i++)
		c[seg[i].l]+=a[i],c[seg[i].r+1]-=a[i];
	for(int i=1;i<=2*m;i++)
	{
		c[i]+=c[i-1];
		if(c[i]<-1||c[i]>1)return ;
	}
	for(int i=1;i<=m;i++)
		if(a[i]>0)printf("1 ");
		else printf("0 ");
	printf("\n");
	fclose(stdin);fclose(stdout);
	exit(0);
}
void dfs(int x)
{
	if(x==m+1){
		check();
		return ;
	}
	if(seg[x].col!=1){
		a[x]=-1;
		dfs(x+1);
	}
	if(seg[x].col!=0){
		a[x]=1;
		dfs(x+1);
	}
	return ;
}
int tmp[60010];
bool cmp(Seg x,Seg y)
{
	return x.l<y.l;
}
int main()
{
	freopen("wait.in","r",stdin);
	freopen("wait.out","w",stdout);
	scanf("%d %d",&m,&n);
	bool flag=true;
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d %d",&seg[i].l,&seg[i].r,&seg[i].col);
		seg[i].id=i;
		tmp[i*2-1]=seg[i].l;
		tmp[i*2]=seg[i].r;
		if(seg[i].col!=-1)flag=false;
	}
	sort(tmp+1,tmp+m*2+1);
	for(int i=1;i<=m;i++)
		seg[i].l=lower_bound(tmp+1,tmp+m*2+1,seg[i].l)-tmp,
		seg[i].r=lower_bound(tmp+1,tmp+m*2+1,seg[i].r)-tmp;
	if(m<=20)
	{
		dfs(1);
		printf("-1\n");
		return 0;
	}
	printf("Why are you so strong?!\n");
	fclose(stdin);fclose(stdout);
	return 0;
}
