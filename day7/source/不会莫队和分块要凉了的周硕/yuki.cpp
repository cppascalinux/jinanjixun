#include<cstdio>
#include<iostream>
#include<cctype>
#include<queue>
#include<stack>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int N = 1e6 + 3;
vector <int> G[N];
int n,m,root,top;
int v[N],fa[N],deep[N],s[N],id[N];
int du[N];
struct io
{
	char ibuf[36000001] , * s , obuf[36000001] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "yuki.in" , "r" , stdin );
		freopen( "yuki.out" , "w" , stdout );
		fread( s = ibuf , 1 ,  36000001  , stdin );
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
	template < class
	 T >
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
//inline int read(){
//	int x;cin >>x;return x;	
//}
inline void dfs(int x,int f,int dep){
	deep[x] = dep;fa[x] = f;
	s[++top] = x;
	for(int i = 0;i < (int)G[x].size();++i){
		int y = G[x][i];
		if(y == f) continue;
		dfs(y,x,dep + 1);		
	}
}
inline int check(){
	int res;
	for(int i = 1;i <= n;++i) {
		if(du[i] > 2) return 0;
		if(du[i] == 1) res = i;
	}	
	return res;
}
inline void work1(){
	dfs(1,0,1);	
	while(m--){
		int opt = read();
		if(opt == 1){
			int x = read(),y = read(),z = read();
		//	printf("%d %d %d\n",x,y,z);
			if(deep[x] < deep[y]) swap(x,y);
			while(deep[x] != deep[y]) v[x] += z,x = fa[x];	
			if(x == y) {v[x] += z;continue;}
			while(x != y){
				v[x] += z;x = fa[x];
				v[y] += z;y = fa[y];
			}
			v[x] += z;
		}
		else{
			int x = read(),y = read();top = 0;
			for(int i = 0;i < (int)G[x].size();++i) s[++top] = v[G[x][i]];
			s[++top] = v[x];
			sort(s + 1,s + top + 1);print(s[y]);
		}
	}
}
struct tree{
	struct node{
		long long val;
		long long tag;
		int lc,rc;	
	}a[N << 1];
	int t = 1;
	inline void pushup(int u){a[u].val = a[a[u].lc].val + a[a[u].rc].val;}
	inline void build(int u,int l,int r){
		if(l == r) {a[u].val = s[l];return;}
		int mid = (l + r) >> 1;
		a[u].lc = ++t;build(a[u].lc,l,mid);
		a[u].rc = ++t;build(a[u].rc,mid + 1,r);
		pushup(u); 
	}
	inline void pushdown(int u,int l,int r){
		if(!a[u].tag) return ;
		int mid = (l + r) >> 1;
		a[a[u].lc].val += a[u].tag * (mid - l + 1);
		a[a[u].lc].tag += a[u].tag;
		a[a[u].rc].val += a[u].tag * (r - mid);
		a[a[u].rc].tag += a[u].tag;
		a[u].tag = 0;
	}
	inline void updata(int u,int l,int r,int ll,int rr,int w){
		if(l == ll && r == rr){a[u].val += w * (r - l + 1);a[u].tag += w;return;}
		pushdown(u,l,r);
		int mid = (l + r) >> 1;
		if(rr <= mid) updata(a[u].lc,l,mid,ll,rr,w);
		else if(ll > mid) updata(a[u].rc,mid + 1,r,ll,rr,w);
		else{
			updata(a[u].lc,l,mid,ll,mid,w);
			updata(a[u].rc,mid + 1,r,mid + 1,rr,w);
		}
		pushup(u);
	}
	inline long long query(int u,int l,int r,int x){
		if(l == r) return a[u].val;
		pushdown(u,l,r);	
		int mid = (l + r) >> 1;
		if(x <= mid) return query(a[u].lc,l,mid,x);
		else return query(a[u].rc,mid + 1,r,x); 
	}
}T;
inline void work2(){
	long long ss[4];
	dfs(root,0,1);
	for(int i = 1;i <= n;++i) id[s[i]] = i,s[i] = v[s[i]];
	T.build(1,1,n);
	while(m--){
		int opt = read();
		if(opt == 1){
			int x = read(),y = read(),z = read();
			int xx = min(id[x],id[y]),yy = max(id[x],id[y]);
			T.updata(1,1,n,xx,yy,z);
		}
		else{
			int x = read(),y = read();x = id[x];
			if(x == 1){
				long long xx = T.query(1,1,n,x);
			long long yy = T.query(1,1,n,x + 1);
			//	print(((y == 1) ? min(xx,yy) : max(xx,yy)));
				print((y == 1) ? min(xx,yy) : max(xx,yy));
			}
			else if(x == n){
			long long xx = T.query(1,1,n,x);
				long long yy = T.query(1,1,n,x - 1);
			//	print(((y == 1) ? min(xx,yy) : max(xx,yy)));
				print((y == 1) ? min(xx,yy) : max(xx,yy));
			}
			else{
				ss[1] = T.query(1,1,n,x);ss[2] = T.query(1,1,n,x + 1);ss[3] = T.query(1,1,n,x - 1);
				sort(ss + 1,ss + 4);
				print(ss[y]);
			//	print(ss[y]);
			}
		}
	}
}
int main(){
//	printf("%d\n",sizeof(ip) / 1204 / 1024);
	n = read();m = read();
	for(int i = 1;i <= n;++i) v[i] = read();
	for(int i = 1;i < n;++i){
		int x = read(),y = read();
		G[x].push_back(y);du[x]++;
		G[y].push_back(x);du[y]++;
	}
	if(n <= 2000) work1();
	else if(root = check()) work2();
//	else work3();
	return 0;	
}
