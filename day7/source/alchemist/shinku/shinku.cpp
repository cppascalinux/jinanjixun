#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+1;

int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}

struct Qry{
	int l,r,id,block;
	Qry(int a=0,int b=0,int c=0,int d=0){
		l=a,r=b,id=c,block=d;
	}
	bool operator < (const Qry &x) const{
		return block==x.block?l<x.l:block<x.block;
	}
}Q[maxn];

int n,m,a[maxn],tot[11],ans[maxn][11];
int L=1,R=0,cnt[maxn];

void inc(int x){
	++cnt[a[x]];
	if (cnt[a[x]]>1) return;
	int rs=a[x];
	while(cnt[rs+1]&&rs+1-a[x]<=10) rs++;
	if (rs-a[x]<=10) tot[rs-a[x]]--;
	int ls=a[x];
	while(ls&&cnt[ls-1]&&a[x]-ls+1<=10) ls--;
	if (a[x]-ls<=10) tot[a[x]-ls]--;
	if (rs-ls+1<=10) tot[rs-ls+1]++;
}

void dec(int x){
	--cnt[a[x]];
	if (cnt[a[x]]) return;
	int rs=cnt[a[x]+1]?a[x]+1:a[x];
	while(cnt[rs+1]&&rs+1-a[x]<=10) rs++;
	if (rs-a[x]<=10) tot[rs-a[x]]++;
	int ls=cnt[a[x]-1]?a[x]-1:a[x];
	while((ls)&&cnt[ls-1]&&a[x]-ls+1<=10) ls--;
	if (a[x]-ls<=10) tot[a[x]-ls]++;
	if (rs-ls+1<=10) tot[rs-ls+1]--;
}

int main(){
	freopen("shinku.in","r",stdin);
	freopen("shinku.out","w",stdout);
	n=read(),m=read();
	int len=sqrt(m);
	for (int i=1;i<=n;++i)
	a[i]=read();
	for (int i=1;i<=m;++i){
		int l=read(),r=read();
		Q[i]=Qry(l,r,i,r/len);
	}
	sort(Q+1,Q+1+m);
	for (int i=1;i<=m;++i){
		int l=Q[i].l,r=Q[i].r;
		while(R<r) R++,inc(R);
		while(R>r) dec(R),R--;
		while(L>l) L--,inc(L);
		while(L<l) dec(L),L++;
		for (int k=1;k<=10;++k)
		ans[Q[i].id][k]=tot[k]%10;
	}
	for (int i=1;i<=m;++i,puts(""))
		for (int k=1;k<=10;++k)
			putchar('0'+ans[i][k]);
}
