#include<cstdio>
#define re register
#define maxn 1000000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

struct stream{
	#define size 1048576
	char cltin[size+1],*ih,*it;
	inline char gc(){
		if(ih==it)
			it=cltin+fread(ih=cltin,1,size,stdin);
		if(ih==it)
			return EOF;
		return *ih++;
	}

	char cltout[size+1],*oh,*ot;
	inline void pc(char c){
		if(oh==ot)
			fwrite(oh=cltout,1,size,stdout);
		*oh++=c;
	}

	stream(){
		freopen("plasticmem.in","r",stdin);
		freopen("plasticmem.out","w",stdout);
		it=cltin+fread(ih=cltin,1,size,stdin);
		oh=cltout;
		ot=cltout+size;
	}

	~stream(){
		fwrite(cltout,1,oh-cltout,stdout);
	}
	#undef size

	template <typename _tp>
	inline void read(_tp& x){
		int sn=1;
		char c=gc();
		for(;c!=45&&(c<48||c>57)&&c!=EOF;c=gc());
		if(c==45&&c!=EOF)
			sn=-1,c=gc();
		for(x=0;c>=48&&c<=57&&c!=EOF;x=(x<<3)+(x<<1)+(c^48),c=gc());
		x*=sn;
	}

	template <typename _tp>
	inline void write(_tp x,char text=-1){
		if(x<0)
			pc(45),x=-x;
		if(!x)
			pc(48);
		else{
			int digit[22];
			for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
			for(;digit[0];pc(digit[digit[0]--]^48));
		}
		if(text>=0)
			pc(text);
	}
};
stream cltstream;
#define getchar cltstream.gc
#define putchar cltstream.pc
#define read cltstream.read
#define write cltstream.write

struct SplayTree{
	int n,m;
	int a[maxn+1];
	struct SplayNode{
		SplayNode *ftr,*lc,*rc;
		int len,val,size,sum,cnt0,cnt1,min0,min1,tag;

		inline void pushDown(){
			if(lc!=NULL){
				if(!lc->val)
					lc->len+=tag;
				else
					lc->len-=tag;
				lc->size+=tag*lc->cnt0-tag*lc->cnt1;
				lc->sum-=tag*lc->cnt1;
				lc->min0+=tag;
				lc->min1-=tag;
				lc->tag+=tag;
			}
			if(rc!=NULL){
				if(!rc->val)
					rc->len+=tag;
				else
					rc->len-=tag;
				rc->size+=tag*rc->cnt0-tag*rc->cnt1;
				rc->sum-=tag*rc->cnt1;
				rc->min0+=tag;
				rc->min1-=tag;
				rc->tag+=tag;
			}
			tag=0;
		}

		inline void pushUp(){
			size=len;
			sum=len*val;
			if(!val){
				cnt0=1;
				cnt1=0;
				min0=len;
				min1=1E9;
			}
			else{
				cnt0=0;
				cnt1=1;
				min0=1E9;
				min1=len;
			}
			if(lc!=NULL){
				size+=lc->size;
				sum+=lc->sum;
				cnt0+=lc->cnt0;
				cnt1+=lc->cnt1;
				min0=min(min0,lc->min0);
				min1=min(min1,lc->min1);
			}
			if(rc!=NULL){
				size+=rc->size;
				sum+=rc->sum;
				cnt0+=rc->cnt0;
				cnt1+=rc->cnt1;
				min0=min(min0,rc->min0);
				min1=min(min1,rc->min1);
			}
		}
	};
	SplayNode mempool[3*maxn+1],*memtop,*root,*vec[maxn+1];
	int top;

	inline SplayNode* newNode(re int len,re int val){
		re SplayNode* p=++memtop;
		p->ftr=p->lc=p->rc=NULL;
		p->len=len;
		p->val=val;
		p->pushUp();
		return p;
	}

	inline void rotate(re SplayNode* p){
		re SplayNode* q=p->ftr;
		q->pushDown();
		p->pushDown();
		p->ftr=q->ftr;
		if(p->ftr!=NULL){
			if(p->ftr->lc==q)
				p->ftr->lc=p;
			if(p->ftr->rc==q)
				p->ftr->rc=p;
		}
		if(q->rc==p){
			q->rc=p->lc;
			if(q->rc!=NULL)
				q->rc->ftr=q;
			p->lc=q;
			q->ftr=p;
		}
		else{
			q->lc=p->rc;
			if(q->lc!=NULL)
				q->lc->ftr=q;
			p->rc=q;
			q->ftr=p;
		}
		q->pushUp();
		p->pushUp();
	}

