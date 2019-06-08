#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mk make_pair
#define rint register int
using namespace std;
const int mod = 1e9+7;
inline int read(){int w=1,s=0;char ch=getchar();while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}while(isdigit(ch)){s=s*10+ch-'0';ch=getchar();}return w*s;}
typedef pair<int,int> pa;
int Sum[100010];
int T,n;pa tmp1[1000100],tmp2[1000100],A[1000100];int fa[1000010],rk[1000100],Pos[1000010];
inline ll ksm(ll x,ll y){ll res=1;while(y){if(y&1) res=res*x%mod;y>>=1;x=x*x%mod;}return res;}
inline bool cmp(int p,int q){
    return A[p]<A[q];
} 
inline int find(int x){if(fa[x]==x) return x;else return fa[x]=find(fa[x]);}
inline int lowbit(int x){return x&(-x);}
inline void add(int x){
    while(x<=n) Sum[x]^=1,x+=lowbit(x);
}
inline int Qry(int x){
    int res=0;while(x) res^=Sum[x],x-=lowbit(x);return res;
}
inline int Solve(){
    memset(Sum,0,sizeof(Sum));
    for(rint i=1;i<=n;++i) fa[i]=i,rk[i]=i;
    sort(rk+1,rk+n+1,cmp);
    for(rint i=n;i;--i){
        int x=rk[i];
        int l=A[x].first,r=A[x].second;
        int t=find(r);
        if(t<l) return 0;
        fa[t]=l-1;Pos[x]=t;
    }int fl=1;
    for(rint i=n;i;--i){
        if(Qry(Pos[i])) fl=mod-fl;
        add(Pos[i]);
    }ll res=1;
    for(rint i=1;i<=n;++i) res=res*ksm(A[i].second-A[i].first+1,mod-2)%mod;
    res=res*fl%mod;
    return res;
}
int main()
{	freopen("determinant.in","r",stdin);
	freopen("determinant.out","w",stdout);
    T=read();
    while(T--){ n=read();
        for(rint i=1;i<=n;++i) tmp1[i].first=read(),tmp1[i].second=read(),tmp2[i].first=read(),tmp2[i].second=read();
        int ans1=1;memcpy(A,tmp1,sizeof(A));ans1=Solve();
        int ans2=1;memcpy(A,tmp2,sizeof(A));ans2=Solve();
//      cout<<ans1<<" "<<ans2<<"\n";
        cout<<1ll*ans1*ans2%mod<<"\n";
    }
    return 0;
}

