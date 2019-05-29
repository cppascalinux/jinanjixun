#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <ctime>
#define maxn 200010
#define re register
#define FOR(i, l, r) for(re int i = l; i <= r; ++i)
using namespace std;

int n, m, c, r, t, x, y, z, bl, ans, cnt1, cnt2, num;
int a[maxn], b[maxn], q[maxn][4], ovo[maxn], orz[maxn];
int ch1[50], ch2[50]; 

struct hz {
	int flag; //1为进2为出 
	int id;
	int pl;
	bool operator <(const hz &o) const {
		return pl < o.pl;
	}
}h[maxn];

int check() {
	cnt1 = 0, cnt2 = 0;
	FOR(i, 1, num) {
		if(h[i].flag == 1) {
			if(b[h[i].id] == 0)
			  ++cnt1;
			else 
			  if(b[h[i].id] == 1)
			    ++cnt2; 
			  else  {
			  	  puts("NOOOOOO");
			  	  exit(0);
			  }
		}
		else {
			if(b[h[i].id] == 0)
			  --cnt1;
			else 
			  if(b[h[i].id] == 1) 
			    --cnt2;
			  else {
			  	  puts("WHYYYYY");
			  	  exit(0);
			  }
		}
		if(abs(cnt2-cnt1) > 1)
		  return 0;
	}
	return 1;
}

int QAQ(int yyy) {
	int res = 0;
	random_shuffle(ovo+1, ovo+m+1); //询问序号
	memset(ch1, 0, sizeof(ch1));
	memset(ch2, 0, sizeof(ch2));
	int mid = (m >> 1 | 1);
	int eps = 1LL*rand()*rand()%yyy+1; // 暂定 
	FOR(i, 1, mid-eps) {
		int now = ovo[i];
		++ch1[q[now][1]];
		--ch1[q[now][2]+1];
	}
	FOR(i, mid-eps, m) {
		int now = ovo[i];
		++ch2[q[now][1]];
		--ch2[q[now][2]+1];
	}
	FOR(i, 1, n) {
		ch1[i] += ch1[i-1];
		ch2[i] += ch2[i-1];
		if(abs(ch1[i]-ch2[i]) > 1) 
		  ++res;
	}
	if(res == 0) {
		FOR(i, mid+1, m) {
			orz[ovo[i]] = 1;
		}
		FOR(i, 1, m) {
			printf("%d ", orz[i]);
		}
		exit(0);
	}
	return res;
}

void dfs(int x) {
	if(x > m) {
		if(check()) {
			FOR(i, 1, m)
			  printf("%d ", b[i]);
			exit(0);
		}
		return;
	}
	if(q[x][3] == -1) { //0为白色， 
		FOR(i, 0, 1) {
			b[x] = i;
			dfs(x+1);
			b[x] = 233;
		} 
	}
	else {
		b[x] = q[x][3];
		dfs(x+1);
		b[x] = 233;
	}  
}

int main() {
	freopen("wait.in", "r", stdin);
	freopen("wait.out", "w", stdout);
	srand(71806291);
	srand(rand());
	srand(rand());
	scanf("%d%d", &m, &n);
	FOR(i, 1, m) {
		scanf("%d%d%d", &q[i][1], &q[i][2], &q[i][3]);
		h[++num].flag = 1, h[num].id = i, h[num].pl = q[i][1];
		h[++num].flag = 2, h[num].id = i, h[num].pl = q[i][2]; 
	}
	sort(h+1, h+num+1);
	if(m <= 20) {
		dfs(1);
		puts("-1");
		return 0;
	}
	if(n <= 20) {
		FOR(i, 1, m)
		  ovo[i] = i;
		int t = 2050;
		int AAA = 21;
		while(t--) {
			int emm = QAQ(100);
		}
	    puts("-1");
	    return 0;
	}
	puts("-1");
	return 0;
}
//
//5 1000000000
//1 4 -1
//2 8 0
//5 7 -1
//1 4 1
//1 5 -1




