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
	freopen("flipflap.in","r",stdin);
	freopen("flipflap.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m;
#define ls q << 1
#define rs q << 1 | 1
#define ln ls,l,mid
#define rn rs,mid + 1,r
#define md int mid = l + r >> 1
int bel[400010],mx;
int len[40],sl[40],ku[40],bl[40][100010],ss[40][110],kuai[40][110][1010];
li jia[40][110],ys[40][100010];
int st[40][110],ed[40][110],ql[400010][40],qr[400010][40];
int tong[1010],tp1[1010],tp2[1010];

inline void build(int q,int l,int r,int dpt){
	int tp = dpt * 2 - (r - l & 1);
	mx = max(mx,tp);len[tp] = r - l + 1;
	bel[q] = tp;++sl[tp];
	ql[q][tp] = qr[q][tp] = sl[tp];
	if(l == r) return;
	md;
	build(ln,dpt + 1);build(rn,dpt + 1);
	for(int i = tp + 1;i <= mx;++i){
		ql[q][i] = ql[ls][i] ? ql[ls][i] : ql[rs][i];
		qr[q][i] = qr[rs][i] ? qr[rs][i] : qr[ls][i];
	} 
}
inline void xg(int q,int l,int r,li x){
	//if(q == 3) cerr<<q<<" "<<l<<" "<<r<<"^^^^^"<<x<<endl;
	if(l <= 0 || r > sl[q] || l > r || !x) return;
	int i,j,k,nw,s1,s2;
	if(bl[q][l] == bl[q][r]){
		nw = bl[q][l];
		for(i = l;i <= r;++i) ys[q][i] += x;
		s1 = s2 = 0;
		for(i = 1;i <= ss[q][nw];++i){
			if(kuai[q][nw][i] >= l && kuai[q][nw][i] <= r) tp1[++s1] = kuai[q][nw][i];
			else tp2[++s2] = kuai[q][nw][i];
		} 
		
		i = j = k = 1;
		while(i <= s1 && j <= s2){
			if(ys[q][tp1[i]] < ys[q][tp2[j]]) kuai[q][nw][k++] = tp1[i++];
			else kuai[q][nw][k++] = tp2[j++];
		}
		while(i <= s1) kuai[q][nw][k++] = tp1[i++];
		while(j <= s2) kuai[q][nw][k++] = tp2[j++];
		return;
	}
	
	nw = bl[q][l];
	for(i = l;i <= ed[q][nw];++i) ys[q][i] += x;
	s1 = s2 = 0;
	for(i = 1;i <= ss[q][nw];++i){
		if(kuai[q][nw][i] >= l && kuai[q][nw][i] <= ed[q][nw]) tp1[++s1] = kuai[q][nw][i];
		else tp2[++s2] = kuai[q][nw][i];
	} 
	i = j = k = 1;
	while(i <= s1 && j <= s2){
		if(ys[q][tp1[i]] < ys[q][tp2[j]]) kuai[q][nw][k++] = tp1[i++];
		else kuai[q][nw][k++] = tp2[j++];
	}
	while(i <= s1) kuai[q][nw][k++] = tp1[i++];
	while(j <= s2) kuai[q][nw][k++] = tp2[j++];
		
	for(i = bl[q][l] + 1;i < bl[q][r];++i) jia[q][i] += x;
	
	nw = bl[q][r];
	for(i = st[q][nw];i <= r;++i) ys[q][i] += x;
	s1 = s2 = 0;
	for(i = 1;i <= ss[q][nw];++i){
		if(kuai[q][nw][i] >= st[q][nw] && kuai[q][nw][i] <= r) tp1[++s1] = kuai[q][nw][i];
		else tp2[++s2] = kuai[q][nw][i];
	} 
	i = j = k = 1;
	while(i <= s1 && j <= s2){
		if(ys[q][tp1[i]] < ys[q][tp2[j]]) kuai[q][nw][k++] = tp1[i++];
		else kuai[q][nw][k++] = tp2[j++];
	}
	while(i <= s1) kuai[q][nw][k++] = tp1[i++];
	while(j <= s2) kuai[q][nw][k++] = tp2[j++];
	
}
inline int cx(int q,int l,int r,li x){
	//cerr<<q<<" "<<l<<" "<<r<<"%%%%%"<<endl;
	if(l <= 0 || r > sl[q] || l > r) return 0;
	int as = 0,i,j;
	li bj;
	//for(i = l;i <= r;++i) if(ys[q][i] + jia[q][bl[q][i]] <= x) ++as;
	//return as;
	if(bl[q][l] == bl[q][r]){
		bj = jia[q][bl[q][l]];
		for(i = l;i <= r;++i) if(ys[q][i] + bj <= x) ++as;
		return as;
	}
	
	bj = jia[q][bl[q][l]];
	for(i = l;bl[q][i] == bl[q][l];++i) if(ys[q][i] + bj <= x) ++as;
	
	for(i = bl[q][l] + 1;i < bl[q][r];++i){
		bj = jia[q][i];
		int aa = 0;
		//cerr<<st[q][i]<<" "<<ed[q][i]<<"*"<<x<<" "<<ss[q][i]<<endl;
		//for(int j = st[q][i];j <= ed[q][i];++j) cerr<<ys[q][j] + bj<<" ";cerr<<endl;
		//for(int j = 1;j <= ss[q][i];++j) cerr<<kuai[q][i][j]<<" ";cerr<<endl;
		//for(int j = 1;j <= ss[q][i];++j) cerr<<ys[q][kuai[q][i][j]] + bj<<" ";cerr<<endl;
		//for(int j = st[q][i];j <= ed[q][i];++j) if(ys[q][j] + bj <= x) ++as;
		//continue; 
		int al = 1,ar = ss[q][i],mid,an = 0;
		while(al <= ar){
			mid = al + ar >> 1;
			//cerr<<al<<" "<<ar<<" "<<mid<<" "<<ys[q][kuai[q][i][mid]] + bj<<endl;
			if(ys[q][kuai[q][i][mid]] + bj <= x) an = mid,al = mid + 1;
			else ar = mid - 1;
		}
		//assert(an == aa);
		//cerr<<an<<" "<<aa<<endl;
		as += an;
	}
	
	bj = jia[q][bl[q][r]];
	for(i = r;bl[q][i] == bl[q][r];--i) if(ys[q][i] + bj <= x) ++as;
	//cerr<<q<<":"<<l<<" "<<r<<" "<<r - l + 1<<" "<<as<<endl;
	return as;
}
inline void xg(int q,int l,int r,int al,int ar,li x){
	if(l >= al && r <= ar){
		for(int i = bel[q];i <= mx;++i) xg(i,ql[q][i],qr[q][i],x * len[i]);
		return;
	}
	xg(bel[q],ql[q][bel[q]],qr[q][bel[q]],x * (min(r,ar) - max(l,al) + 1));
	md;
	if(mid >= al) xg(ln,al,ar,x);
	if(mid < ar) xg(rn,al,ar,x);
}
inline int cx(int q,int l,int r,int al,int ar,int x){
	if(l >= al && r <= ar){
		int as = 0;
		for(int i = bel[q];i <= mx;++i) as += cx(i,ql[q][i],qr[q][i],x);
		return as;
	}
	md;
	int as = 0;
	if(mid >= al) as = cx(ln,al,ar,x);
	if(mid < ar) as += cx(rn,al,ar,x);
	return as;
	
}
int main(){
	srand(time(0));rd();
	file();
	int i,j,k,op,l,r,x,u,v;
	n = read();m = read();
	build(1,1,n,1);
	for(i = 1;i <= mx;++i) if(sl[i]){
		ku[i] = sqrtl(sl[i] * 10);
		u = 0;v = ku[i];
		for(j = 1;j <= sl[i];++j){
			if(v == ku[i]) ss[i][u] = v,ed[i][u] = j - 1,++u,v = 0,st[i][u] = j;
			kuai[i][u][++v] = j;
			bl[i][j] = u;
		}
		ss[i][u] = v;ed[i][u] = sl[i];
		//for(j = 1;j <= ss[i][u];++j) cerr<<kuai[i][u][j]<<" ";cerr<<endl;
	}
	//for(j = 1;j <= mx;++j){
			//cerr<<j<<endl;
			//print(i);pc(' ');print(j);pc(':');pc('\n');
			//for(k = 1;k <= sl[j];++k) print(ys[j][k] + jia[j][bl[j][k]]),pc(' ');pc('\n');
			//for(k = 1;k <= bl[j][sl[j]];++k){
				//for(l = 1;l <= ss[j][k];++l) cerr<<kuai[j][k][l]<<" ";cerr<<endl;
				//for(l = 1;l < ss[j][k];++l) assert(ys[j][kuai[j][k][l]] && ys[j][kuai[j][k][l]] <= ys[j][kuai[j][k][l + 1]]);
			//}
		//}
	//for(i = 1;i <= mx;++i) cerr<<sl[i]<<" "<<len[i]<<"()"<<endl;
	for(i = 1;i <= m;++i){
		//if(i % 1000 == 0 || i <= 100) cerr<<i<<endl;
		op = read();l = read();r = read();x = read();
		if(op == 1) xg(1,1,n,l,r,x);
		else print(cx(1,1,n,l,r,x)),pc('\n');
	}
	return 0;
}
