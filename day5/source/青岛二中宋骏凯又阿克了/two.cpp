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
#define sit set<int>::iterator  
using namespace std;
inline int read(){int w=1,s=0;char ch=getchar();while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();} while(isdigit(ch)){s=s*10+ch-'0';ch=getchar();} return w*s;}
char s[1010100];int n,k;
struct node{int to,next;};
int Ans=0;
struct Segment_Tree{
	int cnt,Sum[20010100],ls[20110000],rs[20010000];
	inline void Modify(int &now,int l,int r,int pos,int d){
		if(!now) now=++cnt;Sum[now]+=d;
		if(l==r) return ;
		int mid=(l+r)>>1;
		if(pos<=mid) Modify(ls[now],l,mid,pos,d);
		else Modify(rs[now],mid+1,r,pos,d);
	}
//	inline int Merge(int x,int y,int l,int r) {
//		if(!x||!y) return x^y;
//		int mid=(l+r)>>1;
//		if(l==r) {
//			Sum[x]=Sum[x]+Sum[y];
//			return x;
//		}
//		ls[x]=Merge(ls[x],ls[y],l,mid);
//		rs[x]=Merge(rs[x],rs[y],mid+1,r);
//		Sum[x]=Sum[ls[x]]+Sum[rs[x]];
//		return x;
//	}
	inline int Qry(int now,int l,int r,int k){
		if(l==r) 
			return l;
		int mid=(l+r)>>1;
		if(Sum[ls[now]]>=k) return Qry(ls[now],l,mid,k);
		else return Qry(rs[now],mid+1,r,k-Sum[ls[now]]);
	}
	inline int get(int now,int l,int r,int x,int y){
		if(!now) return 0;
		if(x<=l&&r<=y) return Sum[now];
		int mid=(l+r)>>1,res=0;
		if(y<=mid) return get(ls[now],l,mid,x,y);
		if(x>mid) return get(rs[now],mid+1,r,x,y);
		return get(ls[now],l,mid,x,y)+get(rs[now],mid+1,r,x,y);
	}
}Seg;
struct SAM{
	int ch[200100][26],fa[200010],tag[200100],len[200100],cnt,las;
	node e[210100];int tot,h[210100],rt[200100];
	set<int> st[200100];
	inline void add(int from,int to){e[++tot].next=h[from];h[from]=tot;e[tot].to=to;}
	inline void Insert(int c,int pos)
    {
        int np=++cnt,p=las;
        las=np;len[np]=len[p]+1;
        while(p&&!ch[p][c]) ch[p][c]=np,p=fa[p];
        if(!p) fa[np]=1;
        else 
        {
            int q=ch[p][c];
            if(len[q]==len[p]+1) fa[np]=q;
            else 
            {
                int nq=++cnt;len[nq]=len[p]+1;
                memcpy(ch[nq],ch[q],sizeof(ch[nq]));
                fa[nq]=fa[q];fa[q]=fa[np]=nq;
                while(p&&ch[p][c]==q) ch[p][c]=nq,p=fa[p];
            }
        }
        tag[np]=pos; 
    }
	inline void DFS(int now,int ffa){
		if(tag[now]) st[now].insert(tag[now]);
		for(rint i=h[now];i;i=e[i].next) {
			int to=e[i].to;if(to==ffa) continue;
			DFS(to,now);
			if(st[now].size()>st[to].size()) {
				swap(st[now],st[to]);
				swap(rt[now],rt[to]);
			}
			for(sit o=st[to].begin();o!=st[to].end();++o) {
				int x=*o;
				int nxt=-1,las=-1;
				sit a=st[now].upper_bound(x);
				if(a!=st[now].end()) 
					nxt=*a;
				if(a!=st[now].begin())
					las=*(--a);
				if(nxt!=-1&&las!=-1) Seg.Modify(rt[now],1,n+2,nxt-las,-1);
				if(nxt!=-1) Seg.Modify(rt[now],1,n+2,nxt-x,1);
				if(las!=-1) Seg.Modify(rt[now],1,n+2,x-las,1);
				st[now].insert(x);
			}
		}
		if(now==1) return ;
		int L=len[fa[now]]+1,R=len[now];
		int all=st[now].size();
		if(all<k) return ;
		int nd=all-k;
		int Lp=Seg.Qry(rt[now],1,n+2,nd),Rp=Seg.Qry(rt[now],1,n+2,nd+1);
		Rp--;
		int tt=Seg.get(rt[now],1,n+2,1,Lp);
		if(Lp>Rp) return ;
		if(tt!=all-k) return ;
		L=max(L,Lp);
		R=min(R,Rp);
		Ans+=max((R-L+1),0);
	}
	inline void Solve() {
		cnt=las=1;
		for(rint i=1;i<=n;++i) Insert(s[i]-'a',i);
//		debug(cnt);
		for(rint i=2;i<=cnt;++i) add(fa[i],i);
		DFS(1,0);
	}
}S;
int main(){
	freopen("two.in","r",stdin);
	freopen("two.out","w",stdout);
	scanf("%s",s+1);k=read();n=strlen(s+1);
	S.Solve();
	cout<<Ans<<"\n";
	return 0;
}	
