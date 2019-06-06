#include<iostream>
#include<cstdio>
using namespace std;
#define int long long
int n,m,cnt,ans;
struct Tr{int l,r,dt;}tr[802018];
void updata(int k){tr[k].dt=tr[k<<1].dt+tr[k<<1|1].dt;}
void build(int k,int l,int r){
	tr[k].l=l; tr[k].r=r;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(k<<1,l,mid); build(k<<1|1,mid+1,r);
	updata(k);
}
void change1(int k,int ad){
	tr[k].dt+=(tr[k].r-tr[k].l+1)*ad;
	if(tr[k].l==tr[k].r)return;
	change1(k<<1,ad); change1(k<<1|1,ad);
}
void change(int k,int ql,int qr,int ad){
	if(ql<=tr[k].l && qr>=tr[k].r){change1(k,ad); return;}
	int mid=(tr[k].l+tr[k].r)>>1;
	if(ql<=mid)change(k<<1,ql,qr,ad);
	if(qr>mid)change(k<<1|1,ql,qr,ad);
	updata(k);
}
void query(int k,int ql,int qr,int ad){
	if(tr[k].dt<=ad && ql<=tr[k].l && qr>=tr[k].r)++ans;
	if(tr[k].l==tr[k].r)return;
	int mid=(tr[k].l+tr[k].r)>>1;
	if(ql<=mid)query(k<<1,ql,qr,ad);
	if(qr>mid)query(k<<1|1,ql,qr,ad);
}
void query1(int ql,int qr,int ad){
	for(int i=1;i<=3*n+1;i++)
		if(tr[i].l>=ql && tr[i].r<=qr && tr[i].dt<=ad)++ans;
}
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
#undef int
int main()
{
	#define int long long
	freopen("flipflag.in","r",stdin);
	freopen("flipflag.out","w",stdout);
	n=read(); m=read();
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int opt=read(),l=read(),r=read(),a=read();
		if(opt==1)change(1,l,r,a);
		else ans=0,query1(l,r,a),printf("%lld\n",ans);
	}fclose(stdin); fclose(stdout);
	return 0;
}
