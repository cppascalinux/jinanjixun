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
inline int read(){int w=1,s=0;char ch=getchar();while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();} while(isdigit(ch)){s=s*10+ch-'0';ch=getchar();} return w*s;}
int T,n,m,A[1010100],Sum1[1011010],Sum2[1010100];
int main() {
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	T=read();
	while(T--) {
		n=read(),m=read();
		int fl=0;
		for(rint i=1;i<=n;++i) A[i]=read(),A[i]%=2;
		if(n==1) {
			if(A[1]==1) {
				cout<<"B\n";
			}
			else cout<<"A\n";
			continue;
		}
		for(rint i=1;i<=n;++i) if(A[i]==0&&(i&1)) fl++;
//		memset(Sum1,0,sizeof(Sum1));
//		memset(Sum2,0,sizeof(Sum2));
		for(rint i=1;i<=n;++i) if(i&1) Sum1[i]=Sum1[i-1]+A[i],Sum2[i]=Sum2[i-1];else Sum2[i]=Sum2[i-1]+A[i],Sum1[i]=Sum1[i-1];
		if(m==0) {
			if(!(n&1)) cout<<"A\n";
			else {
				if(!fl) cout<<"B\n";
				else cout<<"A\n";
			}
		}
		else {
			if(!(n&1)){
				int all=n/2;
				int fl=0;
				for(rint i=1;i<n;++i) {
					int tmp=0;
					if(i&1) {
						tmp=Sum1[i-1];
						if((A[i]!=0)||(A[i+1]!=0)) tmp++;
						tmp+=Sum2[n]-Sum2[i+1];
					}
					else  {
						tmp=Sum1[i-1];
						tmp+=Sum1[n]-Sum1[i+1];
					}
					if(tmp==all) fl=1;
				}
				if(fl) cout<<"B\n";
				else cout<<"A\n";
			}
			else cout<<"A\n";
		}
	}
	return 0;
}	
