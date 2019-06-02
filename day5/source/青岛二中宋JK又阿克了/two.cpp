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
#define M 300020
#define IT set<int>::iterator
int n,K; char ch[M]; LL ans;
struct Hp{
	struct Heap{
		priority_queue<int>Q,D;
		inline int Top(){while(!D.empty()&&Q.top()==D.top())D.pop(),Q.pop();return Q.top();}
		inline void Ins(int x){Q.push(x);}
		inline void Del(int x){D.push(x);}
		inline int Sz(){return Q.size()-D.size();}
	} Bg,Sm;
	inline void del(int x){
		if(Sm.Sz()>0&&Sm.Top()>=x) Sm.Del(x);
		else{Bg.Del(-x);if(Bg.Sz()<K&&Sm.Sz()>0)Bg.Ins(-Sm.Top()),Sm.Del(Sm.Top());}
	}
	inline void ins(int x){
		if(Bg.Sz()<K||!K||x>=-Bg.Top()){
			Bg.Ins(-x);
			if(Bg.Sz()>K) Sm.Ins(-Bg.Top()),Bg.Del(Bg.Top());
		} else Sm.Ins(x);
	}
	inline int BG(){return Bg.Sz()?-Bg.Top():(n+n);}
	inline int SM(){return Sm.Sz()?Sm.Top():(-n-n);}
	inline int sz(){return Bg.Sz()+Sm.Sz();}
};
#define M 300020
namespace SAM{
	int t[M][26],fa[M],len[M],ed,cnt,nw; Hp p[M];
	int H[M],C[M],id[M];
	set<int> T[M];
	inline void init(){cnt=ed=1,nw=0;}
	inline void extend(int c){
		int x=ed; len[ed=++cnt]=++nw,T[cnt].insert(nw);
		while(x&&!t[x][c]) t[x][c]=ed,x=fa[x];
		if(!x){fa[ed]=1;return;} int y=t[x][c];
		if(len[y]==len[x]+1){fa[ed]=y;return;}
		int now=++cnt; len[now]=len[x]+1;
		fa[now]=fa[y],fa[y]=fa[ed]=now;
		memcpy(t[now],t[y],sizeof(t[y]));
		while(x&&t[x][c]==y) t[x][c]=now,x=fa[x];
	}
	inline void solve(){
		for(int i=1;i<=cnt;i++) C[len[i]]++;
		for(int i=1;i<=nw;i++) C[i]+=C[i-1];
		for(int i=1;i<=cnt;i++) H[C[len[i]]--]=i,id[i]=i;
//		for(int i=1;i<=cnt;i++) debug(i)sp,debug(H[i])el;
		for(int i=cnt;i>=2;i--){
			int x=H[i],t1=id[fa[x]],t2=id[x];
			if(p[t2].sz()>=K) ans+=max(min(len[x],p[t2].BG()-1)-max(len[fa[x]]+1,p[t2].SM())+1,0);
//			debug(x)sp,debug(len[x])sp,debug(len[fa[x]]+1)el;
//			debug(p[t2].BG())sp,debug(p[t2].SM())el;
//			debug(p[t2].sz())el;
//			for(IT it=T[t2].begin();it!=T[t2].end();it++) debug((*it))sp; cerr el;
//			debug(ans)el;
//			for(IT it=T[t1].begin();it!=T[t1].end();it++) debug((*it))sp; cerr el;
			if(T[t1].size()<T[t2].size()) swap(t1,t2),swap(id[fa[x]],id[x]);
			for(IT it=T[t2].begin();it!=T[t2].end();it++){
				IT l=T[t1].lower_bound(*it),r=l;
				if(r==T[t1].begin()) p[t1].ins((*r)-(*it));
				else{   
					l--;
					if(r==T[t1].end()) p[t1].ins((*it)-(*l));//,debug(t1)el;
					else p[t1].del((*r)-(*l)),p[t1].ins((*r)-(*it)),p[t1].ins((*it)-(*l));
				} T[t1].insert(*it);
			}
		}
	}
}
int main(){
	freopen("two.in","r",stdin);
	freopen("two.out","w",stdout);
	scanf("%s",ch+1),n=strlen(ch+1),SAM::init(),K=read()-1;
	for(int i=1;i<=n;i++) SAM::extend(ch[i]-'a');
	SAM::solve(),printf("%lld\n",ans); return 0;
}
