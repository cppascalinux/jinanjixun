#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
#define N 210000
#define ls i<<1
#define rs i<<1|1
#define ll long long
#define INF 0x3f3f3f3f
map<int,int> Mp;
map<int,int>::iterator it;
struct Edge{
	int x,y,V,idx;
}E[N];
struct Link{
	int x,next;
}Lk[N*60];
int li[31][31],cs,ans[N],hd[N],sz[31],m;
inline void pushback(int x,int y) {Lk[++cs]=(Link){y,hd[x]};hd[x]=cs;}
inline void ins(int *li,int &sz,int x)
{
	for (int i=m-1;i>=0;--i)
		if (x&1<<i)
			if (li[i]) x^=li[i];
			else {li[i]=x;++sz;break;}
}
void insert(int i,int l,int r,int L,int R,int k)
{
	if (L<=l&&r<=R)
	{
		pushback(i,k);
		return;
	}
	int mid=l+r>>1;
	if (L<=mid) insert(ls,l,mid,L,R,k);
	if (mid<R) insert(rs,mid+1,r,L,R,k);
}
void solve(int o,int d,int l,int r)
{
	for (int j=hd[o];j;j=Lk[j].next) ins(li[d],sz[d],Lk[j].x);
	int mid=l+r>>1;
	if (l==r) {ans[l]=sz[d];return;}
	memcpy(li[d+1],li[d],sizeof(li[d]));sz[d+1]=sz[d];
	solve(o<<1,d+1,l,mid);
	memcpy(li[d+1],li[d],sizeof(li[d]));sz[d+1]=sz[d];
	solve(o<<1|1,d+1,mid+1,r);
}
inline int read(){
	int n=0;char a;bool z=false;
	while(a=getchar())
	{
		if (a>'9'||a<'0')
			if (z) break;
			else continue;
		if (!z) z=true;
		n=(n<<1)+(n<<3)+(a^48);
	}
	return n;
}
int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	m=read();int opt,Q=read(),x;
	for (int i=1;i<=Q;++i)
	{
		opt=read();
		switch(opt)
		{
			case 1:x=read();Mp[x]=i;break;
			case 2:x=read();insert(1,1,Q,Mp[x],i-1,x);Mp.erase(x);break;
		}
	}
	for (it=Mp.begin();it!=Mp.end();++it) insert(1,1,Q,it->first,Q,it->second);
	solve(1,1,1,Q);
	for (int i=1;i<=Q;++i) printf("%d\n",1<<ans[i]);
	return 0;
}

//by qlwpc
