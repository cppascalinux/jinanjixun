#include <cstdio>
#include <cctype>
#include <algorithm>
#include <set>
#define maxn 100005
inline int read() {
	int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return d;
}

int n, m, q;
int op[maxn], w[maxn];

namespace solve1 {
	int vis[maxn];
	int head[maxn], ver[maxn], nxt[maxn], tot;
	
	inline void add(int u, int v) {
		ver[++tot] = v, nxt[tot] = head[u], head[u] = tot;
		ver[++tot] = u, nxt[tot] = head[v], head[v] = tot;
	}
	
	int col[maxn];
	int que[maxn], he, ta;
	int op, w;
	
	void work() {
		n = 1<<m;
		while(q--) {
			op = read(), w = read();
			if(op == 1) vis[w] = 1;
			else vis[w] = 0;
			for(int i = 0; i < n; ++i) head[i] = col[i] = 0;
			tot = 0;
			for(int i = 0; i < n; ++i) if(vis[i])
				for(int u = 0; u < n; ++u) add(u, u^i);
			int mx = 1;
			for(int i = 0; i < n; ++i) if(!col[i]) {
				que[he = ta = 0] = i, col[i] = 1;
				int sum = 1;
				while(he <= ta) {
					int u = que[he++];
					for(int p = head[u]; p; p = nxt[p]) {
						int v = ver[p];
						if(!col[v]) que[++ta] = v, col[v] = 1, ++sum;
					}
				}
				mx = std::max(mx, sum);
			}
			printf("%d\n", mx);
		}
	}
}

int ct[105];

bool ins(int x) {
	for(int i = m-1; i >= 0; --i) if((x>>i)&1) {
		if(ct[i]) x ^= ct[i];
		else {
			ct[i] = x;
			return 1;
		}
	}
	return 0;
}

namespace solve2 {
	void work() {
		int sum = 0;
		for(int i = 1; i <= q; ++i) {
			if(ins(w[i])) ++sum;
			printf("%d\n", 1<<sum);
		}
	}
}

namespace solve3 {
	std::set<int> st;
	void work() {
		for(int i = 1; i <= q; ++i) {
			if(op[i] == 1) st.insert(w[i]);
			else st.erase(w[i]);
			for(int i = m-1; i >= 0; --i) ct[i] = 0;
			int sum = 0;
			for(std::set<int>::iterator it = st.begin(); it != st.end(); ++it)
				if(ins(*it)) ++sum;
			printf("%d\n", 1<<sum);
		}
	}
}

int main() {
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	m = read(), q = read();
	if(m <= 10 && q <= 100) {
		solve1::work();
		return 0;
	}
	int fl2 = 1;
	for(int i = 1; i <= q; ++i) {
		op[i] = read(), w[i] = read();
		if(op[i] == 2) fl2 = 0;
	}
	if(fl2) solve2::work();
	else solve3::work();
	return 0;
}
