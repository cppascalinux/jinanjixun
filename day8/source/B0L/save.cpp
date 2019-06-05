#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
struct io
{
	char ibuf[ 4<<20 ] , * s , obuf[ 1<<20 ] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "save.in" , "r" , stdin );
		freopen( "save.out" , "w" , stdout );
		fread( s = ibuf , 1 ,  4<<20  , stdin );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
	}
	inline int read()
	{
		register int u = 0;
		while( * s < 48 ) s++;
		while( * s > 32 )
			u = ( u << 3 ) + ( u << 1 ) + ( ( * s++ ) ^ 48 );
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
} ip;

#define read ip.read
#define print ip.print
struct ST
{
	int key,tag;
}a[400003];
int n,m;
int s[100003]; 
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void push_up(int x){a[x].key=a[ls(x)].key^a[rs(x)].key;}
void build(int x,int l,int r)
{
	a[x].tag=0;
	if(l==r)
	{
		a[x].key=s[l];
		return;
	}
	int mid=(l+r)>>1;
	build(ls(x),l,mid);
	build(rs(x),mid+1,r);
	push_up(x);
}
void push_down(int x,int l,int r)
{
	int mid=(l+r)>>1;
	if((mid-l+1)&1) a[ls(x)].key^=a[x].tag;
	if((r-mid)&1) a[rs(x)].key^=a[x].tag;
	a[ls(x)].tag^=a[x].tag;
	a[rs(x)].tag^=a[x].tag;
	a[x].tag=0;
}
void modify1(int x,int l,int r,int nl,int nr,int k)
{
	if(nl<=l&&nr>=r)
	{
		if((r-l+1)&1) a[x].key^=k;
		a[x].tag^=k;
		return;
	}
	push_down(x,l,r);
	int mid=(l+r)>>1;
	if(nl<=mid) modify1(ls(x),l,mid,nl,nr,k);
	if(nr>mid) modify1(rs(x),mid+1,r,nl,nr,k);
	push_up(x);
}
void modify2(int x,int l,int r,int p,int k)
{
	if(l==r)
	{
		a[x].key=k;
		return;
	}
	push_down(x,l,r);
	int mid=(l+r)>>1;
	if(p<=mid) modify2(ls(x),l,mid,p,k);
	else modify2(rs(x),mid+1,r,p,k);
	push_up(x);
}
int query(int x,int l,int r,int nl,int nr)
{
	if(nl<=l&&nr>=r) return a[x].key;
	push_down(x,l,r);
	int res=0,mid=(l+r)>>1;
	if(nl<=mid) res^=query(ls(x),l,mid,nl,nr);
	if(nr>mid) res^=query(rs(x),mid+1,r,nl,nr);
	return res;
}
void rebuild(int l,int r)
{
	for(int i=l;i<=r;i++)
		s[i]=query(1,1,n,i,i);
	sort(s+l,s+r+1);
	for(int i=l;i<=r;i++)
		modify2(1,1,n,i,s[i]);	
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		s[i]=read();
	build(1,1,n);
	while(m--)
	{
		int opt=read(),l=read(),r=read();
		if(opt==1)
		{
			int x=read();
			modify1(1,1,n,l,r,x);
		}
		else if(opt==2) rebuild(l,r);
		else print(query(1,1,n,l,r));
	}
	return 0;
}
