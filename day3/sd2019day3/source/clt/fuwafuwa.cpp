#include<cstdio>
#define re register
#define maxm 10000000

int T,a,b,m,n;
struct node{
	node *lc,*rc;
	int val,dep;
};
node mp[maxm+1],*mt,*root;

node* Insert(re node* p,re int x,re int d){
	if(p==NULL){
		p=++mt;
		p->lc=p->rc=NULL;
		p->val=x;
		p->dep=d;
	}
	else
		if(x<p->val)
			p->lc=Insert(p->lc,x,d+1);
		else
			p->rc=Insert(p->rc,x,d+1);
	return p;
}

int main(){
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
	scanf("%d",&T);
	for(;T;--T){
		mt=mp;
		root=NULL;
		scanf("%d%d%d%d",&a,&b,&m,&n);
		a%=m;
		b%=m;
		for(re int i=1;i<=n;++i)
			root=Insert(root,(a+1LL*i*b%m)%m,0);
		printf("%d\n",mt->dep);
	}
	return 0;
}

