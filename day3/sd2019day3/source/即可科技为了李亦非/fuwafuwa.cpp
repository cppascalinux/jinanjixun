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
int ls[550],rs[550],val[550],a,b,m,n,rt;
inline int Insert(int x,int y) {
	if(!x) return y;
	if(val[x]>val[y]) ls[x]=Insert(ls[x],y);
	else rs[x]=Insert(rs[x],y);
	return x;
}
inline void DFS(int now,int dep){
	if(!now) return ;
	if(now==n){
		cout<<dep<<"\n";
		return ;
	}
	DFS(ls[now],dep+1);
	DFS(rs[now],dep+1);
}
int main(){
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
	int T=read();
	while(T--) {
		a=read(),b=read(),m=read(),n=read();
		rt=0;
		memset(ls,0,sizeof(ls));
		memset(rs,0,sizeof(rs));
		for(rint k=1;k<=n;++k) {
			val[k]=(1ll*b*k+a)%m;
//			debug(k);
			rt=Insert(rt,k);
		}
		DFS(rt,0);
	}
	return 0;
}
