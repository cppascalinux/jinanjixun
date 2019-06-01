#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 100000
#define maxm 100000
#define maxq 100000
#define id(a) ((a-1)/sq+1)
#define swap(a,b) a^=b,b^=a,a^=b

int n,m,q,ec,vc,sq;
int des[2*maxn+1],suc[2*maxn+1],las[maxn+1];
int cvr[4*maxn+1],len[4*maxn+1];
int f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],id[maxn+1],top[maxn+1];
int st[maxm+1],ed[maxm+1];
struct Query{
	int id,l,r;
};
Query query[maxq+1];
int ans[maxq+1];

inline bool operator<(const Query& p1,const Query& p2){
	return id(p1.l)==id(p2.l)?(id(p1.l)&1)?p1.r<p2.r:p1.r>p2.r:p1.l<p2.l;
}

inline void connect(re int x,re int y){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
}

void cover(re int L,re int R,re int x,re int cur,re int l,re int r){
	if(l>=L&&r<=R){
		x?(++cvr[cur]):(--cvr[cur]);
		len[cur]=cvr[cur]?r-l+1:l<r?len[cur<<1]+len[cur<<1|1]:0;
	}
	else{
		re int mid=(l+r)>>1;
		if(cvr[cur]){
			len[cur<<1]=mid-l+1;
			len[cur<<1|1]=r-mid;
		}
		if(L<=mid)
			cover(L,R,x,cur<<1,l,mid);
		if(R>mid)
			cover(L,R,x,cur<<1|1,mid+1,r);
		len[cur]=cvr[cur]?r-l+1:l<r?len[cur<<1]+len[cur<<1|1]:0;
	}
}

void dfs1(re int cur,re int ftr){
	f[cur]=ftr;
	dep[cur]=dep[ftr]+1;
	size[cur]=1;
	re int maxsize=0;
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=f[cur]){
			dfs1(des[i],cur);
			size[cur]+=size[des[i]];
			if(maxsize<size[des[i]]){
				maxsize=size[des[i]];
				hes[cur]=des[i];
			}
		}
}

void dfs2(re int cur,re int curtop){
	id[cur]=++vc;
	top[cur]=curtop;
	if(hes[cur]){
		dfs2(hes[cur],curtop);
		for(re int i=las[cur];i;i=suc[i])
			if(des[i]!=f[cur]&&des[i]!=hes[cur])
				dfs2(des[i],des[i]);
	}
}

inline void pthcvr(re int x,re int y,re int z){
	for(;top[x]!=top[y];){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		cover(id[top[y]],id[y],z,1,1,n);
		y=f[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	cover(id[x]+1,id[y],z,1,1,n);
}

int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d%d%d",&n,&m,&q);
	for(re int i=1;i<n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		connect(x,y);
		connect(y,x);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(re int i=1;i<=m;++i)
		scanf("%d%d",&st[i],&ed[i]);
	for(re int i=1;i<=q;++i){
		query[i].id=i;
		scanf("%d%d",&query[i].l,&query[i].r);
	}
	sq=m/sqrt(q);
	std::sort(query+1,query+q+1);
	for(re int i=1,L=1,R=0;i<=q;++i){
		for(;R<query[i].r;++R,pthcvr(st[R],ed[R],1));
		for(;L>query[i].l;--L,pthcvr(st[L],ed[L],1));
		for(;R>query[i].r;pthcvr(st[R],ed[R],0),--R);
		for(;L<query[i].l;pthcvr(st[L],ed[L],0),++L);
		ans[query[i].id]=n-len[1];
	}
	for(re int i=1;i<=q;++i)
		printf("%d\n",ans[i]);
	return 0;
}

