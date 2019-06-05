#include<iostream>
#include<cstdio>
using namespace std;
const int N=202018;
int n,m,a[N],val[N],fa[N],c[N];
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void add(int x){
	if(val[find(x)])return;
	val[x]=1;
	int fl=find(x-1),fr=find(x+1);
	if(val[fl])fa[fl]=x,val[x]+=val[fl];
	if(val[fr])fa[x]=fr,val[fr]+=val[x];
}
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main()
{
	freopen("shinku.in","r",stdin);
	freopen("shinku.out","w",stdout);
	n=read(); m=read(); int mx=0;
	for(int i=1;i<=n;i++)a[i]=read(),mx=max(mx,a[i]);
	while(m--){
		for(int j=1;j<=mx;j++)
			val[j]=c[j]=0,fa[j]=j;
		int l=read(),r=read();
		for(int j=l;j<=r;j++)
			add(a[j]);
		for(int j=1;j<=mx;j++)
			if(fa[j]==j)++c[val[j]];
		for(int j=1;j<=10;j++)
			printf("%d",c[j]%10);
		puts("");
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
