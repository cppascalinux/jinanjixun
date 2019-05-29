#include<iostream>
#include<cstdio>
using namespace std;
#define int long long 
const int MOD=998244353,ny=873463809,N=30;
int n,m,k,w;
int a[N][N][N],b[N][N][N],s1[N][N][N],s2[N][N][N];
void exgcd(int a,int b,int &x,int &y){
    if(!b)x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
int calc1(int x1,int y1,int k1,int x2,int y2,int k2){
	return s1[x2][y2][k2]-s1[x1-1][y2][k2]-s1[x2][y1-1][k2]-s1[x2][y2][k1-1]+s1[x1-1][y1-1][k2]+s1[x1-1][y2][k1-1]+s1[x2][y1-1][k1-1]-s1[x1-1][y1-1][k1-1];
}
int calc2(int x1,int y1,int k1,int x2,int y2,int k2){
	return s2[x2][y2][k2]-s2[x1-1][y2][k2]-s2[x2][y1-1][k2]-s2[x2][y2][k1-1]+s2[x1-1][y1-1][k2]+s2[x1-1][y2][k1-1]+s2[x2][y1-1][k1-1]-s2[x1-1][y1-1][k1-1];
}
#undef int
int main()
{
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	#define int long long
	cin>>n>>m>>k>>w;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int tk=1;tk<=k;tk++)
				cin>>a[i][j][tk],a[i][j][tk]^=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int tk=1;tk<=k;tk++)
				cin>>b[i][j][tk];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int tk=1;tk<=k;tk++)
				s2[i][j][tk]=(s2[i-1][j][tk]+s2[i][j-1][tk]+s2[i][j][tk-1]-s2[i-1][j-1][tk]-s2[i-1][j][tk-1]-s2[i][j-1][tk-1]+s2[i-1][j-1][tk-1]+b[i][j][tk]+MOD)%MOD;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int tk=1;tk<=k;tk++)
				s1[i][j][tk]=(s1[i-1][j][tk]+s1[i][j-1][tk]+s1[i][j][tk-1]-s1[i-1][j-1][tk]-s1[i-1][j][tk-1]-s1[i][j-1][tk-1]+s1[i-1][j-1][tk-1]+a[i][j][tk]+MOD)%MOD;
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int tk=1;tk<=k;tk++)
				for(int i1=1;i1<=n;i1++)
					for(int j1=1;j1<=m;j1++)
						for(int t1=1;t1<=k;t1++)
							if(!calc1(i,j,tk,i1,j1,t1))
								ans=(ans+calc2(i,j,tk,i1,j1,t1))%MOD;
	int aa,ans2;
	int ans1=n*(n+1)%MOD*m%MOD*(m+1)%MOD*k%MOD*(k+1)%MOD*ny%MOD;
	exgcd(ans1,MOD,ans2,aa);
	int end=(ans2%MOD+MOD)%MOD*ans%MOD;
	cout<<end<<endl;
	fclose(stdin); fclose(stdout);
	return 0;
}
