#include<cstdio>
#include<set>
#define re register
#define maxn 10000
#define _it std::set<int>::iterator
#define max(a,b) ((a)>=(b)?(a):(b))

int n,m;
std::set<int> S;
int f[maxn+1],size[maxn+1];

int find(re int x){
	if(f[x]!=x){
		re int tmp=f[x];
		f[x]=find(f[x]);
		tmp!=f[x]&&(size[tmp]-=size[x]);
	}
	return f[x];
}

inline void connect(re int x,re int y){
	if(find(x)!=find(y)){
		f[f[x]]=f[y];
		size[f[y]]+=size[f[x]];
	}
}

int main(){
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	scanf("%d%d",&n,&m);
	n=1<<n;
	for(;m;--m){
		int opt,x;
		scanf("%d%d",&opt,&x);
		if(opt==1)
			S.insert(x);
		else
			S.erase(x);
		for(re int i=1;i<=n;++i){
			f[i]=i;
			size[i]=1;
		}
		for(re int i=1;i<=n;++i)
			for(_it it=S.begin();it!=S.end();++it)
				connect(i,((i-1)^*it)+1);
		re int ans=0;
		for(re int i=1;i<=n;++i)
			ans=max(ans,size[i]);
		printf("%d\n",ans);
	}
	return 0;
}

