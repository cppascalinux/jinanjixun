#include<cstdio>
#include<cstring>
#include<iostream>
#include<cctype>
#include<algorithm>
#include<queue>
#include<set>
#include<vector>
#include<cmath>
#define LL long long
#define pii pair<int,int>
#define mk make_pair
using namespace std;
const int N = 2e3 + 3;
int fa[N];
int n,m;
int size[N]; 
int tot = 0;
int s[N];
vector <int> G[N];
inline int read(){
	int v = 0,c = 1;char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') c = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		v = v * 10 + ch - 48;
		ch = getchar();	
	}
	return v * c;
}

int rt[N];
bool book[N];
inline int bfs(int x){
	int res = 1;
	queue <int> q;
	q.push(x);book[x] = 1;
	while(!q.empty()){
		int k = q.front();q.pop();
		for(int i = 0;i < G[k].size();++i){
			int y = G[k][i];
			if(book[y]) continue;
			q.push(y);
			book[y] = 1;
			res++;
		}
	}
	return res;
}
inline int getans(){
	memset(book,0,sizeof(book));
	int ans = 0;
	for(int i = 0;i <= n;++i){
		if(!book[i]) ans = max(ans,bfs(i));	
	}
	return ans;
}
int main(){
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	n = read(),m = read();
	n = (1 << n) - 1;
	while(m--){
		int opt = read(),x= read();
		if(opt == 1){
			for(int i = 0;i <= n;++i){
				int j = x ^ i;
				G[i].push_back(j);
			}
		}
		else{
			for(int i = 0;i <= n;++i){
				int j = x ^ i;tot = 0;
				int k = G[i].size();
			//	cout << k << endl;
				for(int h = k - 1;h >= 0;--h){
					if(G[i][h] != j) s[++tot] = G[i][h],G[i].pop_back();
					else break;	
				}
			//	cout << k<< endl;
				G[i].pop_back();
				for(int h = 1;h <= tot;++h) G[i].push_back(s[h]);
			}
		}
//	cout << "GG" << endl;
		printf("%d\n",getans());
	}
	return 0;	
}
