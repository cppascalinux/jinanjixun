
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ll long long
#define M 1000100
#define mmp make_pair
using namespace std;

const int MAXN = 2e7+10;
inline char nc() {
	static char buf[MAXN],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,MAXN,stdin),p1==p2)?EOF:*p1++;
}
inline int read() {
	char c=nc();
	int x=0,f=1;
	while(c<'0'||c>'9') {
		if(c=='-')f=-1;
		c=nc();
	}
	while(c>='0'&&c<='9') {
		x=x*10+c-'0';
		c=nc();
	}
	return x*f;
}
//
//int read() {
//	int nm = 0, f = 1;
//	char c = getchar();
//	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
//	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
//	return nm * f;
//}
//struct io
//{
//	char ibuf[50 << 20] , * s , obuf[20 << 20] , * t;
//	int a[24];
//	io() : t( obuf )
//	{
//	//	freopen( "test.in" , "r" , stdin );
//	//	freopen( "test.out" , "w" , stdout );
//		fread( s = ibuf , 1 ,  20 << 20  , stdin );
//	}
//	~io()
//	{
//		fwrite( obuf , 1 , t - obuf , stdout );
//	}
//	inline int read()
//	{
//		register int u = 0;
//		while( * s < 48 ) s++;
//		while( * s > 32 )
//			u = u * 10 + * s++ - 48;
//		return u;
//	}
//	template < class T >
//	inline void print( register T u )
//	{
//		static int * q = a;
//		if( !u ) * t++ = 48;
//		else
//		{
//			while( u ) * q++ = u % 10 + 48 , u /= 10;
//			while( q != a )
//				* t++ = * --q;
//		}
//		* t++ = '\n';
//	}
//} ip;
int a[M], v[M], ans[M], belong[M],  biao, n, m;
struct Note {
	int l, r, id;
	bool operator < (const Note &b) const {
		if(belong[l] == belong[b.l]) {
			if(belong[l] & 1) return r > b.r;
			else return r < b.r;
		}
		return l < b.l;
	}
} note[M];
char as[M][11];

int getl(int be) {
	int x = 0;
	while(be >= 0 && x <= 10) {
		if(v[be]) x++, be--;
		else return x;
	}
	return x;
}

int getr(int be) {
	int x = 0;
	while(be < M && x <= 10) {
		if(v[be]) x++, be++;
		else return x;
	}
	return x;
}

void add(int x) {
	x = a[x];
	v[x]++;
	if(v[x] == 1) {
		int lenl = getl(x - 1), lenr = getr(x + 1);
		ans[lenl]--;
		ans[lenr]--;
		ans[lenl + lenr + 1]++;
	}
}

void del(int x) {
	x = a[x];
	v[x]--;
	if(v[x] == 0) {
		int lenl = getl(x - 1), lenr = getr(x + 1);
		ans[lenl]++;
		ans[lenr]++;
		ans[lenl + lenr + 1]--;
	}
}

void getans(int x) {
	for(int i = 1; i <= 10; i++) as[x][i] = '0' + ans[i] % 10;
}
int main() {
//	freopen("sample3.in", "r", stdin); freopen("sample.out", "w", stdout);
//	ip.io();
	freopen("shinku.in", "r", stdin); freopen("shinku.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	if(n <= 300000) {
		biao = sqrt(n);
		for(int i = 1; i <= n; i++) belong[i] = i / biao;
		for(int i = 1; i <= m; i++) {
			note[i].id = i;
			note[i].l = read(), note[i].r = read();
		}
		sort(note + 1, note + m + 1);
		int L = 1, R = 0;
		for(int i = 1; i <= m; i++) {
			while(R < note[i].r) add(++R);
			while(L > note[i].l) add(--L);
			while(L < note[i].l) del(L++);
			while(R > note[i].r) del(R--);
			getans(note[i].id);
		}
		for(int i = 1; i <= m; i++) {
			for(int j = 1; j <= 10; j++) {
				putchar(as[i][j]);
			}
			putchar('\n');
		}
	}
	else
	{
		
		
		
	}
	return 0;
}

/*
5 5
1 2 4 5 6
1 5
1 2
3 4
3 5
4 5

*/