	inline void splay(re SplayNode* p,re SplayNode* q){
		for(;p->ftr!=q;rotate(p));
		if(q==NULL)
			root=p;
	}

	void breakDown(re SplayNode* p){
		p->pushDown();
		if(p->lc!=NULL)
			breakDown(p->lc);
		if(p->len)
			vec[++top]=p;
		if(p->rc!=NULL)
			breakDown(p->rc);
	}

	SplayNode* buildUp(re int l,re int r){
		re int mid=(l+r)>>1;
		re SplayNode* p=vec[mid];
		p->ftr=NULL;
		if(l<mid){
			p->lc=buildUp(l,mid-1);
			p->lc->ftr=p;
		}
		else
			p->lc=NULL;
		if(mid<r){
			p->rc=buildUp(mid+1,r);
			p->rc->ftr=p;
		}
		else
			p->rc=NULL;
		p->pushUp();
		return p;
	}

	inline SplayNode* rebuild(re SplayNode* p){
		top=0;
		breakDown(p);
		if(top){
			re int cnt=1;
			for(re int i=2;i<=top;++i)
				if(vec[i]->val==vec[i-1]->val)
					vec[cnt]->len+=vec[i]->len;
				else
					vec[++cnt]=vec[i];
			return buildUp(1,cnt);
		}
		else
			return NULL;
	}

	inline SplayNode* find(re int x){
		for(re SplayNode* p=root;p!=NULL;){
			p->pushDown();
			re int ln=p->lc!=NULL?p->lc->size:0,rn=ln+p->len;
			if(x>ln&&x<=rn)
				return p;
			else
				if(x<=ln)
					p=p->lc;
				else{
					p=p->rc;
					x-=rn;
				}
		}
		return NULL;
	}

	inline void opt12(re int l,re int r,re int x){
		re SplayNode* L=find(l);
		re SplayNode* R=find(r);
		if(R!=L){
			splay(L,NULL);
			splay(R,L);
		}
		else
			splay(L,NULL);
		re int ln=l-(L->lc!=NULL?L->lc->size:0)-1,rn=L->size-(R->rc!=NULL?R->rc->size:0)-r,cn=r-l+1;
		if(ln&&L->val!=x){
			re SplayNode* p=newNode(ln,L->val);
			p->ftr=L;
			p->lc=L->lc;
			L->lc=p;
			if(p->lc!=NULL)
				p->lc->ftr=p;
			p->pushUp();
		}
		else
			cn+=ln;
		if(rn&&R->val!=x){
			re SplayNode* p=newNode(rn,R->val);
			p->ftr=L;
			p->rc=R->rc;
			L->rc=p;
			if(p->rc!=NULL)
				p->rc->ftr=p;
			p->pushUp();
		}
		else{
			cn+=rn;
			L->rc=R->rc;
			if(L->rc!=NULL)
				L->rc->ftr=L;
		}
		L->len=cn;
		L->val=x;
		L->pushUp();
		if(L->lc!=NULL){
			re SplayNode* p=L->lc;
			for(;p->rc!=NULL;p=p->rc);
			splay(p,L);
			p->pushDown();
			if(p->val==L->val){
				L->len+=p->len;
				L->lc=p->lc;
				if(L->lc!=NULL)
					L->lc->ftr=L;
				L->pushUp();
			}
		}
		if(L->rc!=NULL){
			re SplayNode* p=L->rc;
			for(;p->lc!=NULL;p=p->lc);
			splay(p,L);
			p->pushDown();
			if(p->val==L->val){
				L->len+=p->len;
				L->rc=p->rc;
				if(L->rc!=NULL)
					L->rc->ftr=L;
				L->pushUp();
			}
		}
	}

