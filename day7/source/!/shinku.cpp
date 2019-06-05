#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
namespace fastIO
{ 
	#define BUF_SIZE 100000
	#define OUT_SIZE 100000
	bool IOerror=0;
	inline char nc()
	{
		static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
		if(p1==pend)
		{
			p1=buf;
			pend=buf+fread(buf,1,BUF_SIZE,stdin);
			if(pend==p1){IOerror=1;return -1;}
		}
		return *p1++;
	}
	inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
	inline void read(int &x)
	{
		bool sign=0;
		char ch=nc();
		x=0;
		for(;blank(ch);ch=nc());
		if(IOerror)return;
		if(ch=='-')sign=1,ch=nc();
		for(;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
		if(sign)x=-x;
	}
	inline void read(ll &x)
	{
		bool sign=0;
		char ch=nc();
		x=0;
		for(;blank(ch);ch=nc());
		if(IOerror)return;
		if(ch=='-')sign=1,ch=nc();
		for(;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
		if(sign)x=-x;
	}
	char ss[500000*15],tt[20];
	int ssl,ttl;
	inline int Flush()
	{
		fwrite(ss+1,sizeof(char),ssl,stdout);
		ssl=0;
		return 0;
	}
	inline int print(ll x)
	{
		if(!x)ss[++ssl]='0';
		if(x<0)ss[++ssl]='-',x=-x;
		for(ttl=0;x;x/=10)tt[++ttl]=char(x%10+'0');
		for(;ttl;ttl--)ss[++ssl]=tt[ttl];
		return ss[++ssl]='\n';
	}
	#undef OUT_SIZE
	#undef BUF_SIZE
};
using namespace fastIO;
using namespace std;
struct Query
{
	int l,r;
	int id;
}q[1000005];
int n,m,Sqr,a[1000005],cnt[1000005],pos[1000005],nowl,nowr,ans[15],res[1000005][15];
void push(int x)
{
	if(cnt[x])
	{
		cnt[x]++;
		return;
	}
	cnt[x]++;
	int r=x+1,l=x-1;
	while(r-x-1<=10&&cnt[r])r++;
	while(x-l-1<=10&&cnt[l])l--;
	if(r-x-1<=10)ans[r-x-1]--;
	if(x-l-1<=10)ans[x-l-1]--;
	if(r-l-1<=10)ans[r-l-1]++;
}
void pop(int x)
{
	cnt[x]--;
	if(cnt[x])return;
	int r=x+1,l=x-1;
	while(r-x-1<=10&&cnt[r])r++;
	while(x-l-1<=10&&cnt[l])l--;
	if(r-x-1<=10)ans[r-x-1]++;
	if(x-l-1<=10)ans[x-l-1]++;
	if(r-l-1<=10)ans[r-l-1]--;
}
void solve(int l,int r)
{
	while(nowr<r)push(a[++nowr]);
	while(nowl>l)push(a[--nowl]);
	while(nowr>r)pop(a[nowr--]);
	while(nowl<l)pop(a[nowl++]);
}
bool cmp(Query a,Query b)
{
	return pos[a.l]==pos[b.l]?a.r<b.r:a.l<b.l;
}
int main()
{
	freopen("shinku.in","r",stdin);
	freopen("shinku.out","w",stdout);
	read(n);
	read(m);
	Sqr=(int)(n/sqrt(m));
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=n;i++)pos[i]=(i-1)/Sqr+1;
	nowl=1,nowr=0;
	for(int i=1;i<=m;i++)
	{
		read(q[i].l);
		read(q[i].r);
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		solve(q[i].l,q[i].r);
		for(int j=1;j<=10;j++)res[q[i].id][j]=ans[j];
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=10;j++)
		  ss[++ssl]=(char)(res[i][j]%10+'0');
		ss[++ssl]='\n';
	}
	Flush();
	return 0;
}
