#include<cstdio>
#include<iostream>
#include<cctype>
#include<cmath>
#include<queue>
#include<vector>
#include<cstring>
#define LL long long
#define pii pair<int,int>
#define mk make_pair
using namespace std; 
const int N = 3e4 + 3;
const int mod = 1e9 + 7;
int p[N];
int n;
inline void up(int &x,int y){
	x += y;
	if(x >= mod) x -= mod;	
	if(x < 0) x += mod;
}
struct Tree{
	vector <pii> G[N];
	int s[N],fa[N];
	int deep[N],st[21][N];
	int sum[N];
	int cnt;
	inline void dfs(int x,int f,int dep){
	//	cerr << x <<" "<<  cnt << endl;
		s[++cnt] = x;//l[x] = cnt;
		st[0][cnt] = x;deep[x] = dep;
		for(int i = 0;i < (int)G[x].size();++i){
			//cout << i << endl;
			int y = G[x][i].first;
			if(y == f) continue;
			up(sum[y],sum[x] + G[x][i].second);	
			dfs(y,x,dep + 1);
		}
	}
	inline void pre(){
		for(int j=1;(1<<j)<=n;j++)
			for(int i=1;i+(1<<j)-1<=n;i++){
				if(deep[st[j - 1][i]] < deep[st[j - 1][i + (1 << (j - 1))]]) st[j][i] = st[j - 1][i];
				else st[j][i] = st[j - 1][i + (1 << (j - 1))];	
			}
	}
	inline int query(int l,int r){
		int k = p[r - l + 1];
		if(deep[st[k][l]] < deep[st[k][r - (1 << k) + 1]]) return st[k][l];
		return st[k][r - (1 << k) + 1];	
	}
};
Tree T1,T2;
inline char nc(){
    #define SIZE 100000
    static char buf[SIZE],*p1 = buf+SIZE,*pend = buf+SIZE;
    if(p1 == pend){
        p1 = buf;pend = buf+fread(buf,1,SIZE,stdin);
        if(p1 == pend) return -1;
    }
    return *p1++;
    #undef SIZE
}
inline int read(){
    int x = 0;int flag = 0;
    char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
    return x;
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n = read();
	for(int i = 1;i < n;++i){
		int x = read(),y = read(),z = read();
		T1.G[x].push_back(mk(y,z));
		T1.G[y].push_back(mk(x,z));
	}
	for(int i = 1;i < n;++i){
		int x = read(),y = read(),z = read();
		T2.G[x].push_back(mk(y,z));
		T2.G[y].push_back(mk(x,z));
	}
	T1.dfs(1,0,1);//cout << 1 << endl;
	T1.pre();
	p[1] = 0;
	int last = 1;
	for(int i = 2;i <= n;++i){
		if(i == (1 << last)) p[i] = last++;
		else p[i] = p[i - 1];
	}
	T2.dfs(1,0,1);T2.pre();
	int ans = 0;
//	return 0;
	for(int i = 1;i < n;++i){
		for(int j = i + 1;j <= n;++j){
			int l1 = T1.query(i,j),l2 = T2.query(i,j);
			int s = 0,ss = 0;
			up(s,T1.sum[i] + T1.sum[j]);
			up(s,mod - 2 * T1.sum[l1]);
			up(ss,T2.sum[i] + T2.sum[j]);
			up(ss,mod -2 * T2.sum[l2]);
			int sum = 2ll * s * ss % mod; 
			up(ans,sum);
		}
	}	
	printf("%d\n",ans);
	return 0;	
}
