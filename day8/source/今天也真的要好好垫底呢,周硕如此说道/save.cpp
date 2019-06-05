#include<cstdio>
#include<iostream>
#include<cctype>
#include<algorithm>
using namespace std;
const int N = 1e5 + 3;
int c[N];int n,m;
struct io
{
	char ibuf[ 10000001 ] , * s , obuf[ 10000001 ] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "save.in" , "r" , stdin );
		freopen( "save.out" , "w" , stdout );
		fread( s = ibuf , 1 ,  10000001  , stdin );
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
			u = u * 10 + * s++ - 48;
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
struct tree{
	struct node{
		int sum,tag;
		int lc,rc;
	}a[N << 1];
	int t;
	inline void pushup(int u){a[u].sum = a[a[u].lc].sum ^ a[a[u].rc].sum;}
	inline void build(int u,int l,int r){
		if(l == r) {a[u].sum = c[l];return ;}
		int mid = (l + r) >> 1;
		a[u].lc = ++t;build(a[u].lc,l,mid);
		a[u].rc = ++t;build(a[u].rc,mid + 1,r);
		pushup(u);
	}
	inline void pushdown(int u,int l,int r){
		if(!a[u].tag) return;
		int mid = (l + r) >> 1;
		int ls = mid - l + 1,rs = r - mid;
		if(ls & 1) a[a[u].lc].sum ^= a[u].tag;
		a[a[u].lc].tag ^= a[u].tag;
		if(rs & 1) a[a[u].rc].sum ^= a[u].tag;
		a[a[u].rc].tag ^= a[u].tag;
		a[u].tag = 0; 
	}
	inline void updata(int u,int l,int r,int ll,int rr,int w){
		if(l == ll && r == rr){
			int ss = r - l + 1;
			if(ss & 1) a[u].sum ^= w;
			a[u].tag ^= w;
			return;
		}
		pushdown(u,l,r);int mid = (l + r) >> 1;
		if(rr <= mid) updata(a[u].lc,l,mid,ll,rr,w);
		else if(ll > mid) updata(a[u].rc,mid + 1,r,ll,rr,w);
		else{
			updata(a[u].lc,l,mid,ll,mid,w);
			updata(a[u].rc,mid + 1,r,mid + 1,rr,w);	
		}
		pushup(u);
	}
	inline int query(int u,int l,int r,int ll,int rr){
		if(l == ll && r == rr) return a[u].sum;
		pushdown(u,l,r);
		int mid = (l + r) >> 1;
		if(rr <= mid) return query(a[u].lc,l,mid,ll,rr);
		else if(ll > mid)  return query(a[u].rc,mid + 1,r,ll,rr);
		else return query(a[u].lc,l,mid,ll,mid) ^ query(a[u].rc,mid + 1,r,mid + 1,rr); 
	} 
}T;
int main(){
	n = read(),m = read();
	for(int i = 1;i <= n;++i) c[i] = read();
	if(n <= 10000){
		while(m--){
			int opt = read();	
			if(opt == 1){
				int l = read(),r = read(),x = read();
				for(int i = l;i <= r;++i) c[i] ^= x; 
			}
			if(opt == 2){
				int l = read(),r = read();
				sort(c + l,c + r + 1);	
			}
			if(opt == 3){
				int l = read(),r = read();int res = 0;
				for(int i = l;i <= r;++i) res ^= c[i];
				print(res);	
			}
		}
	}
	else{
		T.t = 1;
		T.build(1,1,n);
		while(m--){
			int opt = read();	
			if(opt == 1){
				int l = read(),r = read(),x = read();
				T.updata(1,1,n,l,r,x);
			}
			if(opt == 3){ 
				int l = read(),r = read();
				print(T.query(1,1,n,l,r));
			}
		}
	}
	return 0;	
}
