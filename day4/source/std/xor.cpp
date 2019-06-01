#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#define lson o<<1
#define rson o<<1|1
#define mid (l+r)/2
using namespace std;
int m,q,num,base[35][35];
vector<int>s[200005];
map<int,int>last;
set<int>ss;
void ins(int o,int l,int r,int from,int to,int v)
{
	if(l>=from&&r<=to)
	{
		s[o].push_back(v);
		return;
	}
	if(from<=mid)ins(lson,l,mid,from,to,v);
	if(to>mid)ins(rson,mid+1,r,from,to,v);
}
void ins(int*base,int v)
{
	for(int i=m-1;i>=0;i--)
	{
		if(((1<<i)&v)&&!base[i]){base[i]=v;break;}
		if((v^base[i])<v)v^=base[i];
	}
}
void solve(int dep,int o,int l,int r)
{
	for(int i=0;i<m;i++)base[dep][i]=base[dep-1][i];
	int n=(int)s[o].size();
	for(int i=0;i<n;i++)ins(base[dep],s[o][i]);
	if(l==r)
	{
		int num=0;
		for(int i=0;i<m;i++)
		  if(base[dep][i])num++;
		printf("%d\n",(1<<num));
		return;
	}
	solve(dep+1,lson,l,mid);
	solve(dep+1,rson,mid+1,r);
}
int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	scanf("%d%d",&m,&q);
	for(int i=1;i<=q;i++)
	{
		int type,x;
		scanf("%d%d",&type,&x);
		if(type==1)
		{
			last[x]=i;
			ss.insert(x);
		}
		else
		{
			ins(1,1,q,last[x],i-1,x);
			ss.erase(x);
		}
	}
	for(set<int>::iterator it=ss.begin();it!=ss.end();it++)ins(1,1,q,last[*it],q,*it);
	solve(1,1,1,q);
	return 0;
}
