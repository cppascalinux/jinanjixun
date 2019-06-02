#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<set>
#define qmin(x,y) (x=min(x,y))
#define qmax(x,y) (x=max(x,y))
#define pir pair<int,int>
#define fr first
#define sc second
#define mp(x,y) make_pair(x,y)
#define vic vector<int>
#define vit vic::iterator
#define rsort(x,y) sort(x,y),reverse(x,y)
using namespace std;

inline char gc() {
	return  getchar();
}

template<typename T1>
int read(T1 &a) {
	a=0;
	char ch=gc();
	T1 f=1;
	while(!isdigit(ch)) {
		if(ch==EOF) return 0;
		if(ch=='-') f=-1;
		ch=gc();
	}
	while(isdigit(ch)) {
		a=a*10+ch-'0';
		ch=gc();
	}
	a=a*f;
	return 1;
}

template<typename T1,typename T2>
int read(T1 &a,T2 &b) {
	return read(a)+read(b);
}

template<typename T1,typename T2,typename T3>
int read(T1 &a,T2 &b,T3 &c) {
	return read(a,b)+read(c);
}

typedef long long ll;
const int Maxn=210000;
const int inf=0x3f3f3f3f;

int len[Maxn],cnt,link[Maxn],ch[Maxn][27],last;

inline int newnode(int lenn) {
	int root=++cnt;
	len[root]=lenn;
	return root;
}

inline int cp(int las,int lenn) {
	int root=++cnt;
	memcpy(ch[root],ch[las],sizeof(ch[root]));
	link[root]=link[las];
	len[root]=lenn;
	return root;
}

void extend(int x) {
	int cur=newnode(len[last]+1);
	int p=last; last=cur;
	while(p&&!ch[p][x]) {
		ch[p][x]=cur;
		p=link[p];
	}
	if(p) {
		int q=ch[p][x];
		if(len[q]==len[p]+1) link[cur]=q;
		else {
			int clone=cp(q,len[p]+1);
			link[q]=link[cur]=clone;
			while(p&&ch[p][x]==q) {
				ch[p][x]=clone;
				p=link[p];
			}
		}
	}
	else link[cur]=1;
}

int to[Maxn],nxt[Maxn],first[Maxn],tot=1;

inline void add(int u,int v) {
	to[tot]=v;
	nxt[tot]=first[u];
	first[u]=tot++;
}

int dat[Maxn*20],siz[Maxn*20],cnt2,ch2[Maxn*20][2],fa[Maxn*20];
int p[Maxn],k,rt[Maxn],scnt;
ll ans;
char s[Maxn];
set<int> se[Maxn];

#define lch ch2[root][0]
#define rch ch2[root][1]
#define fat fa[root]

inline int newnode2(int x) {
	int root=++cnt2;
	dat[root]=x;
	siz[root]=1;
	lch=rch=0;
	return root;
}

inline void update(int root) {
	siz[root]=siz[lch]+siz[rch]+1;
}

inline int son(int root) {
	return ch2[fat][1]==root;
}

void rotate(int root) {
	int y=fat,z=fa[y],d=son(root),x=ch2[root][d^1];
	if(z) ch2[z][son(y)]=root; fat=z; fa[y]=root;
	if(x) fa[x]=y; ch2[y][d]=x; ch2[root][d^1]=y; update(y);
}

void splay(int root,int top=0) {
	while(fat!=top) {
		if(fa[fat]!=top) rotate(son(root)==son(fat)?fat:root);
		rotate(root);
	} update(root);
}

int find(int root,int k) {
	if(!root) return 0;
	if(siz[lch]+1==k) return dat[root];
	if(k>=siz[lch]) return find(lch,k);
	else return find(rch,k-siz[lch]-1);
}

