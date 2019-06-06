#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 100000

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
		freopen("flipflap.in","r",stdin);
		freopen("flipflap.out","w",stdout);
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

int n,m;
long long val[4*maxn+1];

void update(re int L,re int R,re int x,re int cur,re int l,re int r){
	if(l>=L&&r<=R)
		val[cur]+=(r-l+1)*x;
	if(l<r){
		re int mid=(l+r)>>1;
		if(L<=mid)
			update(L,R,x,cur<<1,l,mid);
		if(R>mid)
			update(L,R,x,cur<<1|1,mid+1,r);
	}
}

int query(re int L,re int R,re int x,re int cur,re int l,re int r){
	re int res=0;
	if(l>=L&&r<=R)
		res+=val[cur]<=x;
	if(l<r){
		re int mid=(l+r)>>1;
		if(L<=mid)
			res+=query(L,R,x,cur<<1,l,mid);
		if(R>mid)
			res+=query(L,R,x,cur<<1|1,mid+1,r);
	}
	return res;
}

int main(){
	read(n);
	read(m);
	for(re int i=1;i<=m;++i){
		int opt,l,r,x;
		read(opt);
		read(l);
		read(r);
		read(x);
		if(opt==1)
			update(l,r,x,1,1,n);
		else
			write(query(l,r,x,1,1,n),10);
	}
	return 0;
}

