#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

const int M = 1000001;
int x,y,W,S,m,n,k,a[M],d[M][32],q,w[M];
map<int,int> mp;

void built(int*d,int k)
{
	for(int i=W;i>=0;i--)if((k>>i)&1)
	{
		if(!d[i]) {d[i]=k; return;}
		k^=d[i];
	}
}

int ask(int now,int l,int r,int x)
{
	if(l==r)
	{
		int k=0;
		for(int i=0;i<n;i++) if(d[now][i]) k++;
		return k;
	}
	int mid=(l+r)>>1;
	if(x<=mid) return ask(now*2,l,mid,x);
	return ask(now*2+1,mid+1,r,x);
}

void ins(int now,int l,int r,int L,int R,int z)
{
	if(L<=l && R>=r)
	{
		built(d[now],z);
		return;
	}
	int mid=(l+r)>>1;
	if(L<=mid) ins(now*2,l,mid,L,R,z);
	if(R>mid) ins(now*2+1,mid+1,r,L,R,z);
}

void rt(int now,int l,int r)
{
	if(l==r) return;
	for(int i=0;i<n;i++)
		if(d[now][i]) built(d[now*2],d[now][i]), built(d[now*2+1],d[now][i]);
	int mid=(l+r)>>1;
	rt(now*2,l,mid);
	rt(now*2+1,mid+1,r);
} 

int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	scanf("%d%d",&n,&q); W=n-1;
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&x,&y);
		if(y>=1<<n)continue;
		if(x==1) mp[y]=i, w[i]=y;
		else ins(1,1,q,mp[y],i-1,y), mp[y]=-1;
	}
	for(int i=1;i<=q;i++) if(w[i] && mp[w[i]]==i) ins(1,1,q,i,q,w[i]); 
	rt(1,1,q);
	for(int i=1;i<=q;i++)
		printf("%d\n",1<<ask(1,1,q,i));
}
