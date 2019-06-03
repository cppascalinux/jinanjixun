#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
#define int long long
const int N=102018,MP=10;
int n,m,k,ans,suma,sumb,sumc,top;
int c[100],col,cl[MP][MP],th[MP][MP];
char mp[MP][MP];
int dx[]={0,1,-1,0};
int dy[]={1,0,0,-1};
struct node{int x,y;}stk[N];
void fenjie(int x){
	top=0;
	while(x){
		c[++top]=x&1;
		x>>=1;
	}
}
void dfs(int x,int y){//cout<<x<<" "<<y<<endl;
	cl[x][y]=col;
	for(int i=0;i<4;i++){
		int rx=x+dx[i],ry=y+dy[i];
		if(rx>=1 && rx<=m && ry>=1 && ry<=n && th[rx][ry]==th[x][y] && !cl[rx][ry])
			dfs(rx,ry);
	}
}
bool check(){
	memset(th,-1,sizeof th);
	int cnt=0,sa=0,sb=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
		if(mp[i][j]=='A')th[i][j]=0,++sa;
		else if(mp[i][j]=='B')th[i][j]=1,++sb;
		else{
			++cnt;
			th[i][j]=c[cnt];
			if(th[i][j]==0)++sa;
			else ++sb;
		}
	}
	if(abs(sa-sb)>k)return 0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(th[i][j]==th[i][j+1] && th[i+1][j]==th[i][j] && th[i][j]==th[i+1][j+1])return 0;
	memset(cl,0,sizeof cl); col=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!cl[i][j])
				++col,dfs(i,j);
	if(col!=2)return 0;
	return 1;
}
#undef int
int main()
{
	freopen("can.in","r",stdin);
	freopen("can.out","w",stdout);
	#define int long long
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];
			if(mp[i][j]=='A')++suma;
			else if(mp[i][j]=='B')++sumb;
			else ++sumc;
		}
	int m=1<<sumc;
	for(int i=0;i<m;i++){
		memset(c,0,sizeof c);
		fenjie(i);
		if(check())++ans;
	}
	cout<<ans<<endl;
	fclose(stdin);fclose(stdout);
	return 0;
}
