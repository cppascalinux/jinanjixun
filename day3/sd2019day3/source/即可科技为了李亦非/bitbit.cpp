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
int mp[550][550],n,m,dx[]={1,0,0,-1},dy[]={0,1,-1,0};
queue<pa> q;
int fa[1001010],Idx[550][550],cnt,vis[510100];
int fl=0;
inline int find(int x){if(x==fa[x]) return x;return fa[x]=find(fa[x]);}
inline bool check1(){
	for(rint i=1;i<=n;++i){
		for(rint j=1;j<=m;++j) {
			if(mp[i][j]){
				if(!vis[find(Idx[i][j])]){
					vis[find(Idx[i][j])]=1;
					fl++;
				}
			}
		}
	}
	memset(vis,0,sizeof(vis));
	if(!fl){
		cout<<0;
		exit(0);
	}
	return fl==1;
}
int used[1010100];
vector<int> vec;
int dsgsjk[550][550];
int ttt=0;
inline bool BFS(int S1,int S2){
	//cerr<<"----------------\n";
	q.push(mk(S1,S2));dsgsjk[S1][S2]=1;
	vec.clear();
//	ttt=0;
	while(!q.empty()){
		pa tmp=q.front();q.pop();
		
//		cerr<<tmp.fir<<" "<<tmp.sec<<"\n";
		++ttt;
		for(rint k=0;k<4;++k) {
			int nwx=dx[k]+tmp.fir,nwy=dy[k]+tmp.sec;
			if(nwx<1||nwy<1||nwx>n||nwy>m) continue;
			if(mp[nwx][nwy]) {vec.pb(find(Idx[nwx][nwy]));continue;}
			if(dsgsjk[nwx][nwy]) continue;
			q.push(mk(nwx,nwy));dsgsjk[nwx][nwy]=1;
		}
	}
//	cout<<ttt<<"\n";
//	debug(ttt);
	sort(vec.begin(),vec.end());
	int m=unique(vec.begin(),vec.end())-vec.begin();
//	debug(m);
	return m==fl;
}
inline bool check2(){
//	debug(fl);
	for(rint i=1;i<=n;++i) {
		for(rint j=1;j<=m;++j) {
			if(!mp[i][j])
			if(!used[find(Idx[i][j])]){
			//	debug(find(Idx[i][j]));
//				debug(i);debug(j);
				if(BFS(i,j)) {
					cout<<2<<"\n";
					cout<<"+\n";
					for(rint p=1;p<=n;++p,cout<<'\n') {
						for(rint q=1;q<=m;++q) {
							if(find(Idx[p][q])==find(Idx[i][j])){
								cout<<1<<" ";continue;
							}
							else if(mp[p][q]) {cout<<1<<" ";continue;}
							else cout<<0<<" ";
						}
					}
					cout<<"-\n";
					for(rint p=1;p<=n;++p,cout<<'\n') {
						for(rint q=1;q<=m;++q) {
							if(find(Idx[p][q])==find(Idx[i][j])){
								cout<<1<<" ";continue;
							}
							else cout<<0<<" ";
						}
					}
					exit(0);
				}
				used[find(Idx[i][j])]=1;
			}
		}
	}
//	debug(ttt);
	return 0;
}
int Ans[550][550];int res[550][550];
inline void Print(int d){
	for(rint i=1;i<=n;++i,cout<<"\n")
	for(rint j=1;j<=m;++j) 
	cout<<Ans[i][j]<<" ",res[i][j]+=d*Ans[i][j];
}
char s[10101];
inline void check(){
//	for(rint i=1;i<=n;++i){
//			for(rint j=1;j<=m;++j) if(res[i][j]!=mp[i][j]) {cout<<"WA";return ;}
//		}
//	cout<<"AC";
}
int main(){
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	n=read(),m=read();
	for(rint i=1;i<=n;++i){scanf("%s",s+1); for(rint j=1;j<=m;++j) mp[i][j]=s[j]-'0';}
	for(rint i=1;i<=n;++i) {
		for(rint j=1;j<=m;++j) Idx[i][j]=++cnt;
	}
	for(rint i=1;i<=n*m;++i) fa[i]=i;
	for(rint i=1;i<=n;++i) {
		for(rint j=1;j<=m;++j) {
			for(rint k=0;k<4;++k) {
				int nwx=dx[k]+i,nwy=dy[k]+j;
				if(nwx<1||nwy<1||nwx>n||nwy>m) continue;
				if(mp[i][j]!=mp[nwx][nwy]) continue;
				int o=Idx[nwx][nwy],oo=find(Idx[i][j]);
				o=find(o);
				if(o!=oo) {
					fa[o]=oo;
				}
			}
		}
	}
	if(check1()){
		cout<<1<<"\n";
		for(rint i=1;i<=n;++i,cout<<"\n") 
		for(rint j=1;j<=m;++j) 
		cout<<mp[i][j]<<" ";
		return 0;
	}
	if(check2()){
		return 0;
	}
	else {
		if(n==1||m==1){
			cout<<fl<<"\n";
			memset(vis,0,sizeof(vis));
			for(rint i=1;i<=fl;++i) {
				cout<<"+\n";
				int fll=-1;
				for(rint j=1;j<=n;++j) {
					for(rint k=1;k<=m;++k) {
						Ans[j][k]=0;
						if(mp[j][k]){
							if((!vis[find(Idx[j][k])])&&(fll==-1)) fll=find(Idx[j][k]),vis[find(Idx[j][k])]=1;
							if(fll==find(Idx[j][k])) Ans[j][k]=1;
						}
					}
				}
				Print(1);
			}
			check();
			return 0;
		}
		cout<<3<<"\n";
		if(m==2) {
				for(rint i=1;i<=n;++i) {
				Ans[i][1]=1;
				if(i&1){
					for(rint j=2;j<=m-1;++j) {
						Ans[i][j]=1;
					}
					if(mp[i][m]) Ans[i][m]=1;
				}
				else {
					for(rint j=2;j<=m;++j) {
						if(mp[i][j]) Ans[i][j]=1;
					}
				}
			}cout<<"+\n";
			Print(1);
			memset(Ans,0,sizeof(Ans));
			for(rint i=1;i<=n;++i) {
				Ans[i][m]=1;
				if(!(i&1)){
					for(rint j=2;j<=m-1;++j) {
						Ans[i][j]=1;
					}
					if(mp[i][1]) Ans[i][1]=1;
				}
				else {
					for(rint j=1;j<=m-1;++j) {
						if(mp[i][j]) Ans[i][j]=1;
					}
				}
			}
			cout<<"+\n";
			Print(1);
			memset(Ans,0,sizeof(Ans));
			for(rint i=1;i<=n;++i) {
				for(rint j=1;j<=m;++j) Ans[i][j]=1;
			}
			cout<<"-\n";
			Print(-1);
			check();
			return 0;
		}
		memset(Ans,0,sizeof(Ans));
		for(rint i=1;i<=n;++i) {
			Ans[i][1]=1;
			if(i&1){
				for(rint j=2;j<=m-1;++j) {
					Ans[i][j]=1;
				}
			}
			else {
				for(rint j=2;j<=m-1;++j) {
					if(mp[i][j]) Ans[i][j]=1;
				}
			}
		}cout<<"+\n";
		Print(1);
		memset(Ans,0,sizeof(Ans));
		for(rint i=1;i<=n;++i) {
			Ans[i][m]=1;
			if(!(i&1)){
				for(rint j=2;j<=m-1;++j) {
					Ans[i][j]=1;
				}
			}
			else {
				for(rint j=2;j<=m-1;++j) {
					if(mp[i][j]) Ans[i][j]=1;
				}
			}
		}
		cout<<"+\n";
		Print(1);
		memset(Ans,0,sizeof(Ans));
		for(rint i=1;i<=n;++i) {
			for(rint j=1;j<=m;++j) Ans[i][j]=1;
		}
		for(rint i=1;i<=n;++i){
			if(mp[i][1]) Ans[i][1]=0;
			if(mp[i][m]) Ans[i][m]=0;
		}
		cout<<"-\n";
		Print(-1);
		check();
	}
	return 0;
}
