#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,k,cnt;
pii ans[300009];
void mrg(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	mrg(l,mid);
	mrg(mid+1,r);
	ans[++cnt]=pii(mid+1,l);
}
int solve1()
{
	if(n<k)
		return cnt=-1,1;
	if(k==1)
		return 1;
	int bit=0;
	while(1<<bit<k)
		bit++;
	if(1<<bit==k)
		return mrg(1,k),1;
	if((k&1)&&n<k+2)
		return cnt=-1,1;
	if(!(k&1)&&n<k+1)
		return cnt=-1,1;
	return 0;
}
void solve2()
{
	int m=k+1+(k&1);
	int lb=1;
	int frm[30];
	memset(frm,0,sizeof(frm));
	for(int i=20;i>=0;i--)
		if(m>>i&1)
		{
			mrg(lb,lb+(1<<i)-1);
			frm[i]=lb;
			lb+=1<<i;
		}
	int mx=0;
	for(int i=0;i<=20;i++)
		if(frm[i])
			mx=i;
	// printf("m:%d mx:%d\n",m,mx);
	for(int i=0;i<=mx-1;i++)
		if(frm[i])
		{
			ans[++cnt]=pii(1,frm[i]);
			int tmp=i;
			while(frm[tmp])
			{
				if(!frm[tmp+1]||tmp+1==mx)
				{
					if(tmp+1!=mx)
					{
						frm[tmp+1]=frm[tmp];
					}
					// printf("i:%d tmp:%d\n",i,tmp);
					frm[tmp]=0;
					break;
				}
				else
				{
					ans[++cnt]=pii(frm[tmp],frm[tmp+1]);
					frm[tmp++]=0;
				}
			}
		}
	int p1=1,p2=1+(1<<mx),v1=m-(1<<mx),v2=1<<mx,inv=0;
	while(1)
	{
		if(v1==1)
		{
			if(k&1)
				ans[++cnt]=pii(p2,p1);
			inv=1;
			break;
		}
		if(v2==1)
		{
			if(k&1)
				ans[++cnt]=pii(p1,p2);
			break;
		}
		if(v1>v2)
		{
			ans[++cnt]=pii(p1,p2);
			v1-=v2,v2*=2;
		}
		else
		{
			ans[++cnt]=pii(p2,p1);
			v2-=v1,v1*=2;
		}
	}
	if(inv)
		for(int i=1;i<=cnt;i++)
		{
			if(ans[i].fi==p1)
				ans[i].fi=p2;
			else if(ans[i].fi==p2)
				ans[i].fi=p1;
			if(ans[i].se==p1)
				ans[i].se=p2;
			else if(ans[i].se==p2)
				ans[i].se=p1;
		}
}
int main()
{
	freopen("chemistry.in","r",stdin);
	freopen("chemistry.out","w",stdout);
	scanf("%d%d",&n,&k);
	if(!solve1())
		solve2();
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
		printf("%d %d\n",ans[i].fi,ans[i].se);
	return 0;
}