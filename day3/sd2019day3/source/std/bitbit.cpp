#include<bits/stdc++.h>
using namespace std;
const int maxn=5010;
int n,m,dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
char s[maxn][maxn],ss[maxn][maxn];
int vs[maxn][maxn],col[maxn*maxn],O;
void dfs(int x,int y,int zz=1){
	vs[x][y]=zz;
	for(int i=0;i<4;++i){
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<1||xx>n||yy<1||yy>m)continue;
		if(s[xx][yy]!='1'||vs[xx][yy])continue;
		vs[xx][yy]=zz;
		dfs(xx,yy,zz);
	}
}

void dfs0(int x,int y,int tg){
	vs[x][y]=tg;
	for(int i=0;i<4;++i){
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<1||xx>n||yy<1||yy>m)continue;
		if(vs[xx][yy]>0&&col[vs[xx][yy]]!=tg){
			col[vs[xx][yy]]=tg;
			O++;
		}
		if(s[xx][yy]!='0'||vs[xx][yy])continue;
		vs[xx][yy]=tg;
		dfs0(xx,yy,tg);
	}
}
int sol1(){
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			vs[i][j]=0;
	int flg=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)if(s[i][j]=='1'&&!vs[i][j]){
			if(flg)return false;
			flg=1;
			dfs(i,j);
		}
	if(flg){
		printf("1\n+\n");
		for(int i=1;i<=n;++i,puts(""))
			for(int j=1;j<=m;++j)
				printf("%c",s[i][j]);
	} else {
		printf("0\n");
	} 
	return true;
}
int sol2(){
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			vs[i][j]=0;
	int ptr=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)if(s[i][j]=='1'&&!vs[i][j])
			dfs(i,j,++ptr);
	for(int i=1;i<=ptr;++i)col[i]=0;
	int tg=-1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)if(s[i][j]=='0'&&!vs[i][j]){
			O=0;
			dfs0(i,j,--tg);
			if(O==ptr){
				printf("2\n+\n");
				for(int i=1;i<=n;++i,puts(""))
					for(int j=1;j<=m;++j)
						printf("%c",s[i][j]=='1'||vs[i][j]==tg?'1':'0');
				printf("-\n");
				for(int i=1;i<=n;++i,puts(""))
					for(int j=1;j<=m;++j)
						printf("%c",vs[i][j]==tg?'1':'0');
				return true;
			}
		}
//	for(int i=1;i<=n;++i,puts(""))
//		for(int j=1;j<=m;++j)
//			printf("%d ",vs[i][j]);
	return false;
}
void sol3(int revflg=0){
	printf("3\n+\n");
	if(revflg==0){
		for(int i=1;i<=n;++i,puts(""))
			for(int j=1;j<=m;++j)
				printf("%c",i!=n&&(i==1||j%2==1||s[i][j]=='1')?'1':'0');	
	} else {
		for(int j=1;j<=m;++j,puts(""))
			for(int i=1;i<=n;++i)
				printf("%c",i!=n&&(i==1||j%2==1||s[i][j]=='1')?'1':'0');	
	}
	printf("+\n");
	if(revflg==0){
		for(int i=1;i<=n;++i,puts(""))
			for(int j=1;j<=m;++j)
				printf("%c",i!=1&&(i==n||j%2==0||s[i][j]=='1')?'1':'0');
	} else {
		for(int j=1;j<=m;++j,puts(""))
			for(int i=1;i<=n;++i)
				printf("%c",i!=1&&(i==n||j%2==0||s[i][j]=='1')?'1':'0');
	}
	printf("-\n");
	if(revflg==0){
		for(int i=1;i<=n;++i,puts(""))
			for(int j=1;j<=m;++j)
				printf("%c",(i==1||i==n)&&(s[i][j]=='1')?'0':'1');	
	} else {
		for(int j=1;j<=m;++j,puts(""))
			for(int i=1;i<=n;++i)
				printf("%c",(i==1||i==n)&&(s[i][j]=='1')?'0':'1');
	}
}
int pre[maxn]; 
int sol(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%s",s[i]+1);
	if(sol1())return 0;
	if(sol2())return 0;
	int revflg=0;
	if(m==1){
		revflg=1;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				ss[j][i]=s[i][j];
		swap(n,m);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				s[i][j]=ss[i][j];
	} else if(n==2){
		revflg=1;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				ss[j][i]=s[i][j];
		swap(n,m);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				s[i][j]=ss[i][j];
//		for(int i=1;i<=n;++i,puts(""))
//			for(int j=1;j<=m;++j)
//				printf("%c",s[i][j]); 
	}
	if(n==1){
		for(int i=1;i<=m;++i)pre[i]=i;
		for(int i=2;i<=m;++i)if(s[1][i]==s[1][i-1]){
			pre[i]=pre[i-1];
		} else pre[i]=i;
		int cnt=0,cnt2=0;
		for(int i=1;i<=m;++i)
			if(s[1][i]=='1'&&pre[i]==i)cnt++;
			else if(s[1][i]=='0'&&pre[i]==i)cnt2++;
		printf("%d",min(cnt,cnt2+1));
		if(cnt<cnt2+1){
			for(int i=1;i<=m;++i)if(s[1][i]=='1'&&pre[i]==i){
				printf("\n+\n");
				if(revflg==0){
					for(int j=1;j<=m;++j)
						if(pre[j]==i)printf("1");
						else printf("0");	
				} else {
					for(int j=1;j<=m;++j)
						if(pre[j]==i)printf("1\n");
						else printf("0\n");
				}
	 		}
		} else {
			printf("\n+\n");
			if(revflg==0){
				for(int i=1;i<=m;++i)printf("1");
			} else {
				for(int i=1;i<=m;++i)printf("1\n");
			}
			for(int i=1;i<=m;++i)if(s[1][i]=='0'&&pre[i]==i){
				printf("\n-\n");
				if(revflg==0){
					for(int j=1;j<=m;++j)
						if(pre[j]==i)printf("1");
						else printf("0");	
				} else {
					for(int j=1;j<=m;++j)
						if(pre[j]==i)printf("1\n");
						else printf("0\n");
				}
			}
		}
		puts("");
		return 0;
	}
	sol3(revflg);
}
int main(){
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	sol();
}
