#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=202018;
int n,m,tot,col[N],sum,mi,mx,vis[N],fa[N],dep[N],v[N];
struct Edge{int to,next;}e[N<<1];
void add(int x,int y){
	e[++tot].to=y;
	e[tot].next=v[x]; v[x]=tot;
}
void dfs1(int x){
	for(int p=v[x];p;p=e[p].next){
		int kp=e[p].to;
		if(kp!=fa[x]){
			dep[kp]=dep[x]+1;
			dfs1(kp);
		}
	}
}
void dfs(int x,int cl,int dt){
	if(cl==dt)return;
	col[x]=dt;
	for(int p=v[x];p;p=e[p].next){
		int kp=e[p].to;
		if(col[kp]==cl)dfs(kp,cl,dt);
	}
}
void getans(int x,int cl){
	++sum;
	mi=min(mi,dep[x]); mx=max(mx,dep[x]);
	for(int p=v[x];p;p=e[p].next){
		int kp=e[p].to;
		if(col[kp]==cl && !vis[kp]){
			vis[kp]=1;getans(kp,cl);
		}
	}
}
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main()
{
	freopen("su.in","r",stdin);
	freopen("su.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		fa[i]=read();
		if(i!=1)add(i,fa[i]),add(fa[i],i);
	}
	for(int j=1;j<=n;j++)col[j]=read();
	m=read(); dfs1(1);
	while(m--){
		int opt=read(),x=read(),y;
		if(opt==1)col[x]=read();
		if(opt==2)dfs(x,col[x],read());
		if(opt==3){
			memset(vis,0,sizeof vis); vis[x]=1;
			mi=1e9,mx=-1e9,sum=0;
			getans(x,col[x]);
			printf("%d %d %d\n",col[x],sum,mx-mi+1);
		}
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
