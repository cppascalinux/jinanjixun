#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define db double
#define inf 0x7F7F7F7F
#define li long long
#define ppi pair<pt,int>
#define fi first
#define se second
using namespace std;
struct pt
{
	int x,y;
	pt(){}
	pt(int a,int b){x=a,y=b;}
	bool operator <(const pt &p) const{return x<p.x||(x==p.x&&y<p.y);}
	pt operator +(pt p){return pt(x+p.x,y+p.y);}
	pt operator -(pt p){return pt(x-p.x,y-p.y);}
	li operator ^(pt p){return (li)x*p.y-(li)y*p.x;}
	li cross(pt a,pt b){return (a-*this)^(b-*this);}
};
int n;
int f[59][59][59];
ppi s[59],st[59];
int ans[59],sm[59][59];
bool cmp(ppi x,ppi y)
{
	pt a=x.fi,b=y.fi;
	if(a.x==0&&a.y==0)
		return 1;
	if(b.x==0&&b.y==0)
		return 0;
	int dir=a^b;
	if(dir!=0)
		return dir>0;
	return a.x>b.x;
}
void solve(int x)
{
	int tp=0;
	for(int i=1;i<=n;i++)
		if(s[x].fi<s[i].fi)
			st[++tp]=s[i],st[tp].fi=st[tp].fi-s[x].fi;
	st[++tp]=ppi(pt(0,0),s[x].se);
	if(tp<3)
		return;
	sort(s+1,s+tp+1,cmp);
	printf("x:%d s[x].se:%d st[1].se:%d\n",x,s[x].se,st[1].se);
	memset(sm,0,sizeof(sm));
	for(int i=2;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			for(int k=i+1;k<=j-1;k++)
			{
				if(st[k].fi.cross(st[i].fi,st[j].fi)>0)
					sm[i][j]+=st[k].se;
			}
		}
	}
	memset(f,0x7F,sizeof(f));
	for(int i=2;i<=tp;i++)
		f[1][i][2]=st[1].se+st[i].se;
	for(int i=1;i<=tp;i++)
	{
		for(int j=i+1;j<=tp;j++)
		{
			for(int k=j+1;k<=tp;k++)
				if(st[i].fi.cross(st[j].fi,st[k].fi)>0)
				{
					for(int l=2;l<=tp-1;l++)
						f[j][k][l+1]=min(f[j][k][l+1],f[i][j][l]+st[k].se+sm[j][k]);
				}
		}
	}
	printf("tp:%d\n",tp);
	for(int i=1;i<=tp;i++)
		for(int j=i+1;j<=tp;j++)
			for(int k=3;k<=tp;k++)
				ans[k]=min(ans[k],f[i][j][k]);
}
int main()
{
	freopen("but.in","r",stdin);
	freopen("but.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&s[i].fi.x,&s[i].fi.y,&s[i].se);
	memset(ans,0x7F,sizeof(ans));
	for(int i=1;i<=n;i++)
		solve(i);
	for(int i=3;i<=n;i++)
		printf("%d ",ans[i]<inf?ans[i]:-1);
	return 0;
}