	inline void opt3456(re int l,re int r,re int d,re int x){
		re SplayNode* L=find(l);
		re SplayNode* R=find(r);
		if(R!=L){
			splay(L,NULL);
			splay(R,L);
			if(R->lc!=NULL){
				re SplayNode* p=R->lc;
				if(!x){
					if(!p->val)
						++p->len;
					else
						--p->len;
					p->size+=p->cnt0-p->cnt1;
					p->sum-=p->cnt1;
					++p->min0;
					--p->min1;
					++p->tag;
				}
				else{
					if(p->val)
						++p->len;
					else
						--p->len;
					p->size-=p->cnt0-p->cnt1;
					p->sum+=p->cnt1;
					--p->min0;
					++p->min1;
					--p->tag;
				}
				if(!p->min0||!p->min1){
					p=rebuild(p);
					R->lc=p;
					if(p!=NULL)
						p->ftr=R;
				}
			}
			if(!d){
				if(R->val==x)
					++R->len;
				if(L->val!=x)
					--L->len;
			}
			else{
				if(R->val!=x)
					--R->len;
				if(L->val==x)
					++L->len;
			}
			R->pushUp();
			if(!R->len){
				if(R->lc!=NULL){
					re SplayNode* p=R->lc;
					for(;p->rc!=NULL;p=p->rc);
					splay(p,R);
					p->pushDown();
					p->ftr=L;
					p->rc=R->rc;
					L->rc=p;
					if(p->rc!=NULL)
						p->rc->ftr=p;
					p->pushUp();
				}
				else{
					L->rc=R->rc;
					if(L->rc!=NULL)
						L->rc->ftr=L;
				}
			}
			R=L->rc;
			if(R!=NULL){
				if(R->lc!=NULL){
					re SplayNode* p=R->lc;
					for(;p->rc!=NULL;p=p->rc);
					splay(p,R);
					p->pushDown();
					if(p->val==R->val){
						R->len+=p->len;
						R->lc=p->lc;
						if(R->lc!=NULL)
							R->lc->ftr=R;
						R->pushUp();
					}
				}
				if(R->rc!=NULL){
					re SplayNode* p=R->rc;
					for(;p->lc!=NULL;p=p->lc);
					splay(p,R);
					p->pushDown();
					if(p->val==R->val){
						R->len+=p->len;
						R->rc=p->rc;
						if(R->rc!=NULL)
							R->rc->ftr=R;
						R->pushUp();
					}
				}
			}
			L->pushUp();
			if(!L->len){
				if(L->lc!=NULL){
					re SplayNode* p=L->lc;
					for(;p->rc!=NULL;p=p->rc);
					splay(p,L);
					p->pushDown();
					p->ftr=NULL;
					p->rc=L->rc;
					if(p->rc!=NULL)
						p->rc->ftr=p;
					p->pushUp();
					root=p;
				}
				else{
					L=L->rc;
					L->ftr=NULL;
					root=L;
				}
			}
			L=root;
			if(L->lc!=NULL){
				re SplayNode* p=L->lc;
				for(;p->rc!=NULL;p=p->rc);
				splay(p,L);
				p->pushDown();
				if(p->val==L->val){
					L->len+=p->len;
					L->lc=p->lc;
					if(L->lc!=NULL)
						L->lc->ftr=L;
					L->pushUp();
				}
			}
			if(L->rc!=NULL){
				re SplayNode* p=L->rc;
				for(;p->lc!=NULL;p=p->lc);
				splay(p,L);
				p->pushDown();
				if(p->val==L->val){
					L->len+=p->len;
					L->rc=p->rc;
					if(L->rc!=NULL)
						L->rc->ftr=L;
					L->pushUp();
				}
			}
		}
	}

	inline void opt7(re int l,re int r){
		re SplayNode* L=find(l);
		re SplayNode* R=find(r);
		if(R!=L){
			splay(L,NULL);
			splay(R,L);
			re int ln=l-(L->lc!=NULL?L->lc->size:0)-1,rn=L->size-(R->rc!=NULL?R->rc->size:0)-r;
			write((R->lc!=NULL?R->lc->sum:0)+(L->len-ln)*L->val+(R->len-rn)*R->val,10);
		}
		else
			write((r-l+1)*L->val,10);
	}

	SplayTree(){
		memtop=mempool;
		read(n);
		read(m);
		for(re int i=1;i<=n;++i)
			read(a[i]);
		top=0;
		for(re int i=2,j=1;i<=n;++i){
			if(a[i]!=a[j]){
				vec[++top]=newNode(i-j,a[j]);
				j=i;
			}
			if(i==n)
				vec[++top]=newNode(i-j+1,a[j]);
		}
		root=buildUp(1,top);
		for(re int i=1;i<=m;++i){
			int opt,l,r;
			read(opt);
			read(l);
			read(r);
			switch(opt){
				case 1:
				case 2:
					opt12(l,r,opt-1);
					break;
				case 3:
				case 4:
				case 5:
				case 6:
					opt3456(l,r,(opt&1)^1,opt<=4);
					break;
				case 7:
					opt7(l,r);
					break;
			}
		}
	}
};
SplayTree CLT;

int main(){
	return 0;
}

