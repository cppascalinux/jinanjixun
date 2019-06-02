#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
#define LL long long
#define fgx cerr<<" ---------------------------------------------- "<<endl
inline int read(){
	int nm=0; bool fh=true; char cw=getchar();
	for(;!isdigit(cw);cw=getchar()) fh^=(cw=='-');
	for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
	return fh?nm:-nm;
}
#define M 200
int n,m,F[M][M],t[M*M];
char ch[M*M]; LL ans;
int main(){
	freopen("three.in","r",stdin);
	freopen("three.out","w",stdout);
	n=read();
	scanf("%s",ch);
	if(n>=M){puts("0");return 0;}
	for(int i=0;i<n;i++) t[i]=t[i+n]=ch[i]-'0';
	for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) for(int k=j+1;k<n;k++){
		if(!(t[i]|t[j]|t[k])){continue;}
		int t1=j-i,t2=k-j,t3=i+n-k;
		if(t1>t2) swap(t1,t2); if(t2>t3) swap(t2,t3); if(t1>t2) swap(t1,t2);
		F[t1][t2]++;
	}
	for(int i=1;i<n;i++) for(int j=i;j<n;j++)
		ans+=(LL)F[i][j]*(LL)(F[i][j]-1);
	printf("%lld\n",ans>>1); return 0;
}