void ins(int &root,int x) {
	int temp=root;
	if(!temp) {
		root=newnode2(x);
		return ;
	}
	while(1) {
		if(dat[temp]<=x) {
			if(ch2[temp][1]) temp=ch2[temp][1];
			else break;
		}
		else {
			if(ch2[temp][0]) temp=ch2[temp][0];
			else break;
		}
	}
	if(dat[temp]<=x) ch2[temp][1]=newnode2(x),fa[ch2[temp][1]]=temp;
	else ch2[temp][0]=newnode2(x),fa[ch2[temp][0]]=temp;
	root=temp;
	splay(root);
}

int min(int root) {
	while(lch) root=lch;
	return root;
}

void del(int &root,int x) {
	int temp=root;
	while(1) {
		if(dat[temp]==x) break;
		if(dat[temp]<=x) temp=ch2[temp][1];
		else temp=ch2[temp][0];
	}
	splay(temp);
	if(ch2[temp][1]) {
		splay(min(ch2[temp][1]),temp);
		ch2[ch2[temp][1]][0]=ch2[temp][0];
		if(ch2[temp][0]) fa[ch2[temp][0]]=ch2[temp][1];
		root=ch2[temp][1];
	}
	else root=ch2[temp][0];
	fat=0;
	if(root) update(root);
}

void dfs(int root) {
	int son,msiz=0;
	for(int i=first[root];i;i=nxt[i]) {
		dfs(to[i]);
		if(se[p[to[i]]].size()>msiz) {
			msiz=se[p[to[i]]].size();
			son=to[i];
		}
	}
	if(!msiz) {
		if(k==1) ans+=len[root]-len[link[root]];
	}
	else {
		rt[root]=rt[son];
		if(p[root]) {
			set<int>::iterator j=se[p[root]].begin(),k=se[p[son]].lower_bound(*j);
			if(k==se[p[son]].end()) ins(rt[root],(*j)-(*se[p[son]].rbegin()));
			else if(k==se[p[son]].begin()) ins(rt[root],(*se[p[son]].begin())-(*j));
			else {
				set<int>::iterator l=k;
				l--;
				del(rt[root],(*k)-(*l));
				ins(rt[root],(*k)-(*j));
				ins(rt[root],(*j)-(*l));
			}
			se[p[son]].insert(*j);
		}
		p[root]=p[son];
		for(int i=first[root];i;i=nxt[i]) if(to[i]!=son) {
			for(set<int>::iterator j=se[p[to[i]]].begin();j!=se[p[to[i]]].end();j++) {
				set<int>::iterator k=se[p[root]].lower_bound(*j);
				if(k==se[p[root]].end()) ins(rt[root],(*j)-(*se[p[root]].rbegin()));
				else if(k==se[p[root]].begin()) ins(rt[root],(*se[p[root]].begin())-(*j));
				else {
					set<int>::iterator l=k;
					l--;
					del(rt[root],(*k)-(*l));
					ins(rt[root],(*k)-(*j));
					ins(rt[root],(*j)-(*l));
				}
				se[p[root]].insert(*j);
			}
		}
		int l=len[link[root]]+1,r=len[root]+1;
		if(k==1) qmax(l,find(rt[root],siz[rt[root]]));
		else if(siz[rt[root]]>=k-1) {
			qmin(r,find(rt[root],siz[rt[root]]-(k-1)+1));
			if(siz[rt[root]]>=k) qmax(l,find(rt[root],siz[rt[root]]-k+1));
		}
		else l=r;
		ans+=max(r-l,0);
	}
}

int main() {
	freopen("two.in","r",stdin);
	freopen("two.out","w",stdout);
	scanf("%s",s);
	read(k);
	int n=strlen(s);
	last=newnode(0);
	for(int i=0;i<n;i++) {
		extend(s[i]-'a');
		p[last]=++scnt;
		se[p[last]].insert(i);
	}
	for(int i=2;i<=cnt;i++) add(link[i],i);
	dfs(1);
	printf("%lld\n",ans);
	return 0;
}

