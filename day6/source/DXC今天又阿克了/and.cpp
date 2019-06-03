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
const int mod = 1e9+7;
inline int read(){int w=1,s=0;char ch=getchar();while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();} while(isdigit(ch)){s=s*10+ch-'0';ch=getchar();} return w*s;}
int n,A[101010],m,f1[31][2010],f2[31][2010];
inline int pls(int a,int b){a+=b;return a>=mod?a-mod:a;}
inline int mns(int a,int b){a-=b;return a<0?a+mod:a;}
inline int DFS1(int pos,int Sta1){
	if(pos==-1){
		return 1;
	}
	if(f1[pos][Sta1]!=-1) return f1[pos][Sta1];
	int res=0;
	int S=0;
	for(rint j=1;j<=n;++j) if(A[j]&(1<<pos)) S|=(1<<j-1);
	for(rint i=0;i<1<<n;++i) {
		if((S&i)!=i) continue;
		int nw=Sta1;
		for(rint j=0;j<n-1;++j) {
			if(Sta1&(1<<j)) continue;
			int x=(i&(1<<j))!=0;
			int y=(i&(1<<j+1))!=0;
			if(x>y) {nw=-1;break;}
			if(x<y) nw|=1<<j;
		}
		if(nw==-1) continue;
		res=pls(res,DFS1(pos-1,nw));
	}
	return f1[pos][Sta1]=res;
}
inline int DFS2(int pos,int Sta1){
	if(pos==-1){
		return 1;
	}
	if(f2[pos][Sta1]!=-1) return f2[pos][Sta1];
	int res=0;
	int S=0;
	for(rint j=1;j<=n;++j) if(A[j]&(1<<pos)) S|=(1<<j-1);
	for(rint i=0;i<1<<n;++i) {
		if((S&i)!=S) continue;
		int nw=Sta1;
		for(rint j=0;j<n-1;++j) {
			if(Sta1&(1<<j)) continue;
			int x=(i&(1<<j))!=0;
			int y=(i&(1<<j+1))!=0;
			if(x<y) {nw=-1;break;}
			if(x>y) nw|=1<<j;
		}
		if(nw==-1) continue;
		res=pls(res,DFS2(pos-1,nw));
	}
	return f2[pos][Sta1]=res;
}
int main(){
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	n=read(),m=read();
	memset(f1,-1,sizeof(f1));
	memset(f2,-1,sizeof(f2));
	for(rint i=1;i<=n;++i) A[i]=read();
//	debug(DFS1(m-1,0));
//	debug(DFS2(m-1,0));
	cout<<1ll*DFS1(m-1,0)*DFS2(m-1,0)%mod<<"\n";
	return 0;
}
