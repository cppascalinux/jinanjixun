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
#define N 650
using namespace std;
const int mod = 1e9+7;
inline int read(){int w=1,s=0;char ch=getchar();while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();} while(isdigit(ch)){s=s*10+ch-'0';ch=getchar();} return w*s;}
int n,A[1010100],vis[1010100],tot,cnt;
inline ll ksm(ll x,ll y){ll res=1;while(y){if(y&1) res=res*x%mod;x=x*x%mod;y>>=1;} return res;}
inline int pls(int a,int b){a+=b;return a>=mod?a-mod:a;}
inline int mns(int a,int b){a-=b;return a<0?a+mod:a;}
vector<int> vec,o,K[101010];
map<vector<int>,int> mp;
int M[N][N];
inline void Gao(int now){
	vis[now]=1;
	++tot;
	if(!vis[A[now]]) Gao(A[now]);
}
inline void DFS(int cur,int las){
	if(!cur){
		K[++cnt]=vec;
		mp[vec]=cnt;
		return ;
	}
	for(rint i=las;i<=cur;++i) {
		vec.pb(i);
		DFS(cur-i,i);
		vec.pop_back();
	}
}
inline void Build(){
	for(rint i=1;i<=cnt;++i) {
//		debug(i);
		if(SZ(K[i])==n){
			M[i][i]=1;
			M[i][cnt+1]=0;
//			debug(i);
		}
		else {
			int tt=0;
			vector<int> nw;
			M[i][i]=1;M[i][cnt+1]=1;
			for(rint j=0;j<SZ(K[i]);++j) {
//				debug(K[i][j]);
				int x=K[i][j];
				for(rint o=1;o<x;++o) {
					nw.clear();
					int to=x-o;
//					debug(to);
					int Inv=1ll*to*ksm(n*(n-1)/2,mod-2)%mod;
					tt+=to;
//					debug(Inv);
					for(rint k=0;k<SZ(K[i]);++k) if(k!=j) nw.pb(K[i][k]);
					nw.pb(o);nw.pb(x-o);
					sort(nw.begin(),nw.end());
					M[i][mp[nw]]=mns(M[i][mp[nw]],Inv);
				}
			}
//			debug(tt);
			for(rint j=0;j<SZ(K[i]);++j) {
				for(rint k=j+1;k<SZ(K[i]);++k) {
					nw.clear();nw.pb(K[i][j]+K[i][k]);
//					debug(K[i][j]);
//					debug(K[i][k]);
					for(rint p=0;p<SZ(K[i]);++p) {
						if(p==j) continue;if(p==k) continue;
						nw.pb(K[i][p]);
					}
					sort(nw.begin(),nw.end());
					int Inv=1ll*K[i][j]*K[i][k]%mod*ksm(n*(n-1)/2,mod-2)%mod;
					tt+=K[i][j]*K[i][k];
					M[i][mp[nw]]=mns(M[i][mp[nw]],Inv);
				}
			}
//			cout<<tt<<"\n";
		}
	}
}
inline void Gauss() {
	for(rint i=1;i<=cnt;++i) {
		int pos=i;
		for(rint j=i;j<=cnt;++j) {
			if(M[j][i]) pos=j;
		}
		swap(M[i],M[pos]);
		int Inv=ksm(M[i][i],mod-2);
		for(rint j=1;j<=cnt;++j){
			if(i==j) continue;
			int K=1ll*Inv*M[j][i]%mod;
			for(rint k=i;k<=cnt+1;++k) {
				M[j][k]=mns(M[j][k],1ll*M[i][k]*K%mod);
			}
		}
	}
	int x=mp[o];
	cout<<1ll*M[x][cnt+1]*ksm(M[x][x],mod-2)%mod;
}
int main(){
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	n=read();
	for(rint i=1;i<=n;++i) A[i]=read();
	for(rint i=1;i<=n;++i) if(!vis[i]) {tot=0;Gao(i);o.pb(tot);}
	sort(o.begin(),o.end());
//	debug(o[0]);
//	debug(o[1]);
	DFS(n,1);
//	debug(cnt);
	Build();
	Gauss();
	return 0;
}

