#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
typedef long long ll;
typedef pair<ll,int> pii;
const ll inf=1e18;
int n,fa[maxn],K,C,W;
ll ans,sum,val[maxn],anses[maxn];
pii sval[maxn];
vector<pii>G[maxn];
struct pxx{
	ll u,v,w;
	pxx(){}
	pxx(ll u,ll v,ll w):
		u(u),v(v),w(w){}
	pxx operator+(const ll x)const{return pxx(u,v,w+x);}
	pxx operator-(const ll x)const{return pxx(u,v,w-x);}
	pxx operator+(const pxx& x)const{
		pxx ret;
		ret.u=u;
		ret.v=x.u;
		if(ret.u<ret.v)swap(ret.u,ret.v);
		ret.w=w+x.w;
		return ret;
	}
	int operator<(const pxx& d)const{
		if(w!=d.w)return w<d.w;
		if(u!=d.u)return u<d.u;
		return v<d.v;
	}
}; 
struct data{
	pxx pre,suf,ans;
	ll sum;
	data(){}
	data(pxx pre,pxx suf,pxx ans,ll sum):
		pre(pre),suf(suf),ans(ans),sum(sum){}
	data operator+(const data& d)const{
		data ret;
		ret.pre=max(pre,d.pre+sum);
		ret.suf=max(suf+d.sum,d.suf);
		ret.ans=max(ans,d.ans);
		ret.ans=max(ret.ans,suf+d.pre);
		ret.sum=sum+d.sum;
		return ret;
	}
};
namespace LCT{
    int ch[maxn][2],fa[maxn],tg[maxn],ftg[maxn];
	ll val[maxn];
	multiset<pxx> st[maxn],stans[maxn];
	data dp[maxn];
	pxx cpre[maxn],cans[maxn];
   	data a[2][maxn],ra[2][maxn];
   	void clr(int n){
   		for(int i=1;i<=n;++i){
   			ch[i][0]=ch[i][1]=fa[i]=tg[i]=ftg[i]=val[i]=0;
   			st[i].clear(),stans[i].clear();
		}	
		memset(dp,0,sizeof(data)*n);
		memset(cpre,0,sizeof(pxx)*n);
		memset(cans,0,sizeof(pxx)*n);
		for(int i=0;i<2;++i){
			memset(a[i],0,sizeof(data)*n);
			memset(ra[i],0,sizeof(data)*n);
		}
	}
    void upd(int o){
    	int ls=ch[o][0],rs=ch[o][1];
    	if(o>n){
    		a[0][o]=ra[0][o]=data(dp[o].pre+val[o],dp[o].pre+val[o],dp[o].ans,val[o]);
    		a[1][o]=ra[1][o]=data(dp[o].pre-val[o],dp[o].pre-val[o],dp[o].ans,-val[o]);
		} else {
			a[1][o]=ra[1][o]=
			a[0][o]=ra[0][o]=data(dp[o].pre,dp[o].pre,max(dp[o].pre+pxx(o,0,0),dp[o].ans),0);
		}
		if(ls){
			for(int i=0;i<2;++i){
				a[i][o]=a[i][ls]+a[i][o];
				ra[i][o]=ra[i][o]+ra[i][ls];	
			}
		}
		if(rs){
			for(int i=0;i<2;++i){
				a[i][o]=a[i][o]+a[i][rs];
				ra[i][o]=ra[i][rs]+ra[i][o];	
			}
		}
    }
    void _pd(int o,int t,int ft){
		if(ft){
			ftg[o]^=1;
			swap(a[0][o],a[1][o]);
			swap(ra[0][o],ra[1][o]);
			val[o]=-val[o];
		}
		if(t){
			tg[o]^=1;
			swap(ch[o][0],ch[o][1]);
			swap(a[0][o],ra[0][o]);
			swap(a[1][o],ra[1][o]);
		}
	}
    void pd(int o){
    	if(ch[o][0])_pd(ch[o][0],tg[o],ftg[o]);
    	if(ch[o][1])_pd(ch[o][1],tg[o],ftg[o]);
    	tg[o]=ftg[o]=0;
    }
    bool isroot(int x){
        if(!x||!fa[x])return true;
        return ch[fa[x]][1]!=x&&ch[fa[x]][0]!=x;
    }
    void rotate(int p){
        int q=fa[p],y=fa[q],k=(ch[q][1]==p);
        if(!isroot(q))ch[y][ch[y][1]==q]=p;
        fa[ch[q][k]=ch[p][k^1]]=q;
        fa[ch[p][k^1]=q]=p,fa[p]=y;
        upd(q);
    }
    void splay(int x){
        int y;
        while(!isroot(x)){
            pd(fa[y=fa[x]]),pd(y),pd(x);
            if(!isroot(y)){
                if((ch[fa[y]][1]==y)^(ch[y][1]==x))rotate(x);
                else rotate(y); 
            }
            rotate(x);
        }
        pd(x),upd(x);
    }
    void uupd(int x){
    	if(x<=n){
	    	dp[x].pre=*st[x].rbegin();
	    	dp[x].ans=*stans[x].rbegin();
	    	if(st[x].size()>=2){
	    		auto it=st[x].end();
	    		dp[x].ans=max(dp[x].ans,*prev(it)+*prev(prev(it)));
			}
		} else {
			dp[x].pre=st[x].size()?*st[x].rbegin():pxx(0,0,-inf);
			dp[x].ans=stans[x].size()?*stans[x].rbegin():pxx(0,0,-inf);
			if(st[x].size()>=2){
	    		auto it=st[x].end();
	    		dp[x].ans=max(dp[x].ans,*prev(it)+*prev(prev(it))+val[x]);
			}
		}
    	
	}
    void cadd(int x,int y){
  	//	printf("cadd:(%d)<%lld,%lld,%lld>\n",y,a[0][y].ans.u,a[0][y].ans.v,a[0][y].ans.w);
    	st[x].insert(a[0][y].pre);
		stans[x].insert(a[0][y].ans);
    	uupd(x);
	}
	void del(int x,int y){
	//	printf("del:(%d)[%lld,%lld,%lld]\n",y,a[0][y].ans.u,a[0][y].ans.v,a[0][y].ans.w);
		st[x].erase(a[0][y].pre);
		stans[x].erase(a[0][y].ans);
		uupd(x);
	}
    void access(int x){
		for(int y=0;x;y=x,x=fa[x]){
			splay(x);
		//	printf("{%d,%d}",x,y);
			if(ch[x][1])cadd(x,ch[x][1]);
			if(y)del(x,y);
			ch[x][1]=y;
			upd(x);
		}
	}
	void rever(int x){
	    access(x),splay(x);
		_pd(x,1,0),pd(x);
	}
	void link(int u,int v){
		access(u),splay(u);
		rever(v);
		fa[v]=u;
		cadd(u,v);
		upd(u);
	}
	void mdy(int u,int v){
		rever(u),access(v),splay(v);
		_pd(v,0,1),pd(v);
	}
	void dfs(int u){
		pd(u);
		if(ch[u][0])dfs(ch[u][0]);
		printf("[%d[%d,%d](%lld,%lld,%lld,%d)]",u,ch[u][0],ch[u][1],dp[u].pre.w,a[0][u].ans.w,a[1][u].ans.w,a[1][u].sum);
		if(ch[u][1])dfs(ch[u][1]);
	}
};
int ptr=0;
void dfs(int u,int f){
	for(auto v:G[u])if(v.first!=f){
		dfs(v.first,u);
		LCT::fa[v.first]=v.second;
		LCT::cadd(v.second,v.first);
		LCT::fa[v.second]=u;
		LCT::upd(v.second);
		LCT::cadd(u,v.second);
		LCT::upd(u);
	}
	LCT::upd(u);
}
ll trsum[maxn],trcnt[maxn];
ll calzzz(ll x){
	ll nw=0,ans=0,nwcnt=0;
	for(int i=21;i>=0;--i){
		nw+=(1<<i);
		if(nw>K||trcnt[nw]+nwcnt>x)nw-=(1<<i);
		else nwcnt+=trcnt[nw],ans+=trsum[nw];
	}
	return ans+anses[x];
}
ll solans(ll K){
	int l=0,r=K-1;
	ll ans=calzzz(K);
	while(l<=r){
		int mid=l+r>>1;
		if(calzzz(mid)>calzzz(mid+1))l=mid+1,ans=min(ans,calzzz(mid+1));
		else r=mid-1,ans=min(ans,calzzz(mid));
	}
	return ans;
}
int main(){
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
//	freopen("..\\down\\3.in","r",stdin);
//	freopen("..\\down\\3.ans","w",stdout);
	scanf("%d%d",&n,&K);
	sum=0;
	ptr=n;
	LCT::clr(2*n);
	for(int i=1;i<=n;++i)G[i].clear();
	for(int i=1;i<=n;++i){
		LCT::st[i].insert(pxx(i,0,0));
		LCT::stans[i].insert(pxx(i,i,0));
		LCT::uupd(i),LCT::upd(i);
	}
	for(int i=2,u,v,w;i<=n;++i){
		scanf("%d%d%d",&u,&v,&w);
		++ptr;
		LCT::val[ptr]=w;
		LCT::uupd(ptr),LCT::upd(ptr);
		
		G[u].push_back(pii(v,ptr));
		G[v].push_back(pii(u,ptr));
		sum+=2*w;
	}
	dfs(1,0);
	for(int i=1;i<=K;++i)scanf("%lld",&val[i]),sval[i]=pii(val[i],i);
	sort(sval+1,sval+K+1);
	int flg=0;
	anses[0]=sum;
	printf("%lld ",solans(0));
	for(int i=1;i<=K;++i){
		int R=1;
		LCT::rever(R);
		pxx path=LCT::a[0][R].ans;
		sum-=path.w;
		anses[i]=sum;
		if(path.w==0&&!flg){
			flg=1;
			fprintf(stderr,"[%d]",i);
		}
		for(int x=lower_bound(sval+1,sval+K+1,pii(val[i],i))-sval;x<=K;x+=x&-x)
			trsum[x]+=val[i],trcnt[x]++;
		int u=path.u,v=path.v;
		LCT::mdy(u,v);
		printf("%lld ",solans(i));
	}
}

