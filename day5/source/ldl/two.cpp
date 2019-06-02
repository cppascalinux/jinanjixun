#include<iostream>
#include<cstdio>
#include<map>
#include<vector>
#include<cstring>
using namespace std;
const int N=2019,Base=131;
typedef unsigned long long ull;
char s[N]; ull p[N],H[N]; int n,k,tm,prt,top;
struct node{int l,r;};
vector <node> stk[N*N];
struct Tr{int l,r,lcol,rcol,f,data;}tr[N<<2];
map<ull,int>mp;
void build(int k,int l,int r){
	tr[k].l=l; tr[k].r=r;// tr[k].data=0;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(k<<1,l,mid); build(k<<1|1,mid+1,r);
}
void down(int k){
	if(tr[k].f){
		tr[k<<1].lcol=tr[k<<1|1].lcol=tr[k<<1].rcol=tr[k<<1|1].rcol=tr[k].f-1;
		tr[k<<1].f=tr[k<<1|1].f=tr[k].f; tr[k<<1].data=tr[k<<1|1].data=0; tr[k].f=0;
	}
}
void updata(int k){
	tr[k].data=tr[k<<1].data+tr[k<<1|1].data;
	if(tr[k<<1].rcol==0 && tr[k<<1|1].lcol==1)++tr[k].data;
	tr[k].lcol=tr[k<<1].lcol; tr[k].rcol=tr[k<<1|1].rcol;
}
void change(int k,int ql,int qr,int dt){
	if(ql<=tr[k].l && qr>=tr[k].r){
		tr[k].lcol=tr[k].rcol=dt; tr[k].data=0; tr[k].f=dt+1;
		return;
	}down(k);
	int mid=(tr[k].l+tr[k].r)>>1;
	if(ql<=mid)change(k<<1,ql,qr,dt);
	if(qr>mid)change(k<<1|1,ql,qr,dt);
	updata(k);
}
//void print(Tr a){
//	cout<<a.l<<" "<<a.r<<" "<<a.lcol<<" "<<a.rcol<<" "<<a.data<<endl;
//}
int main()
{
	freopen("two.in","r",stdin);
	freopen("two.out","w",stdout);
	scanf("%s%d",s+1,&k); n=strlen(s+1);
	p[0]=H[0]=1;
	for(int i=1;i<=n;++i)p[i]=p[i-1]*Base;
	for(int i=1;i<=n;++i)
		H[i]=H[i-1]*Base+s[i];
	for(int l=1;l<=n;++l)
		for(int r=l;r<=n;++r){
			ull val=H[r]-H[l-1]*p[r-l+1];
			if(!mp[val])mp[val]=++top;
			stk[mp[val]].push_back((node){l,r});
		}
	build(1,1,n);
	for(int i=1;i<=top;++i){
		change(1,1,n,0); int th=0,onon=stk[i].size();
		for(int j=0;j<onon;++j){
			change(1,stk[i][j].l,stk[i][j].r,1);
			if(stk[i][j].l==1)th=1;
		}
//		print(tr[1]);
		if(tr[1].data+th==k)++prt;
	}
	cout<<prt<<endl;
	fclose(stdin); fclose(stdout);
	return 0;
}
