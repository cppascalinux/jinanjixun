#include <bits/stdc++.h>
using namespace std;
const int maxn=1<<23+1;

int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}

int n,k,q,m=2,s[maxn];
int y[maxn],x[maxn],c[maxn],sa[maxn],rk[maxn];

void get_SA(){
    for (int i=1;i<=n;++i) ++c[x[i]=s[i]];
    for (int i=2;i<=m;++i) c[i]+=c[i-1];
    for (int i=n;i>=1;--i) sa[c[x[i]]--]=i;
    for (int k=1;k<=n;k<<=1){
        int num=0;
        for (int i=n-k+1;i<=n;++i) y[++num]=i;
        for (int i=1;i<=n;++i) if (sa[i]>k) y[++num]=sa[i]-k;
        for (int i=1;i<=m;++i) c[i]=0;
        for (int i=1;i<=n;++i) ++c[x[i]];
        for (int i=2;i<=m;++i) c[i]+=c[i-1];
        for (int i=n;i>=1;--i) sa[c[x[y[i]]]--]=y[i],y[i]=0;
        swap(x,y);
        x[sa[1]]=1;
        num=1;
        for (int i=2;i<=n;++i)
            x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?num:++num;
        if (num==n) break;
        m=num;
    }
}

int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	k=read(),q=read();
	n=1<<k;
	s[1]=0,s[2]=1;
	for (int i=3;i<=n;++i)
	s[i]=(s[((i-1)>>1)+1]+((i-1)&1))%2;
	for (int i=1;i<=n;++i)
	++s[i];
	get_SA();
	for (int i=1;i<=q;++i)
	printf("%d ",sa[read()]-1);
}
