#include<bits/stdc++.h>
#define ll long long
#define mk make_pair
#define pb push_back
#define pa pair<int,int>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<"\n"
#define fir first
#define sec second
#define SZ(x) (x).size()
using namespace std;
const int mod = 998244353;
inline int read(){int w=1,s=0;char ch=getchar();while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();} while(isdigit(ch)){s=s*10+ch-'0';ch=getchar();} return w*s;}
int f[5050][5050],n,k;
inline int pls(int a,int b){a+=b;return a>=mod?a-mod:a;}
int main(){
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	n=read(),k=read();
	f[1][1]=1;
	for(rint i=1;i<=n;++i) {
		for(rint j=1;j<=i;++j) {
			if(i==1&&j==1) continue;
			f[i][j]=pls(f[i-1][j-1],1ll*j*f[i-1][j]%mod);
			if(j>=2){
				f[i][j]=pls(f[i][j],1ll*(i-j+1)*f[i-1][j-2]%mod);
			}
		}
	}
	cout<<f[n][k];
	return 0;
}
