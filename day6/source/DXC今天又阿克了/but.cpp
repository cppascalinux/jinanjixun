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
struct pt{int x,y;} p[1010100];
inline pt operator + (pt p,pt q){
	return (pt){p.x+q.x,p.y+q.y};
}
inline pt operator - (pt p,pt q){
	return (pt){p.x-q.x,p.y-q.y};
}
inline ll operator ^ (pt p,pt q){
	return 1ll*p.x*q.y-1ll*p.y*q.x;
}
int n,val[1010100],Sum[55][55][55];
inline int Gao (int i,int j,int k) {
	ll pp=(p[k]-p[i])^(p[j]-p[i]);
	return pp>0;
}
inline void Init(){
	for(rint i=1;i<=n;++i) {
		for(rint j=i+1;j<=n;++j) {
			for(rint k=j+1;k<=n;++k) {
				Sum[i][j][k]=0;
				for(rint t=1;t<=n;++t) {
					if(t==i||t==j||t==k) continue;
					int x1=Gao(i,j,t),x2=Gao(j,k,t),x3=Gao(k,i,t);
					if(x1==x2&&x1==x3) {
						Sum[i][j][k]+=val[t];
					}
				}
				Sum[j][i][k]=Sum[k][i][j]=Sum[j][k][i]=Sum[k][j][i]=Sum[i][k][j]=Sum[i][j][k];
			}
		}
	}
}
int o[101100],f[51][51][51];
int Ans[55];
inline bool cmp(int i,int j){if(p[i].x!=p[j].x)return p[i].x<p[j].x;else return p[i].y>p[j].y;}
inline void Solve(){
	for(rint i=1;i<=n;++i) o[i]=i;
	sort(o+1,o+n+1,cmp);
	memset(Ans,0x3f,sizeof(Ans));
	for(rint i=1;i<=n;++i) {
		memset(f,0x3f,sizeof(f));
		for(rint j=i+1;j<=n;++j) {
			f[i][j][2]=val[o[i]]+val[o[j]];
		}
		for(rint k=2;k<=n;++k) {
			for(rint P=i;P<=n;++P) {
				for(rint q=i;q<=n;++q) {
					if(f[P][q][k]<1e9) {
						for(rint nxt=i;nxt<=n;++nxt) {
							if(nxt==P||nxt==q) continue;
							int x=o[nxt],y=o[P],z=o[q];
							if(((p[x]-p[z])^(p[z]-p[y]))>=0) continue;
							if(((p[o[i]]-p[x])^(p[x]-p[z]))>=0&&nxt!=i) continue;
							if(nxt==i) {
								Ans[k]=min(Ans[k],f[P][q][k]);
								continue;
							}
							f[q][nxt][k+1]=min(f[q][nxt][k+1],f[P][q][k]+val[o[nxt]]+Sum[o[nxt]][o[q]][o[i]]);
						}
					}
				}
			}
		}
	}
	for(rint i=3;i<=n;++i) {
		if(Ans[i]>1e9) cout<<-1<<" ";
		else cout<<Ans[i]<<" ";
	}
}
int main(){
	freopen("but.in","r",stdin);
	freopen("but.out","w",stdout);
	n=read();
	for(rint i=1;i<=n;++i) {
		p[i].x=read(),p[i].y=read(),val[i]=read();
	}
	Init();
	Solve();
	return 0;
}
