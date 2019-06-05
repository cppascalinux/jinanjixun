#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<vector>
#include<cmath>
#include<cstring>
#define LL long long
using namespace std;
const int N = 1e5 + 3;
const int INF = 999999999;
const int mod = 20004 + 3;
int a[N];
int c[N],belong[N];
int n,m;
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
int bl;
struct block{
	struct edge{
		int val;
		int nxt;	
	}e[345];
	int head[20011];
	int num;
	int fir[345];
	int last[345];
	int dis[345][345];
	inline void add(int x){
		int t = x % mod;
		e[++num].val = x;
		e[num].nxt = head[t];
		head[t] = num; 	
	}
	inline int query(int x){
		int ans = 0,t = x % mod;
		for(int i = head[t];i;i = e[i].nxt)
			if(e[i].val == x) return i;	
		return ans;
	}
	vector <int> v;	
}b[345];
inline int work(int x,int y){
	int lastx = -1,lasty = -1,res = INF;
	for(int i = 0;i <= n / bl;++i){
		int xx = b[i].query(x),yy = b[i].query(y);
		int ll = lastx,rr = lasty;
		if(xx != 0) lastx = b[i].last[xx];
		if(yy != 0) lasty = b[i].last[yy];
		if(rr != -1 && xx != 0) res = min(res,b[i].fir[xx] - rr);
		if(ll != -1 && yy != 0) res = min(res,b[i].fir[yy] - ll);
	}
	return res;
}
inline void pre(){
	for(int i = 0;i <= n / bl;++i){
		for(int j = 0;j < (int)b[i].v.size();++j){
			for(int k = j;k < (int)b[i].v.size();++k){
				int xx = b[i].query(b[i].v[j]),yy = b[i].query(b[i].v[k]);
				b[i].dis[xx][yy] = min(b[i].dis[xx][yy],k - j);
				b[i].dis[yy][xx] = b[i].dis[xx][yy];
			}
		}
	}
}
int main(){
//	printf("%d\n",sizeof(b)/1024/1024);
	freopen("busy.in","r",stdin);
	freopen("busy.out","w",stdout);
	n = read(),m = read();int lastans = 0;
	for(int i = 1;i <= n;++i) a[i] = read();
	if(n <= 2000){
		while(m--){
			int opt = read();
			if(opt == 1){
				int x = read() ^ lastans,y = read() ^ lastans;
				for(int i = 1;i <= n;++i) if(a[i] == x) a[i] = y;
			}
			else{
				int lastx = -1,lasty = -1;int ans = INF;
				int x = read() ^ lastans;int y = read() ^ lastans;	
				for(int i = 1;i <= n;++i){
					if(a[i] == x){
						if(lasty != -1) ans = min(ans,i - lasty);
						lastx = i;
					}
					if(a[i] == y){
						if(lastx != -1) ans = min(ans,i - lastx);
						lasty = i;
					}
				}
				if(ans != INF) {lastans = ans;printf("%d\n",ans);}
				else {lastans = 0;printf("Chtholly\n");}
			}
		}
	}
	else{
		bl = sqrt(n) * 2.3 ;
		for(int i = 1;i <= n;++i){
			belong[i] = i / bl;
			b[belong[i]].v.push_back(a[i]);
			int t = b[belong[i]].query(a[i]);
			if(t == 0) b[belong[i]].add(a[i]);
			if(t == 0) b[belong[i]].fir[b[belong[i]].query(a[i])] = i;
			b[belong[i]].last[b[belong[i]].query(a[i])] = i;
		//	for(int j = 0;i < 345;++i) b[i].s[]
		}
		for(int i = 0;i <= n / bl;++i) memset(b[i].dis,0x3f,sizeof(b[i].dis));
		pre();
	
		while(m--){
			int opt = read(),x = read() ^ lastans,y = read() ^ lastans;
			int now = 0x3f3f3f3f;
			for(int i = 0;i <= n / bl;++i) {
				int xx = b[i].query(x),yy = b[i].query(y);
				if(xx == 0 || yy == 0) continue;
				now = min(now,b[i].dis[xx][yy]);
			}
			int noww;
			int ans = min(noww = work(x,y),now);
		//	printf("%d %d\n",noww,now);
			if(ans >= 9999999){lastans = 0;printf("Chtholly\n");}
			else lastans = ans,printf("%d\n",ans);
		}
	}
	return 0;	
}
