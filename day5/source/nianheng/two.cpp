#include<map>
#include<set>
#include<ctime>
#include<queue>
#include<cmath>
#include<bitset>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mp(x,y) make_pair(x,y)
#define qmin(x,y) (x=min(x,y))
#define qmax(x,y) (x=max(x,y))
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
inline ll read(){
	ll ans=0,fh=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		ans=(ans<<1)+(ans<<3)+ch-'0',ch=getchar();
	return ans*fh;
}
const int maxn=3e5+100;
struct Node{
	int son[2],fa,siz,cnt,p;
}p[maxn*100];
int ptot;
struct Splay{
	#define lc p[o].son[0]
	#define rc p[o].son[1]
	#define fc p[o].fa
	int rt;
	inline int New(int z){
		int o=++ptot;
		p[o].siz=p[o].cnt=1;
		p[o].p=z;
		return o;
	}
	inline int son(int o){return p[fc].son[1]==o;}
	inline void updata(int o){p[o].siz=p[lc].siz+p[rc].siz+p[o].cnt;};
	inline void rotate(int o){
		int f=fc,g=p[f].fa;
		int a=son(o),b=son(f);
		if(g) p[g].son[b]=o;
		else rt=o;
		p[f].son[a]=p[o].son[a^1],fc=g;
		if(p[o].son[a^1]) p[p[o].son[a^1]].fa=f;
		p[o].son[a^1]=f,p[f].fa=o;
		updata(f),updata(o);
	}
	inline void splay(int o,int Fa){
		while(fc!=Fa){
			if(p[fc].fa!=Fa) rotate(son(o)^son(fc)?o:fc);
			rotate(o);
		}
	}
//	inline void getp(int z){
//		int o=rt;
//		while(o){
//			if(p[lc].siz>=z) o=lc;
//			else{
//				o-=p[lc].siz;
//				if(z==1) return o;
//				z--,o=rc;
//			}
//		}
//		return o;
//	}
	inline int getpos(int z){
		int o=rt,qq=o;
		while(o){
			if(p[o].p<=z) qq=o,o=rc;
			else o=lc;
		}
		return qq;
	}
	inline void del(int x){
		int o=getpos(x);
		splay(o,0);
		if(p[o].cnt>1){
			p[o].cnt--,p[o].siz--;
			return;
		}
		p[lc].fa=p[rc].fa=0;
		if(!lc||!rc) rt=lc+rc;
		else{
			int y=lc;
			while(p[y].son[1])
				y=p[y].son[1];
			p[rc].fa=y,p[y].son[1]=rc;
			splay(rc,0);
		}
	}
	inline void ins(int z){
		int o=getpos(z);
		splay(o,0);
		if(p[o].p==z){
			p[o].siz++,p[o].cnt++;
			return;
		} 
		int x=rc,a=1;
		while(x) o=x,x=lc,a=0;
		x=New(z),p[x].fa=o,p[o].son[a]=x;
		splay(x,0);
	}
	inline int query(int z){
		int o=rt;z++;
		while(o){
			if(p[rc].siz>=z) o=rc;
			else{
				z-=p[rc].siz;
				if(p[o].cnt>=z) return p[o].p;
				z-=p[o].cnt,o=lc;
			}
		}
		return p[o].p;
	}
	Splay(){
		int o=New(-1);
		rc=New(10000000),p[rc].fa=o;
		updata(rt=o);
	};
}tre[maxn];
struct node{
	int son[26],len,link;
}st[maxn];
int head[maxn],nex[maxn],v[maxn],num=1,ri[maxn];
int n,K,Rt[maxn],Ans,tot,las,siz[maxn],son[maxn];
char s[maxn];
set<int>R[maxn];
inline void add(int x,int y){
	v[++num]=y,nex[num]=head[x],head[x]=num;
}
inline void sam_init(){
	st[tot=las=0].link=-1;
}
inline void sam_extend(int z){
	int cur=++tot;
	st[cur].len=st[las].len+1;
	int p=las;
	while(~p&&!st[p].son[z])
		st[p].son[z]=cur,p=st[p].link;
	if(p==-1) st[cur].link=0;
	else{
		int q=st[p].son[z];
		if(st[q].len==st[p].len+1)
			st[cur].link=q;
		else{
			int clo=++tot;
			st[clo].len=st[p].len+1;
			st[clo].link=st[q].link;
			for(int i=0;i<26;i++)
				st[clo].son[i]=st[q].son[i];
			while(~p&&st[p].son[z]==q)
				st[p].son[z]=clo,p=st[p].link;
			st[cur].link=st[q].link=clo;
		}
	}
	las=cur;
}
void dfs1(int x){
	siz[x]=1;
	for(int i=head[x];i;i=nex[i]){
		dfs1(v[i]),siz[x]+=siz[v[i]];
		if(siz[v[i]]>siz[son[x]]) son[x]=v[i];
	}
}
void dfs2(int x,int tp){
	Rt[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(int i=head[x];i;i=nex[i])
		if(v[i]!=son[x]) dfs2(v[i],v[i]);
}
inline void Insert(int x,int z){
	set<int>::iterator pr;
	pr=R[x].upper_bound(z);
	if(pr==R[x].end()){
		if(R[x].empty()) tre[x].ins(z);
		else tre[x].ins(z-*R[x].begin());
		R[x].insert(z);
		return;
	}
	int l=0,r=*pr;
	if(pr!=R[x].begin()) l=*(--pr);
	tre[x].del(r-l);
	tre[x].ins(r-z);
	tre[x].ins(z-l);
	R[x].insert(z);
}
inline void getans(int x,int fac){
	if(K==1){
		int l=min(*R[x].begin(),tre[x].query(1));
		int r=st[st[fac].link].len;
		Ans+=max(0,r-l+1);
	}
	if(p[tre[x].rt].siz-2<K-1) return;
	Ans+=max(0,min(tre[x].query(K-1),*R[x].begin())-max(tre[x].query(K),st[st[fac].link].len));
}
void work(int x){
	if(son[x]) work(son[x]);
	if(ri[x]) Insert(Rt[x],ri[x]);
	for(int i=head[x];i;i=nex[i]){
		int y=v[i];if(y==son[x]) continue;
		work(y);set<int>::iterator it;
		for(it=R[Rt[y]].begin();it!=R[Rt[y]].end();++it)
			Insert(Rt[x],*it);
	}
	getans(Rt[x],x);
}
inline void sam_build(){
	sam_init();
	for(int i=1;i<=n;i++)
		sam_extend(s[i]-'a'),ri[las]=i;
	for(int i=1;i<=n;i++)
		add(st[i].link,i);
	for(int i=0;i<26;i++)
		if(st[0].son[i]){
			dfs1(st[0].son[i]);
			dfs2(st[0].son[i],st[0].son[i]);
			work(st[0].son[i]);
		}
}
int main(){
	freopen("two.in","r",stdin);
	freopen("two.out","w",stdout);
	scanf("%s",s+1),n=strlen(s+1);
	K=read(),sam_build(),printf("%d\n",Ans);
	return 0;
}












