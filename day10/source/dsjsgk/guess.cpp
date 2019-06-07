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
int n,val[1010101],las[500100][10],f[500100][221];
char s[1010100];
int main() {
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	for(rint i=1;i<=n;++i) val[i]=s[i]-'0';
	for(rint i=1;i<=n;++i) {
		memcpy(las[i],las[i-1],sizeof(las[i]));
		las[i][val[i]]=i;
//		for(rint j=1;j<=9;++j) cout<<las[i][j]<<" ";
//		cout<<endl; 
	}
	for(rint i=n+1;i>=1;--i) {
		f[i][0]=i;
//		debug(i);
		for(rint j=1;j<=200;++j) {
			f[i][j]=f[i][j-1];
			for(rint k=1;k<=min(9,j);++k) {
				int x=f[i][j-k];
				if(x==n+1) break;
				int t=las[x][k];
				if(!t) continue;
				if(t<i) continue;
				f[i][j]=max(f[i][j],f[t+1][j-k]);
			}
			if(f[i][j]==n+1) break;
		}
		for(rint j=1;j<=200;++j) {
			f[i][j]=max(f[i][j-1],f[i][j]);
		}//debug(i);
	}
	for(rint j=0;j<=200;++j) {
		if(f[1][j]==n+1){
			cout<<j<<"\n";
			exit(0);
		}
	}
	return 0;
}	
