#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
int m,q;
struct M{
	int a[30];
	void insert(int x)
	{
		for(int i=m-1;i>=0;i--)
			if(x&(1<<i))
			{
				if(a[i])x^=a[i];
				else{
					a[i]=x;
					return ;
				}
			}
	}
	int count()
	{
		int x=0;
		for(int i=0;i<m;i++)
			x+=(bool)a[i];
		return x;
	}
	void clear()
	{
		memset(a,0,sizeof(a));
		return ;
	}
}t[400010];
M operator +(M a,const M& b)
{
	for(int i=0;i<m;i++)
		if(b.a[i])a.insert(b.a[i]);
	return a;
}
void Ins(int root,int l,int r,int x,int y)
{
	t[root].insert(y);
	if(l==r)return ;
	int mid=(l+r)>>1;
	if(x<=mid)Ins(root<<1,l,mid,x,y);
	else Ins(root<<1|1,mid+1,r,x,y);
	return ;
}
void del(int root,int l,int r,int x)
{
	if(l==r)
	{
		t[root].clear();
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid)del(root<<1,l,mid,x);
	else del(root<<1|1,mid+1,r,x);
	t[root]=t[root<<1]+t[root<<1|1];
	return ;
}
map<int,int>mp;
int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	scanf("%d %d",&m,&q);
	int cur=0;
	for(int i=1;i<=q;i++)
	{
		int op,x;
		scanf("%d %d",&op,&x);
		if(op==1)
		{
			cur++;
			mp[x]=cur;
			Ins(1,1,q,cur,x);
		}
		else del(1,1,q,mp[x]);
		printf("%d\n",1<<t[1].count());
	}
	fclose(stdin);fclose(stdout);
	return 0;
}
/*
30 4
1 3
1 1
2 3
2 1

*/
