#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
#define fgx cerr<<" -------------------------- "<<endl
#define LL long long
inline int read(){
	int nm=0; bool fh=true; char cw=getchar();
	for(;!isdigit(cw);cw=getchar()) fh^=(cw=='-');
	for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
	return fh?nm:-nm;
}
#define M 52
#define INF 987654321
struct PT{
	int x,y; PT(){} PT(int _x,int _y){x=_x,y=_y;}
	inline PT operator + (const PT&ot){return PT(x+ot.x,y+ot.y);}
	inline PT operator - (const PT&ot){return PT(x-ot.x,y-ot.y);}
	inline LL operator * (const PT&ot){return (LL)x*(LL)ot.y-(LL)y*(LL)ot.x;}
};
struct node{PT k; int val,id;}p[M];
int n,m,w[M],sm[M][M][M],F[M][M][M],ans[M];
bool cmpy(node i,node j){return i.k.y<j.k.y;}
inline bool in(PT x,PT a,PT b,PT c){return abs((a-x)*(b-x))+abs((b-x)*(c-x))+abs((c-x)*(a-x))==abs(a*b+b*c+c*a);}
bool cmp(node i,node j){return i.k*j.k>0;}
inline void upd(int &x,int y){(x>y)?(x=y):0;}
inline int get_sm(node i,node j,node k){int a=i.id,b=j.id,c=k.id;return sm[a][b][c];}
inline void calc(int d){
	memset(F,0x3f,sizeof(F));
	for(int i=d+1;i<=n;i++) F[2][d][i]=p[d].val+p[i].val;
	for(int lm=2;lm<n-d+1;lm++) for(int i=d;i<=n;i++) for(int j=i+1;j<=n;j++) if(F[lm][i][j]<INF){
		for(int k=j+1;k<=n;k++){
			if((p[j].k-p[i].k)*(p[k].k-p[i].k)<0) continue;
			if((p[k].k-p[j].k)*(p[d].k-p[j].k)<0) break;
			upd(F[lm+1][j][k],F[lm][i][j]+get_sm(p[d],p[j],p[k])+p[k].val);
		}
	}
	for(int lm=3;lm<=n-d+1;lm++) for(int i=d+1;i<=n;i++) for(int j=i+1;j<=n;j++)
		upd(ans[lm],F[lm][i][j]);
}
int main(){
	freopen("but.in","r",stdin);
	freopen("but.out","w",stdout);
	n=read(),memset(ans,0x3f,sizeof(ans));
	for(int i=1;i<=n;i++) p[i].k.x=read(),p[i].k.y=read(),p[i].val=read(),p[i].id=i;
	for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) for(int k=j+1;k<=n;k++){
		for(int x=1;x<=n;x++) if(x!=i&&x!=j&&x!=k&&in(p[x].k,p[i].k,p[j].k,p[k].k)) sm[i][j][k]+=p[x].val;
		sm[i][k][j]=sm[j][i][k]=sm[j][k][i]=sm[k][i][j]=sm[k][j][i]=sm[i][j][k];  
	}
	sort(p+1,p+n+1,cmpy);
	for(int j=n-1;j>1;--j){
		for(int i=1;i<=n;i++) if(i^(j-1)) p[i].k=p[i].k-p[j-1].k;
		p[j-1].k.x=p[j-1].k.y=0,sort(p+j,p+n+1,cmp),calc(j-1);
	}
	for(int i=3;i<=n;i++) if(ans[i]>=INF) ans[i]=-1;
	for(int i=3;i<=n;i++) printf("%d%c",ans[i],i<n?' ':'\n');
	return 0;
}
