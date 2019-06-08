#include <bits/stdc++.h>
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
using namespace std;

const int dx[4]={2,0,0,-2};
const int dy[4]={0,2,-2,0};
const int bx[4]={1,0,0,-1};
const int by[4]={0,1,-1,0};

char mat[100][100];
bool vis[100][100];
int n,top;
vector<pii>ans;

pii find(int x,int y){
	for (int k=0;k<4;++k){
		int nx=x+dx[k];
		int ny=y+dy[k];
		int rx=x+bx[k];
		int ry=y+by[k];
		if ((nx<1)||(ny<1)||(nx>2*n+1)||(ny>2*n+1)) continue;
		if (vis[nx][ny]) continue;
		if (mat[rx][ry]=='|'||mat[rx][ry]=='-') return mp(nx,ny);
	}
	return mp(-1,-1);
}

int main(){
	freopen("loopy8.result","r",stdin);
	freopen("loopy8.out","w",stdout);
	scanf("%d",&n);
	char ch=getchar();
	for (int i=1;i<=2*n+1;++i){
		for (int j=1;j<=2*n+1;++j){
			ch=getchar();
			mat[i][j]=ch;
		}
		ch=getchar();
	}
	pii failed=mp(-1,-1);
	pii start=failed;
	for (int i=1;i<=2*n+1&&start==failed;i+=2)
		for (int j=1;j<=2*n+1;j+=2)
			if (find(i,j)!=failed){
				start=mp(i,j);
				break;
			}
	ans.pb(start);
	while(1){
		int x=ans[ans.size()-1].first;
		int y=ans[ans.size()-1].second;
		vis[x][y]=1;
		pii next=find(x,y);
		if (next==start||next==failed) break;
		ans.pb(next);
	}
	cout<<ans.size()<<endl;
	for (auto v:ans){
		int x=(v.first-1)/2;
		int y=(v.second-1)/2;
		cout<<x<<" "<<y<<endl;
	}
}
