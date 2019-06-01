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
int n,q;
map<int,int> mp;
struct Linear_Base{
	int base[31];
	inline void Init(){memset(base,0,sizeof(base));}
	inline void Insert(int x){
		for(rint i=30;i>=0;--i) {
			if((1<<i)&x)
			{
				if(!base[i]){
					base[i]=x;
				}x^=base[i];
			}
		}
	}
	inline int get() {
		int res=0;
		for(rint i=0;i<=30;++i) if(base[i]) res++;
		return 1<<res;
	}
};
struct Segment_Tree{
	vector<int> tag[400100];Linear_Base S[400100];
	inline void insert(int now,int l,int r,int x,int y,int v){
		if(x<=l&&r<=y) {
			tag[now].pb(v);
			return ;
		}int mid=(l+r)>>1;
		if(x<=mid) insert(now<<1,l,mid,x,y,v);
		if(y>mid) insert(now<<1|1,mid+1,r,x,y,v);
	}
	inline void Gao(int now,int l,int r) {
		S[now].Init();
		if(now!=1) S[now]=S[now>>1];
		for(rint i=0;i<SZ(tag[now]);++i){
			int x=tag[now][i];
			S[now].Insert(x);
		}
		if(l==r) {
			cout<<S[now].get()<<"\n";
			return ;
		}
		int mid=(l+r)>>1;
		Gao(now<<1,l,mid);
		Gao(now<<1|1,mid+1,r);
	}
}Seg;
vector<int> vec;
int main() {
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	n=read(),q=read();
	for(rint i=1;i<=q;++i) {
		int opt=read(),x=read();
		vec.pb(x);
		if(opt==1){
			mp[x]=i;
		}
		else {
			Seg.insert(1,1,q,mp[x],i-1,x);
			mp[x]=0;
		}
	}
	for(rint i=0;i<SZ(vec);++i) {
		int x=vec[i];
		if(mp[x]) {
			Seg.insert(1,1,q,mp[x],q,x);
			mp[x]=0;
		}
	}
	Seg.Gao(1,1,q);
	return 0;
}	
