#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<map>
using namespace std;
int m,n,opt,x,root=0,tot=0;
int ans[1000010];
int last[1000010];
int p[31];
map<int,int>pos;
vector<int>vec[500010];
struct Tree{
	int l,r;
}t[10000010];
struct Ji{
	int a[40];
};
inline int read(){
	int ans=0,k=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')k=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=(ans<<3)+(ans<<1)+(c-'0');c=getchar();}
	return ans*k;
}
inline void add(Ji &tmp,int x){
	for(register int i=30;i>=0;i--){
		if((x>>i)&1){
			if(tmp.a[i])x=x^tmp.a[i];
			else{
				tmp.a[i]=x;
				break;
			}
		}
	}
}
inline int calc(Ji tmp){
	int res=0;
	for(register int i=0;i<=30;i++){
		if(tmp.a[i]){
			res++;
		}
	}
	return res;
}
void build(int &now,int l,int r){
	now=++tot;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(t[now].l,l,mid);
	build(t[now].r,mid+1,r);
}
void insert(int now,int l,int r,int p,int q,int x){
	if(p<=l&&q>=r){
		vec[now].push_back(x);
		return;
	}
	int mid=(l+r)>>1;
	if(p<=mid)insert(t[now].l,l,mid,p,q,x);
	if(q>mid)insert(t[now].r,mid+1,r,p,q,x);
}
void query(int now,int l,int r,Ji tmp){
	int siz=vec[now].size();
	for(register int i=0;i<siz;i++){
		add(tmp,vec[now][i]);
	}
	if(l==r){
		ans[l]=p[calc(tmp)];
		return;
	}
	int mid=(l+r)>>1;
	query(t[now].l,l,mid,tmp);
	query(t[now].r,mid+1,r,tmp);
}
int main(){
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	p[0]=1;
	for(register int i=1;i<=30;i++){
		p[i]=p[i-1]*2;
	}
	m=read();n=read();
	build(root,1,n);
	for(register int i=1;i<=n;i++){
		opt=read();x=read();
		if(opt==1){
			pos[x]=i;
			last[i]=x;
		}
		else{
			insert(root,1,n,pos[x],i-1,x);
			last[pos[x]]=0;
			pos[x]=0;
		}
	}
	for(register int i=1;i<=n;i++){
		if(last[i]){
			insert(root,1,n,i,n,last[i]);
		}
	}
	Ji tmp;
	for(register int i=0;i<40;i++)tmp.a[i]=0;
	query(root,1,n,tmp);
	for(register int i=1;i<=n;i++)printf("%d\n",ans[i]);
	return 0;
}
