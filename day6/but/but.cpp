#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define li long long
#define ppi pair<pt,int>
#define fi first
#define se second
#define inf 0x7F7F7F7F
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
ppi sp[59];
pt p[59],st[59];
int ans[59];
int getcv(int m)
{
	int tp=0;
	for(int i=1;i<=m;i++)
	{
		while(tp>1&&st[tp-1].cross(st[tp],p[i])<=0)
			tp--;
		st[++tp]=p[i];
	}
	int tmp=tp;
	for(int i=m-1;i>=1;i--)
	{
		while(tp>tmp&&st[tp-1].cross(st[tp],p[i])<=0)
			tp--;
		st[++tp]=p[i];
	}
	return tp-1;
}
void solve(int s)
{
	int sm=0;
	for(int i=1;i<=n;i++)
		if((s>>(i-1))&1)
			p[++sm]=sp[i].fi;
	if(sm<3)
		return;
	int tp=getcv(sm);
	if(tp!=sm)
		return;
	int v=0;
	for(int i=1;i<=n;i++)
	{
		int fg=1;
		for(int j=1;j<=tp;j++)
			if(sp[i].fi.cross(st[j],st[j+1])<0)
			{
				fg=0;
				break;
			}
		if(fg)
			v+=sp[i].se;
	}
	ans[tp]=min(ans[tp],v);
}
int main()
{
	freopen("but.in","r",stdin);
	freopen("but.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&sp[i].fi.x,&sp[i].fi.y,&sp[i].se);
	sort(sp+1,sp+n+1);
	memset(ans,0x7F,sizeof(ans));
	for(int i=1;i<1<<n;i++)
		solve(i);
	for(int i=3;i<=n;i++)
		printf("%d ",ans[i]<inf?ans[i]:-1);
	cerr<<clock();
	return 0;
}