#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#define maxn 200010
#define re register
#define FOR(i, l, r) for(re int i = l; i <= r; ++i)
using namespace std;

int n, m, c, r, t, x, y, z;
int a[maxn], head[maxn], siz[maxn], depth[maxn], fa[maxn], q[maxn][4];
int cnt, num, tot, wow[maxn], res, orz[maxn];

priority_queue<int> q1, q2;

struct hz {
	int next;
	int to;
	int dis;
}h[maxn*2];

void add(int from, int to, int dis) {
	h[++num].next = head[from];
	h[num].to = to;
	h[num].dis = dis;
	head[from] = num;
}

int cmp(int x, int y) {
	return x > y;
}

int main() {
	freopen("love.in", "r", stdin);
	freopen("love.out", "w", stdout);
	int bl = 0;
	scanf("%d%d", &n, &m);
	FOR(i, 1, n-1) {
		scanf("%d%d%d", &x, &y, &z);
		if(x != 1 && y != 1)
		  bl = 1;
		add(x, y, z);
		add(y, x, z);
		wow[i] = z;
		res += z;
	}
	FOR(i, 1, m) {
		scanf("%d", &orz[i]);
	}
	sort(wow+1, wow+n, cmp);
	if(!bl) {
        FOR(i, 1, n-1) {
        	q1.push(wow[i]);
		}
		res *= 2;
		printf("%d ", res);
		FOR(i, 1, m) {
			int now = orz[i];
			if(q1.empty()) {
				if(q2.empty()) {
					printf("%d ", res);
					continue;
				}
				else {
					if(q2.top() > now) {
						res -= q2.top();
						res += now;
						q2.pop();
						q2.push(now);
					}
				}
				printf("%d ", res);
				continue;
			}
			int top1 = q1.top();
			q1.pop();
			if(q1.empty()) {
				if(q2.empty()) {
					printf("%d ", res);
					continue;
				}
				else {
					if(q2.top() > now) {
						res -= q2.top();
						res += now;
						q2.pop();
						q2.push(now);
					}
				}
				printf("%d ", res);
				continue;
			}
			int top2 = q1.top();
			q1.pop();
			if(top1 + top2 > now) {
				q2.push(now);
				res -= top1+top2;
				res += now;
			}
			else {
				q1.push(top1);
				q1.push(top2);
			}
			printf("%d ", res);
		}
	}
}
