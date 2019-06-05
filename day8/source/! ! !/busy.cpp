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
	freopen("busy.in","r",stdin);
	freopen("busy.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m,a[100010],lstas,sl[100010],mx;
int cnt,dd[320][100010],bh[100010],da[100010];
int fir[100010],nxt[100010],pre[100010];
struct qy{
	int op,x,y;
}b[100010];
int main(){
	srand(time(0));rd();
	file();
	int i,j,op,x,y;
	n = read();m = read();
	for(i = 1;i <= n;++i) a[i] = read(),++sl[a[i]],mx = max(mx,a[i]);
	for(i = n;i;--i){
		if(fir[a[i]]) pre[fir[a[i]]] = i;
		nxt[i] = fir[a[i]];
		fir[a[i]] = i;
	}
	if(0 || (n <= 1000 && m <= 1000)){
		for(i = 1;i <= m;++i){
			//if(i % 1000 == 0) cerr<<i<<endl;
			op = read();x = read() ^ lstas;y = read() ^ lstas;
			if(op == 1){
				for(j = 1;j <= n;++j) if(a[j] == x) a[j] = y;
			}
			else{
				if(x == y){
					bool fg = 0;
					for(j = 1;j <= n;++j) if(a[j] == x){
						fg = 1;break;
					} 
					if(fg == 0) puts("Chtholly");
					else pc('0'),pc('\n');
					lstas = 0;
					continue;
				}
				int q1 = 0,q2 = 0,as = n + 1;
				for(j = 1;j <= n;++j){
					if(a[j] == x){
						if(q2) as = min(as,j - q2);
						q1 = j;
					}
					else if(a[j] == y){
						if(q1) as = min(as,j - q1);
						q2 = j;
					}
				}
				if(as == n + 1) lstas = 0,puts("Chtholly");
				else lstas = as,print(as),pc('\n');
			}
		}
		return 0;
	}
	bool fg = 1;
	for(i = 1;i <= m;++i){
		b[i].op = read(),b[i].x = read(),b[i].y = read();
		if(b[i].op == 1) fg = 0;
	} 
	fg = 1;
	if(fg){
		int ku = 320;
		for(i = 0;i <= mx;++i) if(sl[i] >= ku){
			da[++cnt] = i;bh[i] = cnt;memset(dd[cnt],0x3f,sizeof(dd[cnt]));dd[cnt][i] = 0;
			int q1 = 0;
			for(j = 1;j <= n;++j){
				if(a[j] == i) q1 = j;
				else if(q1) dd[cnt][a[j]] = min(dd[cnt][a[j]],j - q1);
			}
			q1 = n + 1;
			for(j = n;j;--j){
				if(a[j] == i) q1 = j;
				else if(q1 != n + 1) dd[cnt][a[j]] = min(dd[cnt][a[j]],q1 - j);
			}
		}
		//cerr<<mx<<"***"<<cnt<<endl;
		int tto = 0;
		for(i = 1;i <= m;++i) if(b[i].op == 2){
			//cerr<<i<<endl;
			x = b[i].x ^ lstas;y = b[i].y ^ lstas;
			//cerr<<++tto<<" "<<lstas<<" "<<x<<" "<<y<<" "<<bh[x]<<" "<<bh[y]<<" "<<dd[bh[y]][x]<<" "<<sl[x]<<" "<<sl[y]<<endl;
			if(sl[x] == 0 || sl[y] == 0){
				lstas = 0;puts("Chtholly");continue;
			}
			if(x == y) print(lstas = 0),pc('\n');
			else if(bh[x]) print(lstas = dd[bh[x]][y]),pc('\n');
			else if(bh[y]) print(lstas = dd[bh[y]][x]),pc('\n');
			else{
				int as = n + 1,q1 = 0,q2 = 0;
				x = fir[x];y = fir[y];
				while(x && y){
					if(x < y){
						if(q2) as = min(as,x - q2);
						q1 = x;x = nxt[x];
					} 
					else{
						if(q1) as = min(as,y - q1);
						q2 = y;y = nxt[y];
					}
				}
				while(x){
					if(q2) as = min(as,x - q2);
					q1 = x;x = nxt[x];
				} 
				while(y){
					if(q1) as = min(as,y - q1);
					q2 = y;y = nxt[y];
				}
				print(lstas = as);pc('\n');
			}
		}
		//cerr<<clock()<<endl;
		return 0;
	}
	//fwrite(bfu,1,bfuu - bfu,stdout);
	return 0;
}

