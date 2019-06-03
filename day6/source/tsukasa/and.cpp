#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;
#define mo 1000000007
#define MAXN 13

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

int n,m;
int b[MAXN];
int dp[33][1035];

int main()
{
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	n=read();m=read()-1;
	for (int i=1;i<=n;i++) b[i]=read();
//	memset(dp,0,sizeof(dp));
	dp[m+1][0]=1;
	for (int i=m+1;i>0;i--){
		for (int s=0;s<(1<<(n-1));s++){
			for (int j=0;j<(1<<(n));j++){
				bool flag=true;
				for (int k=1;k<n;k++) 
					if ((!(s&(1<<(k-1)))) && (j&(1<<(k-1))) && (!(j&(1<<k)))){
						flag=false; break;
					}
				if (!flag) continue;
				for (int k=0;k<n;k++) if ((j&(1<<k)) && (!(b[k+1]&(1<<(i-1))))){
					flag=false; break;
				}
				if (!flag) continue;
				int neww=s;
				for (int k=1;k<n;k++)
					if (!(j&(1<<(k-1))) && (j&(1<<k)))
						neww|=(1<<(k-1));
				dp[i-1][neww]=(dp[i-1][neww]+dp[i][s])%mo;
//				cout<<neww;
			}
		}
	}
	int ans1=0;
	for (int i=0;i<(1<<(n-1));i++) ans1=(ans1+dp[0][i])%mo;
//	for (int i=1;i<=n;i++) b[i]^=(1<<m)-1;
	memset(dp,0,sizeof(dp));
	dp[m+1][0]=1;
	for (int i=m+1;i>0;i--){
		for (int s=0;s<(1<<(n-1));s++){
			for (int j=0;j<(1<<(n));j++){
				bool flag=true;
				for (int k=1;k<n;k++) if ((!(s&(1<<(k-1)))) && (!(j&(1<<(k-1)))) && (j&(1<<k))){
					flag=false; break;
				}
				if (!flag) continue;
				for (int k=0;k<n;k++) if ((!(j&(1<<k))) && (b[k+1]&(1<<(i-1)))){
					flag=false; break;
				}
				if (!flag) continue;
				int neww=s;
				for (int k=1;k<n;k++)
					if ((j&(1<<(k-1))) && !(j&(1<<k)))
						neww|=(1<<(k-1));
				dp[i-1][neww]=(dp[i-1][neww]+dp[i][s])%mo;
			}
		}
	}
	int ans2=0;
	for (int i=0;i<(1<<(n-1));i++) ans2=(ans2+dp[0][i])%mo;
	printf("%lld",1ll*ans1*ans2%mo);
}
