#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+1;

int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}

struct Edge{
	int to,next;
	Edge(int a=0,int b=0){
		to=a,next=b;
	}
}l[maxn<<1];

int head[maxn],dep[maxn],n,m,cnt;
int p[22][maxn],fa[maxn],val[maxn];
int id[maxn];

void Add(int a,int b){
	l[++cnt]=Edge(b,head[a]);head[a]=cnt;
	l[++cnt]=Edge(a,head[b]);head[b]=cnt;
}

	int t[maxn];
	void ADD(int x,int v){
		while(x<=n)t[x]+=v,x+=(x&-x);
	}
	int Sum(int x){
		int r=0;
		while(x)r+=t[x],x-=(x&-x);
		return r;
	}
	void Update(int l,int r,int v){
		if (l>r) swap(l,r);
		ADD(l,v),ADD(r+1,-v);
	}


void Prep(int u,int f){
	fa[u]=p[0][u]=f;
	dep[u]=dep[f]+1;
	for (int i=1;i<21;++i)
	p[i][u]=p[i-1][p[i-1][u]];
	for (int i=head[u];i;i=l[i].next){
		int v=l[i].to;if (v==f) continue;
		Prep(v,u);
	}
}

int Lca(int a,int b){
	if (dep[b]<dep[a]) swap(a,b);
	for (int i=20;~i;--i)
	if (dep[p[i][b]]>=dep[a]) b=p[i][b];
	if (a==b) return a;
	for (int i=20;~i;--i)
	if (p[i][a]!=p[i][b]) a=p[i][a],b=p[i][b];
	return p[0][a];
}

void update(int u,int t,int c){
	if (u!=t)val[u]+=c;
	else return;
	update(fa[u],t,c);
}

void change(int a,int b,int c){
	int f=Lca(a,b);
	update(a,f,c),update(b,f,c);
	val[f]+=c;
}

vector<int>son;

void query(int u,int c){
	son.clear();son.push_back(val[u]);
	for (int i=head[u];i;i=l[i].next)
	son.push_back(val[l[i].to]);
	sort(son.begin(),son.end());
	printf("%d\n",son[c-1]);
}

void Query(int u,int c){
	son.clear();son.push_back(Sum(dep[u]));
	if (dep[u]>1) son.push_back(Sum(dep[u]-1));
	if (dep[u]<n) son.push_back(Sum(dep[u]+1));
	sort(son.begin(),son.end());
	printf("%d\n",son[c-1]);
}

void Solve(){
	for (int i=1;i<=n;++i)
	id[dep[i]]=i;
	for (int i=1;i<=n;++i)
	Update(i,i,val[id[i]]);
	for (int i=1;i<=m;++i){
		int op=read(),x=read(),y=read();
		if (op==1) Update(dep[x],dep[y],read());
		if (op==2) Query(x,y);
	}
}

void Rough(){
	for (int i=1;i<=m;++i){
		int op=read(),x=read(),y=read();
		if (op==1) change(x,y,read());
		if (op==2) query(x,y);
	}
}

int main(){
	freopen("yuki.in","r",stdin);
	freopen("yuki.out","w",stdout);
	n=read(),m=read();
	for (int i=1;i<=n;++i)
		val[i]=read();
	for (int i=2;i<=n;++i){
		int u=read(),v=read();
		Add(u,v);
	}
	Prep(1,0);
	if (m>10000) Solve();
	else Rough();
}
