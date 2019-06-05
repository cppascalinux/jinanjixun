#include<bits/stdc++.h>
using namespace std;
#define li long long
//char buf[100010],*buff = buf + 100000;
//#define gc (((buff == buf + 100000) ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
#define gc getchar()
//char bfu[50000010],*bfuu = bfu;
//#define pc(x) (*(bfuu++) = (x))
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
	freopen("save.in","r",stdin);
	freopen("save.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m,a[100010],b[100010],ton[16500];
struct qy{
	int op,l,r,x;
}d[100010];
int t[400010],c[400010];
#define ls q << 1
#define rs q << 1 | 1
#define ln ls,l,mid
#define rn rs,mid + 1,r
#define md int mid = l + r >> 1
inline void init(int q,int l,int r){
	if(l == r){
		t[q] = a[l];return;
	}
	md;
	init(ln);init(rn);t[q] = t[ls] ^ t[rs];
}
inline void ud(int q,int l,int r,int x){
	c[q] ^= x;
	if(r - l + 1 & 1) t[q] ^= x;
}
inline void ps(int q,int l,int r){
	md;
	ud(ln,c[q]);ud(rn,c[q]);c[q] = 0; 
}
inline void xg(int q,int l,int r,int al,int ar,int x){
	if(l >= al && r <= ar){
		ud(q,l,r,x);return;
	}
	ps(q,l,r);md;
	if(mid >= al) xg(ln,al,ar,x);
	if(mid < ar) xg(rn,al,ar,x);
	t[q] = t[ls] ^ t[rs];
}
inline int cx(int q,int l,int r,int al,int ar){
	if(l >= al && r <= ar) return t[q];
	ps(q,l,r);md;
	int as = 0;
	if(mid >= al) as = cx(ln,al,ar);
	if(mid < ar) as ^= cx(rn,al,ar);
	return as;
}
int main(){
	srand(time(0));rd();
	file();
	int i,j,op,l,r,x;
	n = read();m = read();for(i = 1;i <= n;++i) a[i] = read();
	if(1 && (n <= 10000 && m <= 10000)){
		for(i = 1;i <= m;++i){
			op = read();
			if(op == 1){
				l = read();r = read();x = read();
				for(j = l;j <= r;++j) a[j] ^= x;
			}
			else if(op == 2){
				l = read();r = read();
				if(r - l <= 2000) sort(a + l,a + r + 1);
				else{
					for(j = l;j <= r;++j) ++ton[a[j] & 16383];
					for(j = 0;j <= 16383;++j) ton[j] += ton[j - 1];
					for(j = l;j <= r;++j) b[l - 1 + ton[a[j] & 16383]--] = a[j];
					memset(ton,0,sizeof(ton));
					for(j = l;j <= r;++j) ++ton[b[j] >> 14];
					for(j = 0;j <= 16383;++j) ton[j] += ton[j - 1];
					for(j = r;j >= l;--j) a[l - 1 + ton[b[j] >> 14]--] = b[j];
					memset(ton,0,sizeof(ton));
				}
			}
			else{
				l = read();r = read();
				int as = 0;
				for(j = l;j <= r;++j) as ^= a[j];
				print(as);pc('\n');
			}
		}
		return 0;
	}
	bool fg = 1;
	for(i = 1;i <= m;++i){
		d[i].op = read();
		if(d[i].op == 2) fg = 0;
		if(d[i].op == 1){
			d[i].l = read();d[i].r = read();d[i].x = read();
		}
		else{
			d[i].l = read();d[i].r = read();
		}
	}
	if(fg){
		init(1,1,n);
		for(i = 1;i <= m;++i){
			if(d[i].op == 1) xg(1,1,n,d[i].l,d[i].r,d[i].x);
			else if(d[i].op == 3) print(cx(1,1,n,d[i].l,d[i].r)),pc('\n');
		}
		return 0;
	}
	//fwrite(bfu,1,bfuu - bfu,stdout);
	return 0;
}

