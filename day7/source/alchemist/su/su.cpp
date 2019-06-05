#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+1;

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
}l[maxn];

int head[maxn],n,m,cnt;
int val[maxn],dep[maxn];

void Add(int a,int b){
	l[++cnt]=Edge(b,head[a]);head[a]=cnt;
	l[++cnt]=Edge(a,head[b]);head[b]=cnt;
}

void prep(int u,int f){
	for (int i=head[u];i;i=l[i].next){
		int v=l[i].to;
		if (v==f) continue;
		dep[v]=dep[u]+1;
		prep(v,u);
	}
}

int sum,dax,din;

void change(int u,int f,int c){
	sum++;dax=max(dax,dep[u]);din=min(din,dep[u]);
	for (int i=head[u];i;i=l[i].next){
		int v=l[i].to;
		if (val[v]!=val[u]||v==f) continue;
		change(v,u,c);
	}
	val[u]=c;
}

void query(int u){
	sum=0,dax=0,din=n;
	change(u,0,val[u]);
	printf("%d %d %d\n",val[u],sum,dax-din+1);
}

int main(){
	freopen("su.in","r",stdin);
	freopen("su.out","w",stdout);
	n=read();
	for (int i=1;i<=n;++i){
		int f=read();
		if (f) Add(i,f);
	}
	prep(1,0);
	for (int i=1;i<=n;++i)
		val[i]=read();
	m=read();
	for (int i=1;i<=m;++i){
		int op=read();
		int x=read(),y;
		if (op!=3) y=read();
		if (op==1){val[x]=y;}
		if (op==2){change(x,0,y);}
		if (op==3){query(x);}
	}
}
