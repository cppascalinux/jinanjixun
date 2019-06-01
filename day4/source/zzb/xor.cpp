#include <cstdio>
#include <vector>
#include <queue>
#include <map>
using namespace std;
long long m, q;
vector<int> s;
int sd;
bool mak(int u, int v) {
	for(int i = 0; i < sd; i++)	if((u ^ v) == s[i]) return true;
	return false;
}

int main() {
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	scanf("%d %d", &m, &q);
	m *= m;
	while(q--) {
		int a, b;
		scanf("%d %d", &a, &b);
		if(a == 1) {
			s.push_back(b);
			sd++;
		} else {
			for(int i = 0; i < sd; i++)
				if(s[i] == b) s[i] = s[--sd];
		}
		int max = 0;
		map<int,bool> ma;
		for(int i = 0; i < m; i++) {
			int n = 0;
			n++;
			queue<int> k;
			k.push(i);
			while(!k.empty()) {
				for(int j = i + 1; j < m; j++) if(ma[j] == false && mak(k.front(),j)) {
						ma[j] = true;
						n++;
						k.push(j);
					}
				k.pop();
			}
			if(n > max) max = n;
		}
		printf("%d\n", max);
	}
	return 0;
}
