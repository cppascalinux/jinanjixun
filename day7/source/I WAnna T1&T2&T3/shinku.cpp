#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
using namespace std;
struct io
{
	char ibuf[40<<20] , * s , obuf[20<<20] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "shinku.in" , "r" , stdin );
		freopen( "shinku.out" , "w" , stdout );
		fread( s = ibuf , 1 ,  40<<20  , stdin );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
		fclose(stdin);fclose(stdout);
	}
	inline int read()
	{
		register int u = 0;
		while( * s < 48 ) s++;
		while( * s > 32 )
			u = (u<<1)+(u<<3) + ((* s++) ^ 48);
		return u;
	}
	template < class T >
	inline void print( register T u )
	{
		static int * q = a;
		if( !u ) * t++ = 48;
		else
		{
			while( u ) * q++ = u % 10 + 48 , u /= 10;
			while( q != a )
				* t++ = * --q;
		}
		* t++ = '\n';
	}
	inline void pc(register char u){
		* t++ = u;
	}
} ip;
#define read ip.read
#define print ip.print
#define pc ip.pc
/*
int mx[4000010],mn[4000010];
int lazy1[4000010],lazy2[4000010];
void pushdown(int root)
{
	if(lazy1[root]!=-1)lazy1[root<<1]=lazy1[root<<1|1]=mn[root<<1]=mn[root<<1|1]=lazy1[root];
	if(lazy2[root]!=-1)lazy2[root<<1]=lazy2[root<<1|1]=mx[root<<1]=mx[root<<1|1]=lazy2[root];
	lazy1[root]=lazy2[root]=-1;
	return ;
}
void build(int root,int l,int r)
{
	lazy1[root]=lazy2[root]=-1;
	if(l==r){
		mx[root]=r-1;
		mn[root]=l+1;
		return ;
	}
	int mid=(l+r)>>1;
	build(root<<1,l,mid);
	build(root<<1|1,mid+1,r);
	return ;
}
void change1(int root,int l,int r,int x,int y,int to)
{
	if(x<=l&&r<=y){
		mn[root]=to;
		lazy1[root]=to;
		return ;
	}
	pushdown(root);
	int mid=(l+r)>>1;
	if(x<=mid)change1(root<<1,l,mid,x,y,to);
	if(y>mid)change1(root<<1|1,mid+1,r,x,y,to);
	return ;
}
void change2(int root,int l,int r,int x,int y,int to)
{
	if(x<=l&&r<=y){
		mx[root]=to;
		lazy2[root]=to;
		return ;
	}
	pushdown(root);
	int mid=(l+r)>>1;
	if(x<=mid)change2(root<<1,l,mid,x,y,to);
	if(y>mid)change2(root<<1|1,mid+1,r,x,y,to);
	return ;
}
int query1(int root,int l,int r,int x)
{
	if(l==r)return mn[root];
	int mid=(l+r)>>1;
	pushdown(root);
	if(x<=mid)return query1(root<<1,l,mid,x);
	return query1(root<<1|1,mid+1,r,x);
}
int query2(int root,int l,int r,int x)
{
	if(l==r)return mx[root];
	int mid=(l+r)>>1;
	pushdown(root);
	if(x<=mid)return query2(root<<1,l,mid,x);
	return query2(root<<1|1,mid+1,r,x);
}*/
int L,R;
int sum[11];
int cnt[1000010];
inline void Add(int x,int to)
{
	cnt[x]+=to;
	if(to==1&&cnt[x]>1)return ;
	if(to==-1&&cnt[x]>0)return ;
	int a=x,b=x;
	bool flag=false,flag2=false;
	for(int i=0;i<=10;i++)
	{
		if(x-i==L||!cnt[x-i-1])
		{
			sum[i]-=to;
			a=x-i;
			flag=true;
			break;
		}
	}
	for(int i=0;i<=10;i++)
	{
		if(x+i==R||!cnt[x+i+1])
		{
			sum[i]-=to;
			b=x+i;
			flag2=true;
			break;
		}
	}
	if(flag&&flag2&&b-a+1<=10)sum[b-a+1]+=to;
	return ;
}
struct Query{
	int l,r,id,bl;
}q[1000010];
bool cmp(Query a,Query b)
{
	return a.bl==b.bl?((a.bl&1)?a.r>b.r:a.r<b.r):a.bl<b.bl;
}
int ans[1000010][11];
int a[1000010];
/*
vector<Query>vec[1010];
void solve(vector<Query>& V)
{
	sort(V.begin(),V.end(),cmp);
	for(int i=0;i<=10;i++)
		sum[i]=0;
	for(int i=L;i<=R;i++)
		cnt[i]=0;
	int nowl=1,nowr=0;
	for(int i=0;i<V.size();i++)
	{
		while(nowr<V[i].r)
		{
			nowr++;
			Add(a[nowr],1);
		}
		while(nowl>V[i].l)
		{
			nowl--;
			Add(a[nowl],1);
		}
		while(nowl<V[i].l)
		{
			Add(a[nowl],-1);
			nowl++;
		}
		for(int j=1;j<=10;j++)
			ans[V[i].id][j]=sum[j];
	}
	return ;
}
*/
int main()
{
	int n,m;L=1e9;R=-1;
	n=read();m=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		L=min(L,a[i]);
		R=max(R,a[i]);
	}
	int S=sqrt(n);
	for(int i=1;i<=m;i++)
	{
		int l,r;
		l=read();r=read();
		q[i]=(Query){l,r,i,l/S};
	}
//	for(int i=0;i*S<=n;i++)
//		solve(vec[i]);//cerr<<i<<"\n";
	sort(q+1,q+m+1,cmp);
	int nowl=1,nowr=0;
	for(int i=1;i<=m;i++)
	{
		while(nowr<q[i].r)
		{
			nowr++;
			Add(a[nowr],1);
		}
		while(nowr>q[i].r)
		{
			Add(a[nowr],-1);
			nowr--;
		}
		while(nowl>q[i].l)
		{
			nowl--;
			Add(a[nowl],1);
		}
		while(nowl<q[i].l)
		{
			Add(a[nowl],-1);
			nowl++;
		}
		for(int j=1;j<=10;j++)
			ans[q[i].id][j]=sum[j];
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=10;j++)
			pc(ans[i][j]%10+'0');
		pc('\n');
	}
	return 0;
}
