#include<bits/stdc++.h>
#define to edge[i].v
#define mp make_pair
#define rint register int
#define fgx cerr<<"-------------"<<endl
#define N 1000010
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
void dbg(){cerr<<endl;}	
template<typename A,typename... B>void dbg(A x,B... y){cerr<<x<<" ";dbg(y...);}
#define debug(...) cerr<<#__VA_ARGS__<<"=",dbg(__VA_ARGS__)
namespace IO
{	const int __S=1e7;char __buf[__S],*__H,*__T;
	inline char getc()
	{	if(__H==__T) __T=(__H=__buf)+fread(__buf,1,__S,stdin);
		if(__H==__T) return -1;return *__H++;
	}
	template <class __I>inline void read(__I &__x)
	{	char __c=getc(); while(!isdigit(__c)) __c=getc();
		for(__x=0;isdigit(__c);__c=getc()) __x=__x*10+(__c^'0');
	}
	char __obuf[__S],*__oS=__obuf,*__oT=__oS+__S-1,__c,__qu[55];int __qr;
	inline void flush(){fwrite(__obuf,1,__oS-__obuf,stdout);__oS=__obuf;}
	inline void putc(char __x){*__oS++ =__x;if(__oS==__oT) flush();}
	template <class __I>inline void print(__I __x)
	{	if(!__x) putc('0');
		while(__x) __qu[++__qr]=__x%10^'0',__x/=10;
		while(__qr) putc(__qu[__qr--]);
	}
	inline void el(){putc('\n');}inline void sp(){putc(' ');}
}using namespace IO;
int a[N],la[N],ans[N][10],t[N][10],n,vis[N*50];
struct Q{int l,r,id;}q[N];
inline void ADD(int x,int y,int g){for(--y;x<=n;x+=x&-x)(t[x][y]+=g)%=10;}
#define add(A,B,C) ADD(A,C,1),ADD(B+1,C,-1)
#define del(A,B,C) ADD(A,C,-1),ADD(B+1,C,1)
inline int cmp(Q x,Q y){return x.r<y.r;}
inline void query(int x,int *_){for(;x;x-=x&-x)for(rint i=0;i<10;i++)(_[i]+=t[x][i])%=10;}
struct fuck{int l,r,k,id;}; vector<fuck> v[N];
int main()
{	freopen("shinku.in","r",stdin);
	freopen("shinku.out","w",stdout);
	int m,gg=0; cin>>n>>m;
	for(rint i=1;i<=n;i++) read(a[i]);
	for(rint i=1;i<=m;i++) read(q[i].l),read(q[i].r),q[i].id=i;
	sort(q+1,q+m+1,cmp);
	for(rint i=1,j=1;i<=n;la[a[i]]=i,i++)
	{	for(rint o=0;o<v[a[i]].size();o++)
		if(!vis[v[a[i]][o].id]) vis[v[a[i]][o].id]=1,del(v[a[i]][o].l,v[a[i]][o].r,v[a[i]][o].k);
		{	int _=la[a[i]],cur=i,p=a[i]+1,q=a[i]-1,len=1;
			for(;len<=10&&p<=a[i]+10&&q>=a[i]-10;len++)
			{	if(la[p]>cur){p++;continue;}
				if(la[q]>cur){q--;continue;}
				if(la[p]>la[q])
				{	++gg,v[q].push_back((fuck){max(_,la[p])+1,cur,len,gg}),v[p].push_back((fuck){max(_,la[p])+1,cur,len,gg});
					add(max(_,la[p])+1,cur,len),cur=la[p],p++;
				}
				else
				{	++gg,v[q].push_back((fuck){max(_,la[q])+1,cur,len,gg}),v[p].push_back((fuck){max(_,la[q])+1,cur,len,gg});
					add(max(_,la[q])+1,cur,len),cur=la[q];q--;
				}
				if(!cur||cur<_) break;
			}
		}
		for(;j<=m&&q[j].r==i;j++) query(q[j].l,ans[q[j].id]);
	}
	for(rint i=1;i<=m;i++,el())
	for(rint j=0;j<10;j++) print((ans[i][j]+10)%10);
	return flush(),0;
}

