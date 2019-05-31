#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define MAXN 511
#define ll long long

int read()
{
	int ret=0,neg=1;
	char c=getchar();
	while (c<'0' || c>'9'){
		if (c=='-') neg=-1;
		c=getchar();
	}
	while (c>='0' && c<='9'){
		ret=ret*10+c-'0';
		c=getchar();
	}
	return ret*neg;
}

char s[MAXN][MAXN];
int belong[MAXN][MAXN];
int n,m;
int cnt0,cnt1;
int mx[4]={0,0,1,-1};
int my[4]={1,-1,0,0};
int sta[MAXN*MAXN],top;
bool vis[MAXN][MAXN];
bool hv[MAXN*MAXN];
bool flag;

void dfs(int x,int y,int num)
{
//	cerr<<x<<' '<<y<<' '<<num<<'\n';
	if (x==23 && y==162)
	puts("fuck");
	belong[x][y]=num;
	for (int i=0;i<4;i++){
		int nx=x+mx[i],ny=y+my[i];
		if (nx<=0 || ny<=0 || nx>n || ny>m || belong[nx][ny]!=0)continue;
		if ((num>0)^(s[nx][ny]=='0')) dfs(nx,ny,num);
	}
}

void check(int x,int y)
{
	vis[x][y]=1;
	for (int i=0;i<4;i++){
		int nx=x+mx[i],ny=y+my[i];
		if (nx<=0 || ny<=0 || nx>n || ny>m || vis[nx][ny])continue;
		if (s[nx][ny]!=s[x][y]) sta[++top]=belong[nx][ny];
		else check(nx,ny);
	}
} 

int main()
{
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	n=read();m=read();
	for (int i=1;i<=n;i++) scanf("%s",s[i]+1);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) if (!belong[i][j]){
		if (s[i][j]=='1') dfs(i,j,++cnt1);
		else dfs(i,j,-(++cnt0));
	}
	//0
	if (cnt1==0){
		puts("0");
		return 0;
	}
	// 1
	if (cnt1==1){
		puts("1");puts("+");
		for (int i=1;i<=n;i++) printf("%s\n",s[i]+1);
		return 0;
	}
	// 2
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) if (s[i][j]=='0' && !vis[i][j]){
		check(i,j);int cnt=0;
		for (int k=1;k<=top;k++) if (!hv[sta[k]]) cnt++,hv[sta[k]]=1;
		for (int k=1;k<=top;k++) hv[sta[k]]=0;top=0;
		if (cnt==cnt1){
			puts("2");
			puts("+");
			int c=belong[i][j];
			for (int k=1;k<=n;k++){
				for (int l=1;l<=m;l++) if (belong[k][l]>0 || belong[k][l]==c) putchar('1'); else putchar('0');
				putchar('\n');
			}
			puts("-");
			for (int k=1;k<=n;k++){
				for (int l=1;l<=m;l++) if (belong[k][l]==c) putchar('1'); else putchar('0');
				putchar('\n');
			}
			return 0;
		}
	}
	if (n==1){
		printf("%d\n",cnt1);
		for (int i=1;i<=cnt1;i++){
			puts("+");
			for (int j=1;j<=m;j++) if (belong[1][j]==i) putchar('1');else putchar('0');
			putchar('\n');
		}
		return 0;
	}
	if (m==1){
		printf("%d\n",cnt1);
		for (int i=1;i<=cnt1;i++){
			puts("+");
			for (int j=1;j<=n;j++) if (belong[j][1]==i) puts("1");else puts("0");
		}
		return 0;
	}
	if (m==2){
		puts("3");
		puts("+");
		for (int i=1;i<=n;i++){
			for (int j=1;j<=m;j++)	if (i==1 || (i!=n && (j%2==1 || s[i][j]=='1'))) putchar('1'); else putchar('0');
			putchar('\n');
		}
		puts("+");
		for (int i=1;i<=n;i++){
			for (int j=1;j<=m;j++)	if (i==n || (i!=1 && (j%2==0 || s[i][j]=='1'))) putchar('1'); else putchar('0');
			putchar('\n');
		}
		puts("-");
		for (int i=1;i<=n;i++){
			for (int j=1;j<=m;j++)	if ((i!=1 && i!=n) || (s[i][j]=='0')) putchar('1'); else putchar('0');
			putchar('\n');
		}
		return 0;
	}
	puts("3");
	puts("+");
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++)	if (j==1 || (j!=m && (i%2==1 || s[i][j]=='1'))) putchar('1'); else putchar('0');
		putchar('\n');
	}
	puts("+");
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++)	if (j==m || (j!=1 && (i%2==0 || s[i][j]=='1'))) putchar('1'); else putchar('0');
		putchar('\n');
	}
	puts("-");
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++)	if ((j!=1 && j!=m) || (s[i][j]=='0')) putchar('1'); else putchar('0');
		putchar('\n');
	}
}
