#include<cstdio>
#define re register
#define maxn 100000
#define max(a,b) ((a)>=(b)?(a):(b))

int n,k,ans;
int a[maxn+1],b[maxn+1],f[maxn+1];

void dfs(re int cur){
	if(cur<n){
		for(re int i=1;i<=n;++i)
			if(!b[i]){
				a[cur+1]=i;
				b[i]=1;
				dfs(cur+1);
				a[cur+1]=0;
				b[i]=0;
			}
	}
	else{
		re int res=0;
		for(re int i=1;i<=n&&res<=k;++i){
			f[i]=1;
			for(re int j=1;j<i;++j)
				if(a[j]>a[i])
					(f[j]&1)&&(f[i]=max(f[i],f[j]+1));
				else
					(f[j]&1)||(f[i]=max(f[i],f[j]+1));
			res=max(res,f[i]);
		}
		ans+=res==k;
	}
}

int main(){
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	scanf("%d%d",&n,&k);
	dfs(0);
	printf("%d",ans);
	return 0;
}

