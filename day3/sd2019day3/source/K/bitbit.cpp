#include<bits/stdc++.h>
#define For for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
#define FOR for(int i=1;i<=n;i++,putchar('\n')) for(int j=1;j<=m;j++)
const int N=505;
int f[N][N],b[N*N],num,n,m;
bool a[N][N],used[N][N],a1[N][N],a2[N][N],a3[N][N],F;
void dfs(int x,int y,int s){
	if(!a[x][y]||f[x][y]) return;
	f[x][y]=s,dfs(x+1,y,s),dfs(x-1,y,s),dfs(x,y+1,s),dfs(x,y-1,s);
}
void dfs(int x,int y){
	if(x>n||y>m||!x||!y||used[x][y]) return;
	if(a[x][y]){b[++num]=f[x][y];return;}
	used[x][y]=1,dfs(x+1,y),dfs(x-1,y),dfs(x,y+1),dfs(x,y-1);
}
int main(){
	int s=0;
	freopen("bitbit.in","r",stdin),freopen("bitbit.out","w",stdout);
	scanf("%d%d",&n,&m);
	For{scanf("%1d",&a[i][j]);if(a[i][j]) F=1;}
	if(!F) return !printf("0");
	For if(a[i][j]&&!f[i][j]) s++,dfs(i,j,s);
	if(n==1||m==1){
		bool P=n!=1;
		printf("%d\n",s);
		if(m==1) for(int i=1;i<=n;i++) a[1][i]=a[i][1],m=n;
		while(s--){
			bool F=1;
			printf("+\n");
			for(int i=1;i<=m;i++){
				if(!a[1][i]&&a[1][i-1]) F=0;
				putchar((F&a[1][i])^48);
				if(P) putchar('\n');
			}
			for(int i=1;i<=m;i++){if(a[1][i]&&!a[1][i+1]){a[1][i]=0;break;}a[1][i]=0;}
			if(!P) putchar('\n');
		}
		return 0;
	}
	if(s==1){printf("1\n+\n");FOR putchar(a[i][j]^48);return 0;}
	For{
		int k=0;
		if(!a[i][j]&&!f[i][j]) num=0,dfs(i,j);
		std::sort(b+1,b+num+1);
		for(int i=1;i<=num;i++) k+=b[i]!=b[i-1];
		if(k==s){
			printf("2\n+\n"),memset(used,0,sizeof used),num=0,dfs(i,j);
			FOR putchar((a[i][j]|used[i][j])^48);
			printf("-\n");FOR putchar(used[i][j]^48);
			return 0;
		}
	}
	For a1[i][j]=(a[i][j]|i&1);
	For a2[i][j]=(a[i][j]|!(i&1));
	For a3[i][j]=1;
	for(int i=1;i<=n;i++) if(!a1[i][1]) a1[i][1]=1,a2[i][1]=0;
	for(int i=1;i<=n;i++) if(!a2[i][m]) a2[i][m]=1,a1[i][m]=0;
	for(int i=1;i<=n;i++) if(a1[i][m]) a1[i][m]=0,a3[i][m]=0;
	for(int i=1;i<=n;i++) if(a2[i][1]) a2[i][1]=0,a3[i][1]=0;
	printf("3\n+\n");FOR putchar(a1[i][j]^48);
	printf("+\n");FOR putchar(a2[i][j]^48);
	printf("-\n");FOR putchar(a3[i][j]^48);
	return 0;
}
