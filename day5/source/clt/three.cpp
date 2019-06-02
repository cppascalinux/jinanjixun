#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 100000
#define maxm 10000000
#define eps 1E-12

const double Pi=acos(-1);

int n,m,c,W=1;
long long ans;
char s[maxn+5];
double p[maxm+1],q[maxm+1];

inline double calc(re int p1,re int p2,re int p3){
	re double x1=cos(2*Pi*p1/n),y1=sin(2*Pi*p1/n);
	re double x2=cos(2*Pi*p2/n),y2=sin(2*Pi*p2/n);
	re double x3=cos(2*Pi*p3/n),y3=sin(2*Pi*p3/n);
	return (x1*y2-x2*y1+x2*y3-x3*y2+x3*y1-x1*y3)/2;
}

int main(){
	freopen("three.in","r",stdin);
	freopen("three.out","w",stdout);
	scanf("%d%s",&n,s);
	for(re int i=0;i<n;++i)
		W&=s[i]==48;
	if(W)
		putchar(48);
	else{
		for(re int i=0;i<n;++i)
			for(re int j=i+1;j<n;++j)
				for(re int k=j+1;k<n;++k)
					if((s[i]|s[j]|s[k])^48)
						p[m++]=calc(i,j,k);
		std::sort(p,p+m);
		for(re int i=0;i<m;++i)
			if(!c||abs(p[i]-q[c-1])>eps)
				q[c++]=p[i];
		for(re int j=0;j<c;++j){
			re int cnt=0;
			for(re int i=0;i<m;++i)
				cnt+=abs(p[i]-q[j])<eps;
			ans+=1LL*cnt*(cnt-1)/2;
		}
		printf("%lld",ans);
	}
	return 0;
}

