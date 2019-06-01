#include<bits/stdc++.h>
using namespace std;
#define li long long
#define gc getchar()
#define pc putchar
inline li read(){
	li x = 0,y = 0,c = gc;
	while(!isdigit(c)) y = c,c = gc;
	while(isdigit(c)) x = x * 10 + c - '0',c = gc;
	return y == '-' ? -x : x;
}
inline void print(li x){
	if(x < 0) pc('-'),x = -x;
	if(x >= 10) print(x / 10);
	pc(x % 10 + '0');
}
inline void file(){
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m,mx,as[100010];
map<int,int> mp;
struct cx{
	int l,r,x;
}a[100010];
int cnt;
vector<int> t[400010];
#define ls q << 1
#define rs q << 1 | 1
#define ln ls,l,mid
#define rn rs,mid + 1,r
#define md int mid = l + r >> 1
struct xx{
	int a[30];
	inline void ins(int x){
		for(int i = m - 1;i >= 0;--i) if(x & (1 << i)){
			if(a[i]) x ^= a[i];
			else{
				a[i] = x;
				for(int j = i - 1;j >= 0;--j) if(a[j] && (a[i] & (1 << j))) a[i] ^= a[j];
				for(int j = i + 1;j < m;++j) if(a[j] & (1 << i)) a[j] ^= a[i];
				return;
			}
		}
	}
	inline int cx(){
		int as = 0;
		for(int i = m - 1;i >= 0;--i) as += (a[i] != 0);
		return 1 << as;
	}
}b[20];
inline void xg(int q,int l,int r,int x){
	if(l >= a[x].l && r <= a[x].r){
		//cerr<<q<<" "<<l<<" "<<r<<"**"<<a[x].x<<endl;
		t[q].push_back(a[x].x);
		return;
	}
	md;
	if(mid >= a[x].l) xg(ln,x);
	if(mid < a[x].r) xg(rn,x);
}
inline void wk(int dpt,int q,int l,int r){
	for(int i = 0;i < t[q].size();++i){
		b[dpt].ins(t[q][i]);
	} 
	if(l == r){
		as[l] = b[dpt].cx();
		return;
	}
	md;
	b[dpt + 1] = b[dpt];wk(dpt + 1,ln);
	b[dpt + 1] = b[dpt];wk(dpt + 1,rn); 
}
int main(){
	srand(time(0));rd();
	file();
	int i,j,k,l,op,x;
	m = read();n = read();mx = 1 << m;
	for(i = 1;i <= n;++i){
		op = read();x = read();
		if(op == 1) mp[x] = i;
		else{
			a[++cnt].r = i - 1;a[cnt].x = x;a[cnt].l = mp[x];mp[x] = 0;
			xg(1,1,n,cnt);
		}
	} 
	for(map<int,int>::iterator it = mp.begin();it != mp.end();++it) if(it -> second){
		//cerr<<"***"<<(it -> first)<<" "<<(it -> second)<<endl;
		a[++cnt].r = n;a[cnt].x = it -> first;a[cnt].l = it -> second;
		xg(1,1,n,cnt);
	}
	wk(0,1,1,n);
	for(i = 1;i <= n;++i) print(as[i]),pc('\n');
	return 0;
}
