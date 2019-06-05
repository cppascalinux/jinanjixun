#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 200010
#define re register
#define FOR(i, l, r) for(re int i = l; i <= r; ++i)
using namespace std;

int n, m, c, r, t, x, y, z;
int sq, num, k;
int a[maxn], b[maxn], fa[maxn];
int ans, head[maxn], depth[maxn], maxx, minn, qwq[maxn], top[maxn], siz[maxn], son[maxn];

struct hz {
	int next;
	int to;
}h[maxn];

void add(int from, int to) {
	h[++num].next = head[from];
	h[num].to = to;
	head[from] = num;
}

void dfs3(int x,int topf){
    top[x]=topf;
    if(!son[x])
      return;
    dfs3(son[x],topf);
    for(re int i=head[x];i!=0;i=h[i].next){
        if(h[i].to==fa[x]||h[i].to==son[x])
          continue;
        dfs3(h[i].to,h[i].to);
    }
}

int lca(int x,int y){
    while(top[x]!=top[y]){
        if(depth[top[x]]<depth[top[y]])
          swap(x,y);
        x=fa[top[x]];
    }
    if(depth[x]>depth[y])
      swap(x,y);
    return x;
}

void dfs1(int x, int f) {
	depth[x] = depth[f] + 1;
	fa[x] = f;
	siz[x] = 1;
	for(re int i = head[x]; i != 0; i = h[i].next) {
		if(h[i].to == f)
		  continue;
		dfs1(h[i].to, x);
		siz[x] += siz[h[i].to];
		if(siz[h[i].to] > siz[son[x]])
		  son[x] = h[i].to;
	}
}

void dfs2(int x, int kth) {
	qwq[0] = 0;
	qwq[++qwq[0]] = a[x];
	for(re int i = head[x]; i != 0; i = h[i].next) {
		qwq[++qwq[0]] = a[h[i].to];
	}
	sort(qwq+1, qwq+qwq[0]+1);
	printf("%d\n", qwq[kth]);
}

int main() {
	freopen("yuki.in", "r", stdin);
	freopen("yuki.out", "w", stdout);
	scanf("%d%d", &n, &m);
	FOR(i, 1, n)
	  scanf("%d", &a[i]);
	FOR(i, 1, n-1) {
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	depth[0] = -1;
	dfs1(1, 0);
	dfs3(1, 1);
	FOR(i, 1, m) {
		scanf("%d", &t);
		if(t == 1) {
			scanf("%d%d%d", &x, &y, &z);
			if(x == y) {
				a[x] += z;
				continue;
			}
			int LCAA = lca(x, y);
			while(x != LCAA)
			  a[x] += z, x = fa[x];
			while(y != LCAA)
			  a[y] += z, y = fa[y];
			a[LCAA] += z;
		}
		if(t == 2) {
			scanf("%d%d", &x, &k);
			dfs2(x, k);
		}
	}
}
