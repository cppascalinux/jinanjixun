#include<cstring>
#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#include<cstdlib>
#include<cctype>
#include<algorithm>
#define pii pair<int,int>
#define mk make_pair
using namespace std;
const int N = 6;
char a[N][N];
bool book[N][N];
bool cc[N][N];
int color[N][N];
int a_color[N][N];
pii z[N * N];
int dx[4] = {1,-1,0,0},dy[4] = {0,0,1,-1};
int n,m,num,tot;
inline int read(){
    int v = 0,c = 1;char ch = getchar();
    while(!isdigit(ch)){
        if(ch == '-') c = -1;
        ch = getchar();
    }
    while(isdigit(ch)){
        v = v * 10 + ch - 48;
        ch = getchar(); 
    }
    return v * c;
}
inline void work1(){
	int ans = 0,now = 0;
	while(now <= m){
		while(now <= m && a[1][now] != '1') now++;	
		if(now > m) break;
		ans++;
		while(now <= m && a[1][now] == '1') now++;
	}
	cout << ans << endl;now = 0;
	//bool first = 1;
	while(now <= m){
		while(now <= m && a[1][now] != '1') now++;
		if(now > m) break;
		int l = now;
		while(now <= m && a[1][now] == '1') now++;
	//	if(first) first = 0;
		putchar('+'),putchar('\n');
		for(int i = 1;i <= m;++i){
			if(i >= l && i < now) putchar('1');
			else putchar('0');	
		}
		putchar('\n');
	}
}
inline int bfs(int x,int y){
	memset(book,0,sizeof(book));
	book[x][y] = 1;
	queue <pii> q;int sum = 1;
	q.push(mk(x,y));
	while(!q.empty()){
		pii k = q.front();q.pop();
//		printf("%d %d\n",k.first,k.second);
		for(int i = 0;i < 4;++i){
			int xx = k.first + dx[i],yy = k.second + dy[i];
		//	if(cc[xx][yy] == 0 && (xx < 1 || xx > n || yy < 1 || yy > m || book[xx][yy] || a[xx][yy] == '0')) continue;
			if(xx < 1 || xx > n || yy < 1 || yy > m || book[xx][yy]) continue;
			if(cc[xx][yy] == 0 && a[xx][yy] == '0') continue; 
			if(a[xx][yy] == '1') sum++;
			book[xx][yy] = 1;
			q.push(mk(xx,yy));
		}
	}
	//cout << sum << endl;
	return sum;
}
inline int bb(int x,int y,int c){
	color[x][y] = c;
	queue <pii> q;int sum = 1;
	q.push(mk(x,y));
		while(!q.empty()){
		pii k = q.front();q.pop();
		for(int i = 0;i < 4;++i){
			int xx = k.first + dx[i],yy = k.second + dy[i];
			if(cc[xx][yy] == 0 || xx < 1 || xx > n || yy < 1 || yy > m || color[xx][yy]) continue;
			if(a[xx][yy] == '0') sum++;
			color[xx][yy] = c;
			q.push(mk(xx,yy));
		}
	}
	return sum;	
}
inline int fun(){
	memset(color,0,sizeof(color));
	int c = 0;
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= m;++j){
			if(cc[i][j] == 1 && !color[i][j]){
				++c;
				bb(i,j,c);	
			}
		}
	return c;
}
inline void work2(){
	int x,y,ans = 0x3f3f3f3f,type;
	for(int i = 1;i <= n;++i)
	for(int j = 1;j <= m;++j) if(a[i][j] == '1') x = i,y = j,num++;
	if(!num){printf("0\n");return;}
	if(bfs(x,y) == num){
		printf("1\n");
		for(int i = 1;i <= n;++i){
			for(int j = 1;j <= m;++j)
			putchar(a[i][j]);
			puts("");
		}	
		return ;
	}
//	cout << "GG" << endl;
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= m;++j) if(a[i][j] != '1') z[tot++] = mk(i,j);
	for(int i = 1;i < (1 << tot);++i){
		memset(cc,0,sizeof(cc));
		for(int j = 0;j < tot;++j)
			if(i & (1 << j)) cc[z[j].first][z[j].second] = 1;	
		if(bfs(x,y) == num){
		//	cout << 1 << endl;
			int now = fun();
			if(ans > now) {
			//	cout << 1 << endl;
				ans = now;
				for(int i = 1;i <= n;++i)
					for(int j = 1;j <= m;++j)
						a_color[i][j] = color[i][j];	
			}
		}
	}
//	for(int i = 1;i <= n;++i){
//		for(int j = 1;j <= m;++j) cout << a_color[i][j];
//		cout << endl;
//	}
	printf("%d\n",ans + 1);
	printf("+\n");
//	system("pause");
	for(int i = 1;i <= n;++i){
		for(int j = 1;j <= m;++j)
			if(a_color[i][j] != 0 || a[i][j] == '1') putchar('1');
			else putchar('0');
		putchar('\n');
	}
	while(ans--){
		printf("-\n");
		for(int i = 1;i <= n;++i){
		for(int j = 1;j <= m;++j)
			if(a_color[i][j] == ans + 1) putchar('1');
			else putchar('0');
			putchar('\n');
		}
	}
}
int main(){
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	n = read(),m = read();
	for(int i = 1;i <= n;++i) scanf("%s",a[i] + 1);
	if(n == 1) work1();
	else if(n <= 3) work2();
	//else work3();
	return 0;	
}
