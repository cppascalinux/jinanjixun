#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=102018;
int n,m,q,blo,tot;
int anc[N][22],dep[N],bian[N],dian[N],vald[N],valb[N],ans[N],bl[N],v[N],zd[N],zb[N];
struct robot{int x,y,id;}ro[N],qs[N];
struct Edge{int to,next;}e[N<<1];
void add(int x,int y){
	e[++tot].to=y;
	e[tot].next=v[x]; v[x]=tot;
}
bool cmp(const robot &a,const robot &b){
	return bl[a.x]==bl[b.x]?(a.y<b.y):a.x<b.x;
}
void dfs(int x,int fa){
	for(int i=1;i<=20;i++)
		anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int p=v[x];p;p=e[p].next){
		int kp=e[p].to;
		if(kp!=fa){
			dep[kp]=dep[x]+1;
			anc[kp][0]=x;
			dfs(kp,x);
		}
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	int cha=dep[x]-dep[y];
	for(int i=0;i<=20;i++)
		if(cha & (1<<i))x=anc[x][i];
	if(x==y)return y;
	for(int i=20;i>=0;i--)
		if(anc[x][i]!=anc[y][i])
			x=anc[x][i],y=anc[y][i];
	return anc[y][0];
}
void init(int th,int val){
	int x=ro[th].x,y=ro[th].y,lca=LCA(x,y);// cout<<"lca("<<x<<","<<y<<"):"<<lca<<"  val:"<<val<<endl;
	bian[x]+=val; bian[y]+=val; bian[lca]-=val*2;
	dian[x]+=val; dian[y]+=val; dian[lca]-=val; dian[anc[lca][0]]-=val;
//	for(int j=1;j<=n;j++)cout<<j<<":"<<dian[j]<<" "<<bian[j]<<endl;
}
void get(int x){
	for(int p=v[x];p;p=e[p].next){
		int kp=e[p].to;
		if(kp!=anc[x][0]){
			get(kp);
			zd[x]+=zd[kp]; zb[x]+=zb[kp];
		}
	}
}
void work1(){
	dfs(1,0);
	int blo=sqrt(n+1);
	for(int i=1;i<=n;i++)
		bl[i]=(i-1)/blo+1;
	sort(qs+1,qs+q+1,cmp);
	int l=qs[1].x,r=l-1;
	for(int i=1;i<=q;i++){
		while(l<qs[i].x)init(l,-1),++l;
		while(l>qs[i].x)--l,init(l,1);
		while(r<qs[i].y)++r,init(r,1);
		while(r>qs[i].y)init(r,-1),--r;
		for(int j=1;j<=n;j++)zd[j]=dian[j],zb[j]=bian[j];
		get(1); zd[0]=zb[0]=0;
		for(int j=1;j<=n;j++)
			zd[0]+=zd[j]>0,zb[0]+=zb[j]>0;
		ans[qs[i].id]=zd[0]-zb[0];
	}
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
}
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n=read(); m=read(); q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v); add(v,u);
	}
	for(int i=1;i<=m;i++)
		ro[i].x=read(),ro[i].y=read(),ro[i].id=i;
	for(int i=1;i<=q;i++)
		qs[i].x=read(),qs[i].y=read(),qs[i].id=i;
	if(n<=1000)work1();
	else work2();
	fclose(stdin); fclose(stdout);
	return 0;
}
