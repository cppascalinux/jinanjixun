#include<bits/stdc++.h>
#define ll long long
#define mk make_pair
#define pb push_back
#define pa pair<int,int>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<"\n"
#define fir first
#define sec second
#define SZ(x) (x).size()
using namespace std;
namespace IO
{   const int __S=1e7;char __buf[__S],*__H,*__T;
    inline char getc()
    {   if(__H==__T) __T=(__H=__buf)+fread(__buf,1,__S,stdin);
        if(__H==__T) return -1;return *__H++;
    }
    template <class __I>inline void read(__I &__x)
    {   char __c=getc(); while(!isdigit(__c)) __c=getc();
        for(__x=0;isdigit(__c);__c=getc()) __x=__x*10+(__c^'0');
    }
}using namespace IO;
char s[20101000];
int n,m,A[1010100],las[1010100],pos[1010100],cnt;
struct BIT{
	int Sum[1010000];
	inline void add(int pos,int d){while(pos<=n) Sum[pos]+=d,pos+=(pos&(-pos));}
	inline int Qry(int pos){int res=0;while(pos)res+=Sum[pos],pos-=(pos&(-pos));return res;}
	inline void Gao(int l,int r,int d){
		if(l>r) return ;
		add(l,d);add(r+1,-d);
	}
}bit[11];
struct node{
	int pos,val;
}t[33];
inline bool operator < (node p,node q){
	return p.pos>q.pos;
}
vector<int> vec[1010100];
int vis[1010100];
vector<pa> Qry[1010100];
int pp[1010100];
inline bool cmp(int i,int j){return t[i].pos>t[j].pos;}
inline void Gao(int i) {
	cnt=0;
	for(rint j=max(A[i]-11,0);j<=A[i]+11;++j) {
		if(las[j]!=0) t[++cnt].pos=las[j],t[cnt].val=j;
		if(pos[las[j]]!=0&&(j==A[i])) t[++cnt].pos=vec[j][pos[las[j]]-1],t[cnt].val=j;
	}
//	for(rint i=1;i<=cnt;++i) pp[i]=i;
	sort(t+1,t+cnt+1);
	int las=i;
	for(rint j=1;j<=cnt;++j) {
//		int idx=pp[j];
		if(vis[A[i]]==1)
		{
			int Max=A[i],Min=A[i];
			while(vis[Max+1]==1) Max++;
			while(vis[Min-1]==1) Min--;
			if(Max-Min+1<=10) {
				bit[Max-Min+1].Gao(t[j].pos+1,las,1);
			}
			if(Max-A[i]<=10&&Max-A[i]) {
				bit[Max-A[i]].Gao(t[j].pos+1,las,-1);
			}
			if(A[i]-Min<=10&&A[i]-Min) {
				bit[A[i]-Min].Gao(t[j].pos+1,las,-1);
			}
			las=t[j].pos;
		}
		else if(vis[A[i]]==2) {
			break;
		}
		vis[t[j].val]++;
	}
	if(vis[A[i]]==1)
	{
		int Max=A[i],Min=A[i];
		while(vis[Max+1]==1) Max++;
		while(vis[Min-1]==1) Min--;
		if(Max-Min+1<=10) {
			bit[Max-Min+1].Gao(1,las,1);
		}
		if(Max-A[i]<=10&&Max-A[i]) {
			bit[Max-A[i]].Gao(1,las,-1);
		}
		if(A[i]-Min<=10&&A[i]-Min) {
			bit[A[i]-Min].Gao(1,las,-1);
		}
	}
	for(rint j=1;j<=cnt;++j) {
		if(vis[t[j].val]) vis[t[j].val]--;
	}
}
int Ans[1010010][11];
int main(){
	freopen("shinku.in","r",stdin);
	freopen("shinku.out","w",stdout);
	int top=0;
	read(n),read(m);
	for(rint i=1;i<=n;++i) {
		read(A[i]);
		vec[A[i]].pb(i);
		pos[i]=vec[A[i]].size()-1;
	}
	for(rint i=1;i<=m;++i) {
		int l,r;read(l),read(r);
		Qry[r].pb(mk(l,i));
	}
	for(rint i=1;i<=n;++i) {
		las[A[i]]=i;
		Gao(i);
		for(rint j=0;j<SZ(Qry[i]);++j) {
			int l=Qry[i][j].fir,idx=Qry[i][j].sec;
			for(rint t=1;t<=10;++t) Ans[idx][t]=bit[t].Qry(l)%10;
		}
	}
	for(rint i=1;i<=m;++i,s[++top]='\n') for(rint j=1;j<=10;++j) s[++top]='0'+Ans[i][j];
	fwrite(s+1,1,top,stdout);
	return 0;
}
