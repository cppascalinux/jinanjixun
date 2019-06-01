#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int nm=0; bool fh=true; char cw=getchar();
	for(;!isdigit(cw);cw=getchar()) fh^=(cw=='-');
	for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
	return nm*fh;
}
#define M 100020
map<int,int>K; vector<int> q[M<<2];
int n,m,p[M],typ[M],t[M],w[M<<2][31],sz[M<<2];
inline void ins(int *c,int k,int &SZ){
	for(int i=30;~i;--i) if((k>>i)&1)
		if(!c[i]){c[i]=k,++SZ;return;} else k^=c[i];
}
void add(int x,int l,int r,int ls,int rs,int k){
	if(ls<=l&&r<=rs){q[x].push_back(k);return;} if(r<ls||rs<l) return;
	int mid=((l+r)>>1); add(x<<1,l,mid,ls,rs,k),add(x<<1|1,mid+1,r,ls,rs,k);
}
void calc(int x,int l,int r){
	memcpy(w[x],w[x>>1],sizeof(w[x])),sz[x]=sz[x>>1];
	for(int i=0,TP=q[x].size();i<TP;i++) ins(w[x],q[x][i],sz[x]);
	if(l==r){printf("%d\n",1<<sz[x]);return;} int mid=((l+r)>>1);
	calc(x<<1,l,mid),calc(x<<1|1,mid+1,r);
}
int main(){	
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	m=read(),n=read();
	for(int i=1;i<=n;i++){typ[i]=read(),p[i]=read();(typ[i]==1)?K[p[i]]=i:t[K[p[i]]]=i;}
	for(int i=1;i<=n;i++) if(typ[i]==1&&!t[i]) t[i]=n+1;
	for(int i=1;i<=n;i++) if(typ[i]==1) add(1,1,n,i,t[i]-1,p[i]); calc(1,1,n); return 0;
}
