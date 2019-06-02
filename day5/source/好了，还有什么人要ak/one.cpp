#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
#include<iostream>
#include<cstring>
#define ll long long
#define maxn 640
#define re(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int read(){char c=getchar();int f=1;int ans = 0;while(c>'9'||c<'0'){if(c=='-')f=-f;c=getchar();}while(c<='9'&&c>='0'){ans =ans*10+c-'0';c=getchar();}return ans*f;}
//_____________________________________________________________________________________________________
int n,m,cnt,A[25],S,T;
ll a[1005][25],to[maxn][maxn],E[maxn][maxn],sum[maxn];
void dfs(int x,int limit,int dep)
{
	if(x<0||dep>n+1)return;
	if(x==0)
	{
		++cnt;
		re(i,1,dep-1) a[cnt][i] = A[i];
		return;
	}
	re(i,0,x)
	{
		A[dep] = i;
		dfs(x-i*dep,i,dep+1);
	}
}
#define p 1000000007
inline ll ksm( ll x,ll b)
{
	ll ans = 1;
	while(b)
	{
		if(b&1) ans = ans * x %p;
		x = x*x %p;
		b>>=1;
	}
	return ans;
}
ll dp[maxn][maxn],answer[maxn],fac[21];
#define pr(x) printf("%d ",x)
#define P printf("\n")
int seq[21],vis[maxn],times[21];
int main()
{
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	n = read();
	fac[0] = 1;re(i,1,n) fac[i] = fac[i-1] * i %p;
	re(i,1,n) seq[i] = read();
	re(i,1,n)
	{
		int x = seq[i] , tot = 0;
		while(!vis[x])
		{
			vis[x] = 1;
			tot++;
			x = seq[x];
		}
		times[tot]++;
	}
	dfs(n,1,1);
//	re(i,1,n) pr(times[i]);P;
	re(i,1,cnt)
	{
		int bo = 1;
		re(j,1,n) if( a[i][j]!=times[j] ) bo = 0;
		if(bo) 
		{
			T = i;
			re(j,1,n) swap( a[i][j],a[cnt][j] );
			break;
		}
	}
/*	pr(T);
	P;
	re(i,1,cnt)
	{
		re(j,1,n) pr(a[i][j]);
		P;
	}*/
	re(i,1,cnt)
		re(j,1,cnt)
		if(i!=j)
		{
			int x = 0,y = 0,res = 2,bo=0,able=1;
		//	pr(i);pr(j);P;
			re(k,1,n)
			{
				if(!able) break;
				int t = a[i][k]-a[j][k];
			//	pr(t);
				switch(t)
				{
					case 0 :
						break;
					case 1 :
						res--;
						if(res<0)
							able = 0;
						if(res) x=k;
						else y = k;
						break;
					case 2:
						res-=2;
						if(res<0)
							able = 0;
						x = y = k;
						break;
					case -1:
						if(bo) able = 0;
						bo = 1;
						break;
					default : 
						able = 0;
				}
						
			}
			if(!able)continue;
		//	pr(i);pr(j);pr(x);pr(y);P;
			
			ll mul = 1;
			
			re(k,1,n)
				mul = mul * fac[a[i][k]] %p * ksm( k,a[i][k] ) %p;
			
		//	pr(mul);P;
			
			to[i][j] = to[j][i] = 
				( x==y?a[i][x]*(a[i][x]-1)/2 : a[i][x]*a[i][y] ) * x * y %p * fac[n] %p * ksm( mul,p-2 )%p ;
		}
	
	/*re(i,1,cnt){re(j,1,cnt)pr(to[i][j]);P;}
	*/
	re(i,1,cnt)
		re(j,1,cnt)
		sum[i] = (sum[i]+to[i][j])%p;
	re(i,1,cnt)
		re(j,1,cnt)
		
		{
			if(i==j)dp[i][j] = 1;
			else if(j!=T)
			{
				dp[i][j] = -to[j][i]*ksm( sum[j],p-2 )%p;
			//	pr(i);pr(j);pr(dp[i][j]);P;
				answer[i] += -dp[i][j];
			}	
		}	
	
	
/*	P;
		re(i,1,cnt){re(j,1,cnt)pr(dp[i][j]);pr(answer[i]);P;}
P;*/
	
	re(i,1,cnt)
	{
		int j = i;
		while(!dp[j][i]) j++;
		re(t,i,cnt) swap(dp[j][t],dp[i][t]);
		swap( answer[j],answer[i] );
		
		re(j,i+1,cnt)
		{
			ll k = -dp[j][i] * ksm( dp[i][i],p-2 )%p;
			re(t,i,cnt)
				dp[j][t] = ( dp[j][t]+k*dp[i][t] ) %p;
			answer[j] = ( answer[j]+k*answer[i] )%p; 
		}
	}	
//	re(i,1,cnt){re(j,1,cnt)pr(dp[i][j]);pr(answer[i]);P;}
	
	printf("%lld\n",(p+answer[cnt]*ksm( dp[cnt][cnt],p-2 )%p)%p);
    return 0;
}

