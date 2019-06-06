#include<bits/stdc++.h>
typedef long long i64;
const int N=100010;
int _(int l,int r){
	int x;
	assert(scanf("%d",&x)==1&&l<=x&&x<=r);
	return x;
}
int n,m,ans;
struct range{
	int l,d;
	bool operator<(const range&w)const{
		return d!=w.d?d<w.d:l<w.l;
	}
}rs[N*2];
struct point{
	i64 y;
	int l,r;
	bool operator<(const point&p)const{return y<p.y;}
}ps0[N*2],*_ps=ps0,tmp1[10000],tmp2[10000],tmp0[4];
struct block{
	point*ps;
	i64 a;
	int l,r,pp,d;
	void init(range*a,int n){
		pp=n;
		ps=_ps,_ps+=pp;
		for(int i=0;i<n;++i)ps[i]=(point){0,a[i].l,a[i].l+a[i].d};
		this->a=0;
		d=a[0].d+1;
		l=ps[0].l;
		r=ps[pp-1].r;
		//printf("[%d:(%d %d)]",n,l,r);
	}
	void modify(int L,int R,i64 a){
		i64 ad=a*d;
		if(L<=l&&r<=R)this->a+=ad;
		else if(L<=r&&l<=R){
			int p1=0,p2=0,p0=0;
			for(int i=0;i<pp;++i){
				if(L<=ps[i].l&&ps[i].r<=R){
					ps[i].y+=ad;
					tmp1[p1++]=ps[i];
				}else if(L>ps[i].r||R<ps[i].l)tmp2[p2++]=ps[i];
				else{
					ps[i].y+=a*(std::min(R,ps[i].r)-std::max(L,ps[i].l)+1);
					tmp0[p0++]=ps[i];
				}
			}
			if(p0){
				std::sort(tmp0,tmp0+p0);
				if(p1<p2){
					std::merge(tmp0,tmp0+p0,tmp1,tmp1+p1,tmp1+p1);
					std::merge(tmp1+p1,tmp1+p1+p1+p0,tmp2,tmp2+p2,ps);
				}else{
					std::merge(tmp0,tmp0+p0,tmp2,tmp2+p2,tmp2+p2);
					std::merge(tmp1,tmp1+p1,tmp2+p2,tmp2+p2+p2+p0,ps);
				}
			}else std::merge(tmp1,tmp1+p1,tmp2,tmp2+p2,ps);
		}
			//for(int i=0;i<pp;++i)printf("[%d,%d:%lld]",ps[i].l,ps[i].r,ps[i].y);puts("");
	}
	void query(int L,int R,i64 a){
		if(L<=l&&r<=R){
			a-=this->a;
			if(a>=ps[0].y){
				if(a>=ps[pp-1].y)ans+=pp;
				else ans+=std::upper_bound(ps,ps+pp,point{a,0})-ps;
			}
		}else if(L<=r&&l<=R){
			a-=this->a;
			{for(int i=0;i<pp;++i)if(L<=ps[i].l&&ps[i].r<=R&&ps[i].y<=a)++ans;}
		}
	}
};
struct seq{
	block*bs;
	int bp;
	void init(range*a,int n){
		//printf("<%d,%d>",d,n);
		int bsz=sqrt(n*log2(n))+1;
		bp=(n-1)/bsz+1;
		bs=new block[bp];
		for(int i=0,l=0,r;i<bp;++i,l=r){
			r=std::min(n,l+bsz);
			bs[i].init(a+l,r-l);
		}
	}
	void modify(int l,int r,i64 a){
		for(int i=0;i<bp;++i)bs[i].modify(l,r,a);
	}
	void query(int l,int r,i64 a){
		for(int i=0;i<bp;++i)bs[i].query(l,r,a);
	}
}ss[50];
int rp=0,sp=0;
int main(){
	n=_(1,100000),m=_(1,100000);
	rs[rp++]=(range){1,n-1};
	for(int i=0;i<rp;++i){
		int l=rs[i].l,r=l+rs[i].d,m=(l+r)/2,m1=m+1;
		//printf("[%d,%d]",l,r);
		if(l<r){
			rs[rp++]=(range){l,m-l};
			rs[rp++]=(range){m1,r-m1};
		}
	}
	std::sort(rs,rs+rp);
	for(int i=0,j=0;i<rp;i=j){
		int d=rs[i].d;
		for(++j;j<rp&&rs[j].d==d;++j);
		ss[sp++].init(rs+i,j-i);
	}
	while(m--){
		int op=_(1,2),l=_(1,n),r=_(l,n),a=_(-100000,100000);
		switch(op){
			case 1:
				for(int i=0;i<sp;++i)ss[i].modify(l,r,a);
				break;
			case 2:
				ans=0;
				for(int i=0;i<sp;++i)ss[i].query(l,r,a);
				printf("%d\n",ans);
				break;
			default:
				assert(0);
		}
	}
 	return 0;
}
