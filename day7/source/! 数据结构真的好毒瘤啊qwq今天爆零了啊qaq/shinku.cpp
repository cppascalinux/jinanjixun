#include<bits/stdc++.h>
using namespace std;
#define li long long
char buf[100010],*buff = buf + 100000;
#define gc (((buff == buf + 100000) ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
//#define gc getchar()
char bfu[50000010],*bfuu = bfu;
#define pc(x) (*(bfuu++) = (x))
//#define pc putchar
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
	freopen("shinku.in","r",stdin);
	freopen("shinku.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m,a[1000010],mx;
int ans[1000010][13];
struct qy{
	int l,r,id;
}b[1000010];
int cnt[1000010],tot[20];
inline bool operator < (qy q,qy w){
	return q.r == w.r ? q.l < w.l : q.r > w.r;
}
struct szsz{
	int t[1000020];
	inline void xg(int q,int x){
		for(int i = q;i <= n + 1;i += i & -i) t[i] += x;
	}
	inline int cx(int q){
		int as = 0;
		for(int i = q;i;i -= i & -i) as += t[i];
		return as;
	}
}t[13];

int pre[1000020],lst[1000020],nw[13][1000020];
int main(){
	srand(time(0));rd();
	file();
	register int i,j,k,l;
	n = read();m = read();
	for(i = 1;i <= n;++i) a[i] = read(),mx = max(mx,a[i]);
	for(i = 1;i <= m;++i){
		b[i].l = read();b[i].r = read();b[i].id = i;
	}	
	sort(b + 1,b + m + 1);
	//cerr<<clock()<<" "<<mx<<endl;
	for(i = 1;i <= n;++i){
		pre[i] = lst[a[i]];
		lst[a[i]] = i;
	}
	const int qaq = 12;
	for(i = 1;i <= mx;++i) nw[1][i] = lst[i];
	for(i = 2;i <= qaq;++i){
		for(j = 1;j <= mx;++j) nw[i][j] = min(nw[i - 1][j],lst[j + i - 1]);
	}
	for(i = 1;i <= qaq;++i) for(j = 1;j <= mx;++j){
		if(i != 1 && nw[i][j] == nw[i - 1][j]) continue;
		//if(i != 1) cerr<<i<<"***"<<nw[i - 1][j]<<" "<<-1<<endl;
		if(i != 1) t[i].xg(nw[i - 1][j] + 1,-1);
		//cerr<<i<<"&&&"<<nw[i][j]<<" "<<1<<endl;
		t[i].xg(nw[i][j] + 1,1);
	} 
	for(i = n,j = 1;i;--i){
		while(j <= m && b[j].r == i){
			int as = 0;
			for(l = 1;l <= qaq;++l){
				as += t[l].cx(b[j].l);
				//cerr<<b[j].id<<" "<<l<<":"<<b[j].l<<" "<<as<<endl;
				if(l <= qaq - 2) ans[b[j].id][l] += mx - as;
				if(l > 1 && l <= qaq - 1) ans[b[j].id][l - 1] -= 2 * (mx - as);
				if(l > 2) ans[b[j].id][l - 2] += mx - as;
			}
			++j;
		}
		for(l = 1;l <= qaq;++l){
			int gg = a[i] - l + 1;
			if(gg > 0 && nw[l][gg] > pre[i]){
				//cerr<<l<<"***"<<nw[l][gg]<<" "<<-1<<endl;
				t[l].xg(nw[l][gg] + 1,-1);
				//cerr<<l<<"&&&"<<pre[i]<<" "<<1<<endl;
				t[l].xg(pre[i] + 1,1);
				for(k = l + 1;k <= qaq;++k){
					if(nw[k][gg] > pre[i]){
						if(nw[k][gg] != nw[k - 1][gg]){
							//cerr<<k<<"&&&"<<nw[k - 1][gg]<<" "<<1<<endl;
							t[k].xg(nw[k - 1][gg] + 1,1);
							//cerr<<k<<"***"<<nw[k][gg]<<" "<<-1<<endl;
							t[k].xg(nw[k][gg] + 1,-1);
						}
					}
					else{
						//cerr<<k<<"&&&"<<nw[k - 1][gg]<<" "<<1<<endl;
						t[k].xg(nw[k - 1][gg] + 1,1);
						//cerr<<k<<"***"<<pre[i]<<" "<<-1<<endl;
						t[k].xg(pre[i] + 1,-1);
						break;
					}
				}
				for(k = l;k <= qaq;++k) nw[k][gg] = min(nw[k][gg],pre[i]);
			}
		}
	}
	for(i = 1;i <= m;++i){
		for(j = 1;j <= qaq - 2;++j) pc(ans[i][j] % 10 + '0');pc('\n');
	} 
	fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}

