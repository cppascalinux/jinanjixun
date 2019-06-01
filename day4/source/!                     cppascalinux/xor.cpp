#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<ctime>
#define pii pair<int,int>
#define fi first
#define se second
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
int m,q;
struct node
{
	int v[31];
	node(){memset(v,0,sizeof(v));}
	void ins(int x)
	{
		for(int i=m-1;i>=0;i--)
			if((x>>i)&1)
			{
				if(v[i])
					x^=v[i];
				else
				{
					for(int j=0;j<=i-1;j++)
						if((x>>j)&1)
							x^=v[j];
					v[i]=x;
					for(int j=i+1;j<=m-1;j++)
						if((v[j]>>i)&1)
							v[j]^=x;
					break;
				}
			}
	}
	int getsm()
	{
		int sm=0;
		for(int i=0;i<=m-1;i++)
			if(v[i])
				sm++;
		return 1<<sm;
	}
};
char *p1,*p2,buffer[10000009];
vector<int> qs[400009];
node bs[400009];
int ans[100009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void add(int a,int l,int r,int ll,int rr,int val)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
		return qs[a].push_back(val),void();
	int mid=(l+r)>>1;
	add(a<<1,l,mid,ll,rr,val);
	add(a<<1|1,mid+1,r,ll,rr,val);
}
void dfs(int a,int l,int r,int d)
{
	// printf("a:%d l:%d r:%d\n",a,l,r);
	for(int i=0;i<(int)qs[a].size();i++)
	{
		bs[d].ins(qs[a][i]);
		// printf("%d ",qs[a][i]);
	}
	// printf("\n");
	if(l==r)
		return ans[l]=bs[d].getsm(),void();
	int mid=(l+r)>>1;
	bs[d+1]=bs[d];
	dfs(a<<1,l,mid,d+1);
	dfs(a<<1|1,mid+1,r,d);
}
int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	rd(m),rd(q);
	map<int,int> lst;
	map<int,int>::iterator it;
	for(int i=1,a,b;i<=q;i++)
	{
		rd(a),rd(b);
		if(a==1)
			lst[b]=i;
		else
		{
			add(1,1,q,lst[b],i-1,b);
			lst.erase(b);
		}
	}
	for(it=lst.begin();it!=lst.end();it++)
		add(1,1,q,it->se,q,it->fi);
	dfs(1,1,q,1);
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
	cerr<<clock();
	return 0;
}