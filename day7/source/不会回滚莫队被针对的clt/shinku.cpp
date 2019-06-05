#include<cstdio>
#define re register
#define maxn 1000000
#define max(a,b) ((a)>=(b)?(a):(b))
#define abs(a) max(a,-(a))

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
		freopen("shinku.in","r",stdin);
		freopen("shinku.out","w",stdout);
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
int a[maxn+1],p[maxn+1],ans[maxn+1];

int main(){
	read(n);
	read(m);
	for(re int i=1;i<=n;++i)
		read(a[i]);
	for(re int i=1;i<=m;++i){
		int l,r;
		read(l);
		read(r);
		for(re int j=l;j<=r;++j)
			if(!p[a[j]]){
				re int x=a[j];
				p[x]=x;
				++ans[1];
				if(p[x-1]){
					--ans[p[x]-x+1];
					--ans[x-p[x-1]];
					++ans[p[x]-p[x-1]+1];
					p[p[x]]=p[x-1];
					p[p[x-1]]=p[x];
				}
				if(p[x+1]){
					--ans[x-p[x]+1];
					--ans[p[x+1]-x];
					++ans[p[x+1]-p[x]+1];
					p[p[x]]=p[x+1];
					p[p[x+1]]=p[x];
				}
			}
		for(re int j=1;j<=10;++j)
			putchar(ans[j]%10+48);
		putchar(10);
		for(re int j=l;j<=r;++j)
			p[a[j]]=0;
		for(re int j=1;j<=10;++j)
			ans[j]=0;
	}
	return 0;
}

