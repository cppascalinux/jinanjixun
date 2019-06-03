#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
#include<iostream>
#include<cstring>
#define ll long long
#define maxn (1<<10)+5
#define re(i,a,b) for(int i=a;i<=b;i++)
#define p 1000000007

#define pr(x) printf("%d ",x)
#define P printf("\n")
#define p2(x) {for(int jo=m;jo;jo--) printf( "%d",(x>>jo-1)&1 );printf(" ");}
using namespace std;
inline int read(){char c=getchar();int f=1;int ans = 0;while(c>'9'||c<'0'){if(c=='-')f=-f;c=getchar();}while(c<='9'&&c>='0'){ans =ans*10+c-'0';c=getchar();}return ans*f;}
//_____________________________________________________________________________________________________
/*/int A[35][maxn],O[35][maxn];
bool check[2][maxn][maxn];
int solve(int w,int And,int Or)
{
	if(!w)return 1;
	if(~dp[w][And][Or]) return dp[w][And][Or];
	re(i,1,able[0][w][0])
		if(check[Or][able[0][w][i]]) O[w][++O[w][0]] = able[0][w][i] ; 
	re(i,1,able[1][w][0])
		if(check[And][able[1][w][i]]) A[w][++A[w][0]] = able[1][w][i] ; 
	ll ans = 0; 
	re(i,1,A[w][0])
		re(j,1,O[w][0])
		ans += solve( w-1,A[w][i],O[w][j] );
	A[w][0] = O[w][0] = 0;
	return dp[w][And][Or] = ans%p;
		
}*/
int n,m,b[15],a[15],cnt;
bool bo[15];
ll dp[2][35][15][15];

int main()
{
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
    n=read(),m=read();
  /*  //cnt = (1<<m)-1;
    re(w,1,m)
    	re(i,0,cnt)
    		re(j,0,cnt) dp[w][i][j] = -1;*/
    re(i,1,n) b[i] = read();
    re(l,1,n)
    	re(r,l,n) dp[0][0][l][r] = dp[1][0][l][r] = 1;
    	
    re(w,1,m)
    {
    	re(i,1,n) a[i] = (b[i]>>w-1)&1;
		re(l,1,n)
			re(r,l,n)
				re(k,0,1)
			{
				for(int t=r;t>=l&&a[t]==k;t--) dp[k][w][l][r] += (t==l?1:dp[k][w-1][l][t-1])*dp[k][w-1][t][r]%p;
				dp[k][w][l][r] += dp[k][w-1][l][r];
			//	for(int t=l;t<=r&&a[t];t++) 
			//	dp[1][w][l][r] += dp[1][w-1][l][t]*(t==r?1:dp[1][w-1][t+1][r])%p;
			//	dp[k][w][l][r] += dp[k][w-1][l][r];
				dp[k][w][l][r]%=p;//dp[1][w][l][r]%=p;
			//	pr(l);pr(r);pr(dp[0][w][l][r]);pr(dp[1][w][l][r]);P;
			}
	}
	printf("%lld\n",dp[1][m][1][n]*dp[0][m][1][n]%p);
    	
    	
   // re(i,1,m) 
   /*
    re(i,1,m)
    	re(j,0,cnt)
		{
    		if((j&a[i])==a[i])
    			able[0][i][ ++able[0][i][0] ] = j;
    		if((j&a[i])==j)
    			able[1][i][ ++able[1][i][0] ] = j;
		}
		*/
/*	re(i,1,m)
	{
		p2(a[i]);P;
		re(j,1,able[0][i][0]) p2(able[0][i][j]); P;
		re(j,1,able[1][i][0]) p2(able[1][i][j]); P;
		P;
		
	}	*/
		
/*	re(i,0,(1<<m-1)-1)
		re(j,0,cnt)
		{
			check[0][i][j] = check[1][i][j] = 1;
			re(k,1,m-1)
			{
				if(!((i>>k-1)&1)&&((j>>k-1)&1)&&!((j>>k)&1) ) check[0][i][j] = 0;
				if(!((i>>k-1)&1)&&!((j>>k-1)&1)&&((j>>k)&1) ) check[1][i][j] = 0;
			}	
		}*/
		
		
	//pr( solve1( m ) );
    return 0;
}

