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
struct node{int to,next,w;} e[10101001];
int n,m,tot,h[1010100];
inline void add(int from,int to,int w){e[++tot].next=h[from];h[from]=tot;e[tot].to=to;e[tot].w=w;}
ll Ans=0;
namespace Subtask1{
	ll f[3030][3030][2],tmp[3030][2];
	int sz[1010010];
	inline void DFS(int now,int ffa){
		f[now][0][0]=0;
		f[now][1][1]=0;
		sz[now]=1;
		for(rint x=h[now];x;x=e[x].next){
			int to=e[x].to;if(to==ffa) continue;
			DFS(to,now);
			memcpy(tmp,f[now],sizeof(tmp));
			for(rint i=0;i<=sz[now];++i) {
				for(rint j=0;j<=sz[to];++j) {
					if(i&&j)
					tmp[i+j-1][0]=max(tmp[i+j-1][0],f[now][i][1]+f[to][j][1]+e[x].w);
					if(i)
					tmp[i+j][1]=max(tmp[i+j][1],f[now][i][1]+f[to][j][0]);
					if(j)
					tmp[i+j][1]=max(tmp[i+j][1],f[now][i][0]+f[to][j][1]+e[x].w);
					tmp[i+j][0]=max(tmp[i+j][0],f[now][i][0]+f[to][j][0]);
				}
			}sz[now]+=sz[to];
			memcpy(f[now],tmp,sizeof(tmp));
		}//debug(now);
		//for(rint i=0;i<=m;++i) debug(f[now][i][0]);
	}
	multiset<int> st;
	inline void Solve(){
		memset(f,-0x3f,sizeof(f));
		DFS(1,0);
		for(rint i=1;i<=m;++i) {
			f[1][i][0]=max(f[1][i-1][0],f[1][i][0]);
			//debug(f[1][i][0]);
		}
		ll Max=0,cnt=0,Sum=0;
		cout<<Ans-Max<<" ";
		for(rint i=1;i<=m;++i) {
			int x=read();
			if(cnt)
			if((*st.rbegin())>x){
//				debug(x);
				st.insert(x);
				int y=*st.rbegin();
				Sum+=x-y;
				Max+=y-x;
				st.erase(st.find(y));
				swap(x,y);
			}
//			debug(f[1][cnt+1][0])
			if(Max<f[1][cnt+1][0]-Sum-x){
				Max=f[1][cnt+1][0]-Sum-x;
				Sum+=x;
				cnt++;
				st.insert(x);
			}
//			for(int t:st) debug(t);
//			cout<<endl;
			cout<<Ans-Max<<" ";
		}
	}
}
namespace Subtask2{
	ll f[103000][5][2],tmp[5][2];
	int sz[1010010];
	inline void DFS(int now,int ffa){
		f[now][0][0]=0;
		f[now][1][1]=0;
		sz[now]=1;
		for(rint x=h[now];x;x=e[x].next){
			int to=e[x].to;if(to==ffa) continue;
			DFS(to,now);
			memcpy(tmp,f[now],sizeof(tmp));
			for(rint i=0;i<=min(sz[now],m);++i) {
				for(rint j=0;j<=min(sz[to],m);++j) {
					if(i&&j)
					tmp[i+j-1][0]=max(tmp[i+j-1][0],f[now][i][1]+f[to][j][1]+e[x].w);
					if(i)
					tmp[i+j][1]=max(tmp[i+j][1],f[now][i][1]+f[to][j][0]);
					if(j)
					tmp[i+j][1]=max(tmp[i+j][1],f[now][i][0]+f[to][j][1]+e[x].w);
					tmp[i+j][0]=max(tmp[i+j][0],f[now][i][0]+f[to][j][0]);
				}
			}sz[now]+=sz[to];
			memcpy(f[now],tmp,sizeof(tmp));
		}//debug(now);
		//for(rint i=0;i<=m;++i) debug(f[now][i][0]);
	}
	multiset<int> st;
	inline void Solve(){
		memset(f,-0x3f,sizeof(f));
		DFS(1,0);
		for(rint i=1;i<=m;++i) {
			f[1][i][0]=max(f[1][i-1][0],f[1][i][0]);
			//debug(f[1][i][0]);
		}
		ll Max=0,cnt=0,Sum=0;
		cout<<Ans-Max<<" ";
		for(rint i=1;i<=m;++i) {
			int x=read();
			if(cnt)
			if((*st.rbegin())>x){
//				debug(x);
				st.insert(x);
				int y=*st.rbegin();
				Sum+=x-y;
				Max+=y-x;
				st.erase(st.find(y));
				swap(x,y);
			}
//			debug(f[1][cnt+1][0])
			if(Max<f[1][cnt+1][0]-Sum-x){
				Max=f[1][cnt+1][0]-Sum-x;
				Sum+=x;
				cnt++;
				st.insert(x);
			}
//			for(int t:st) debug(t);
//			cout<<endl;
			cout<<Ans-Max<<" ";
		}
	}
}
multiset<int> st;
namespace Subtask3{
	ll res[1101010];
	inline void Solve(){
		res[0]=0;
		for(rint i=1;i<=(n+1)/2;++i) {
			res[i]=res[i-1];
			if(st.size()>=2){
				int x=*st.rbegin();
				res[i]+=x;
				st.erase(st.find(x));
				x=*st.rbegin();
				res[i]+=x;
				st.erase(st.find(x));
			}
			else {
				int x=*st.rbegin();
				res[i]+=x;
				st.erase(st.find(x));
			}
		}
		for(rint i=1;i<=m;++i) {
			res[i]=max(res[i],res[i-1]);
			//debug(f[1][i][0]);
		}
		ll Max=0,cnt=0,Sum=0;
		cout<<Ans-Max<<" ";
		for(rint i=1;i<=m;++i) {
			int x=read();
			if(cnt)
			if((*st.rbegin())>x){
//				debug(x);
				st.insert(x);
				int y=*st.rbegin();
				Sum+=x-y;
				Max+=y-x;
				st.erase(st.find(y));
				swap(x,y);
			}
//			debug(f[1][cnt+1][0])
			if(Max<res[cnt+1]-Sum-x){
				Max=res[cnt+1]-Sum-x;
				Sum+=x;
				cnt++;
				st.insert(x);
			}
//			for(int t:st) debug(t);
//			cout<<endl;
			cout<<Ans-Max<<" ";
		}
	}
}
int main(){
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
	n=read(),m=read();
	for(rint i=1;i<n;++i){
		int u=read(),v=read(),w=read();
		add(u,v,w);Ans+=2*w;
		st.insert(w);
		//debug(2*w);
		add(v,u,w);
	}
//	debug(Ans);
	if(n<=3000){
		Subtask1::Solve();
		return 0;
	}
	if(m<=2){
		Subtask2::Solve();
		return 0;
	}
	Subtask3::Solve();
	return 0;
}	
