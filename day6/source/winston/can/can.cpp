#include <bits/stdc++.h>
using namespace std;
const int maxn=6;

char mart[maxn][maxn];
int n,m,k,ans;
int color[maxn][maxn];
int vis[maxn][maxn],top;

void check(int i,int j){
	if (!i) return;
	if (!j) return;
	if (i>n) return;
	if (j>m) return;
	if (!color[i][j]) return;
	if (!vis[i][j]) top++,vis[i][j]=1;
	else return;
	check(i+1,j);
	check(i,j+1);
	check(i-1,j);
	check(i,j-1);
}

int main(){
	freopen("can.in","r",stdin);
	freopen("can.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;++i)
	scanf("%s",mart[i]+1);
	int tot=n*m;
	for (int S=0;S<1<<tot;++S){
		memset(color,0,sizeof(color));
		memset(vis,0,sizeof(vis));
		int cnt=0;top=0;
		for (int i=1;i<=tot;++i){
			if (S&(1<<(i-1))) continue;
			cnt++;
			color[(i-1)/m+1][(i%m)==0?m:i%m]=1;
		}
		int els=tot-cnt;
		if (abs(els-cnt)>k) continue;
		bool flag=1;
		for (int i=1;(i<=n)&&flag;++i)
		for (int j=1;j<=m;++j) if (color[i][j]){
			if (mart[i][j]=='B') {flag=0;break;}
		}
		if (!flag) continue;
		for (int i=1;(i<=n)&&flag;++i)
		for (int j=1;j<=m;++j) if (!color[i][j]){
			if (mart[i][j]=='A') {flag=0;break;}
		}
		if (!flag) continue;
		for (int i=1;(i<n)&&flag;++i)
		for (int j=1;j<m;++j){
			int x=color[i][j];
			if (color[i+1][j]!=x) continue;
			if (color[i][j+1]!=x) continue;
			if (color[i+1][j+1]!=x) continue;
			flag=0;break;
		}
		if (!flag) continue;
		bool chk=1;
		for (int i=1;i<=n&&chk;++i)
		for (int j=1;j<=m;++j)
		if (color[i][j]) {chk=0;check(i,j);break;}
		if (top==cnt) ans++;
	}
	printf("%d\n",ans);
}
