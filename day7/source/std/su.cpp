#include<bits/stdc++.h>
const int N=100077,C=30;
typedef uint32_t u32;
using std::max;
#define lc c[0]
#define rc c[1]
std::mt19937 mt(1231);
int c_up=0,c_split=0,c_merge=0;
struct node;
typedef node *pn;
struct node{
    pn c[2],fa;
    u32 rnd,l,r,d,sz,cols;
    u32 top,col;
    void pr();
    void set_l(){
        l=0,r=1,d=1,sz=1,cols=0;
    }
    void set_r(){
        l=1,r=0,d=1,sz=1,cols=0;
    }
    void up(){
        ++c_up;
        int k=lc->r-rc->l;
        if(k<0){
            l=lc->l-k;
            r=rc->r;
            d=max(lc->d-k,rc->d);
        }else{
            l=lc->l;
            r=rc->r+k;
            d=max(lc->d,rc->d+k);
        }
        sz=lc->sz+rc->sz;
        cols=lc->cols|rc->cols;
    }
    pn sc(int k,pn w){
        (c[k]=w)->fa=this;
        up();
        return this;
    }
}ns[N*4],*pool[N*2],**pp=pool,*cs[N][C];
pn merge(pn a,pn b,u32 x){
    if(a->rnd>b->rnd){
        if(x<a->rnd)return a->sc(1,merge(a->rc,b,x));
    }else{
        if(x<b->rnd)return b->sc(0,merge(a,b->lc,x));
    }
    pn w=*--pp;
    w->rnd=mt()|1u;
    w->fa=0;
    (w->lc=a)->fa=w;
    return w->sc(1,b);
}
pn merge(pn a,pn b){
    ++c_merge;
    return!a?b:!b?a:merge(a,b,mt()|1u);
}
void split(pn a,int t,pn&l,pn&r){
    ++c_split;
    for(pn f;f=a->fa;a=f)if(a==f->c[t]){
        a=f;
        l=a->lc,r=a->rc;
        *pp++=(a);
        for(;f=a->fa;a=f){
            if(a==f->lc)r=f->sc(0,r);
            else l=f->sc(1,l);
        }
        l->fa=r->fa=0;
        return;
    }
    a->fa=0;
    if(t)l=0,r=a;
    else l=a,r=0;
}
int read(int l,int r){
    int x;
    assert(scanf("%d",&x)==1&&l<=x&&x<=r);
    return x;
}
int n,m,idp=0,id[N],col[N],fa[N];
std::vector<int>es[N];
void set_cs(int x,int c,pn u){
    assert(!u||!u->fa);
    pn get_top(int);
    node*w=ns+x*2;
    cs[x][c]=u;
    if(u){
        u->top=x,u->col=c;
        for(;w;w=w->fa)w->cols|=1u<<c;
    }else{
        w->cols&=~(1u<<c);
        for(w=w->fa;w;w=w->fa)w->cols=w->lc->cols|w->rc->cols;
    }
}
pn dfs(int x){
    pn w=ns+x*2;
    w->set_l();
    for(int y:es[x]){
        node*u=dfs(y);
        if(col[x]==col[y])w=merge(w,u);
        else set_cs(x,col[y],merge(cs[x][col[y]],u));
    }
    id[x]=++idp;
    ns[x*2+1].set_r();
    return merge(w,ns+x*2+1);
}
int get_child(int x,int y){
    return *std::lower_bound(es[x].begin(),es[x].end(),y,[](int a,int b){return id[a]<id[b];});
}
pn get_top(int x){
    pn w=ns+x*2;
    while(w->fa)w=w->fa;
    return w;
}
int main(){
	freopen( "su.in" , "r" , stdin );
	freopen( "su.out" , "w" , stdout );
    n=read(1,1e5);
    for(int i=1;i<=n*2+8;++i)*pp++=ns+n*2+i;
    for(int i=1;i<=n;++i)es[fa[i]=read(i==1?0:1,i-1)].push_back(i);
    for(int i=1;i<=n;++i)col[i]=read(1,C)-1;
    col[0]=C;
    dfs(0)->col=C;
    assert(idp==n+1);
    for(m=read(1,1e5);m;--m){
        int o=read(1,3),x=read(1,n);
        pn w=get_top(x);
        pn p1,p2,p3;
        int y=w->top,cx=w->col;
        switch(o){
            case 1:{
                int c=read(1,C)-1;
                if(c==cx)break;
                split(ns+x*2,1,p1,p2);
                split(ns+x*2+1,0,p2,p3);
                set_cs(y,cx,merge(p1,p3));
                split(ns+x*2,0,p1,p2);
                split(ns+x*2+1,1,p2,p3);
                set_cs(x,cx,p2);
                p2=merge(p1,merge(cs[x][c],p3));
                set_cs(x,c,0);
                pn yw=get_top(y);
                if(yw->col==c&&y==fa[x]){
                    int t=yw->top;
                    split(ns+y*2,0,p1,p3);
                    set_cs(t,c,merge(p1,merge(p2,p3)));
                }else{
                    set_cs(fa[x],c,merge(cs[fa[x]][c],p2));
                }
                break;
            }
            case 2:{
                int c=read(1,C)-1;
                if(c==cx)break;
                int z=get_child(y,x);
                split(ns+z*2,1,p1,p2);
                split(ns+z*2+1,0,p2,p3);
                set_cs(y,cx,merge(p1,p3));
                while(p2->cols>>c&1){
                    pn v=p2;
                    while(v->lc)v=v->c[v->rc->cols>>c&1];
                    split(v,0,p1,p3);
                    pn u=cs[(v-ns)/2][c];
                    set_cs((v-ns)/2,c,0);
                    p2=merge(p1,merge(u,p3));
                }
                pn yw=get_top(y);
                if(yw->col==c){
                    int t=yw->top;
                    split(ns+y*2,0,p1,p3);
                    set_cs(t,c,merge(p1,merge(p2,p3)));
                }else{
                    set_cs(y,c,merge(cs[y][c],p2));
                }
                break;
            }
            case 3:{
                int z=get_child(y,x);
                split(ns+z*2,1,p1,p2);
                split(ns+z*2+1,0,p2,p3);
                printf("%d %d %d\n",cx+1,p2->sz/2,p2->d);
                set_cs(y,cx,merge(p1,merge(p2,p3)));
                break;
            }
        }
    }
    return 0;
}

