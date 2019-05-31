#include<iostream>
#include<cstdio>
using namespace std;
const int N=2600;
int n,m,cnt,tot,top,mxbl,mx1;
bool vis[N],xuan[N],ans[N],end[N][N],pr[N],yj[N][N];
int col[N][N],sum[N],ed[N][N],v[N],stk[N],anspr[N][N];
char map[N][N],s[N];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
struct Edge{int to,next;}e[N*N];
void add(int x,int y){
	e[++tot].to=y;
	e[tot].next=v[x];v[x]=tot;
}
void dfsbl(int x,int y){
	col[x][y]=cnt;
	for(int i=0;i<4;i++){
		int rx=x+dx[i],ry=y+dy[i];
		if(map[rx][ry]=='1' && !col[rx][ry])
			dfsbl(rx,ry);
	}
}
void dfswh(int x,int y){
	col[x][y]=cnt;
	for(int i=0;i<4;i++){
		int rx=x+dx[i],ry=y+dy[i];
		if(map[rx][ry]=='1' && !ed[cnt][col[rx][ry]]){
			++sum[cnt];
			ed[cnt][col[rx][ry]]=ed[col[rx][ry]][cnt]=1;
			add(cnt,col[rx][ry]); add(col[rx][ry],cnt);
		}
		else if(map[rx][ry]=='0' && !col[rx][ry])dfswh(rx,ry);
	}
}
void gengxin(){
	top=0;
	for(int i=mxbl+1;i<=cnt;i++)
		if(xuan[i])stk[++top]=i,ans[i]=1;
}
void work(){
	int res=mxbl; mx1=mxbl;
	for(int i=1;i<=cnt-mxbl;i++){
		int mx=0,w=mxbl+1;
		for(int j=mxbl+1;j<=cnt;j++)
			if(mx<sum[j])mx=sum[j],w=j;
		xuan[w]=1;
		for(int p=v[w];p;p=e[p].next){
			int kp=e[p].to;
			if(!vis[kp]){
				--res,vis[kp]=1;
				for(int p1=v[kp];p1;p1=e[p1].next)--sum[e[p1].to];
			}
		}
		if(res+i+1<mx1)mx1=res+i+1,gengxin();
	}
}
void prcol(int x){
	puts("-");
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(col[i][j]==x)printf("1");
			else printf("0");
		}
		putchar('\n');
	}pr[x]=1;
}
void prdfs(int x,int y){
	end[x][y]=1;
	for(int i=0;i<4;i++){
		int rx=x+dx[i],ry=y+dy[i];
		if(map[rx][ry]=='1' && !end[rx][ry])
			prdfs(rx,ry);
	}
}
void prone(){
	puts("+");
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!yj[i][j] && end[i][j])
				yj[i][j]=1,printf("1");
			else printf("0");
		}
		putchar('\n');
	}
}
void print(){
	cout<<mx1<<endl;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(map[i][j]=='0' && ans[col[i][j]]){
				map[i][j]='1';
				if(!pr[col[i][j]])prcol(col[i][j]);
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!end[i][j] && map[i][j]=='1'){
				prdfs(i,j); prone();
			}
}
int main()
{
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n+1;i++)
		for(int j=0;j<=m+1;j++)map[i][j]='*';
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)
			map[i][j]=s[j];
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!col[i][j] && map[i][j]=='1'){
				++cnt;
				dfsbl(i,j);
			}
	mxbl=cnt;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!col[i][j] && map[i][j]=='0'){
				++cnt;
				dfswh(i,j);
			}
	work(); print();
	fclose(stdin); fclose(stdout);
	return 0;
}
/*
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			cout<<col[i][j]<<" ";
		cout<<endl;
	}
	for(int i=mxbl+1;i<=cnt;i++){
		for(int j=1;j<=mxbl;j++)
			cout<<ed[i][j]<<"("<<i<<"->"<<j<<") ";
		cout<<endl;
	}
	for(int i=1;i<=top;i++)cout<<stk[i]<<" ";
	cout<<top<<endl;
*/
