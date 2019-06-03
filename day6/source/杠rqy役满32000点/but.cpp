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
	freopen("but.in","r",stdin);
	freopen("but.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n;
struct node{
	li x,y;
	node(li _x = 0,li _y = 0){x = _x;y = _y;}
}a[55],nw;
inline node operator + (node q,node w){
	return node(q.x + w.x,q.y + w.y);
}
inline node operator - (node q,node w){
	return node(q.x - w.x,q.y - w.y);
}
inline li operator * (node q,node w){
	return q.x * w.y - q.y * w.x;
}
inline bool operator == (node q,node w){
	return q.x == w.x && q.y == w.y;
}
inline bool operator <= (node q,node w){
	return q.x < w.x || (q.x == w.x && q.y <= w.y);
}
int as[55];
int vl[55],f[55][55][55];
int jj[55][55];
int gx[55][55];
inline bool cmp(int x,int y){
	if(a[x] == nw) return 1;
	if(a[y] == nw) return 0;
	if(a[x].x < nw.x && a[y].x >= nw.x) return 0;
	if(a[y].x < nw.x && a[x].x >= nw.x) return 1;
	return (a[x] - nw) * (a[y] - nw) > 0;
}
inline bool jiao(node a,node b,node c,node d){
	return 1.0l * ((c - a) * (d - a)) * ((c - b) * (d - b)) < 0 && 1.0l * ((a - c) * (b - c)) * ((a - d) * (b - d)) < 0;
}
int main(){
	srand(time(0));rd();
	file();
	int i,j,k,l,u,v;
	n = read();
	for(i = 1;i <= n;++i){
		a[i].x = read();a[i].y = read();vl[i] = read();
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= n;++j) jj[i][j] = j;
		nw = a[i];
		//if(i == 2) cerr<<a[5].x<<" "<<a[1].x<<" "<<" "<<nw.x<<" "<<cmp(5,1)<<endl;
		sort(jj[i] + 1,jj[i] + n + 1,cmp);
		jj[i][n + 1] = i;
		//for(j = 1;j <= n + 1;++j) cerr<<jj[i][j]<<" ";cerr<<endl;
	}
	memset(as,0x3f,sizeof(as));
	for(i = 1;i <= n;++i) for(j = 1;j <= n;++j) if(i != j) for(k = 1;k <= n;++k){
		if(k == j){
			if(a[i].x > a[k].x) gx[i][j] -= vl[k];
		}
		else if(k == i) gx[i][j] += vl[k];
		else if(jiao(a[i],a[j],a[k],node(a[k].x + 1,-10000000))){
			if(a[i].x < a[j].x) gx[i][j] += vl[k];
			else gx[i][j] -= vl[k];
		}
	}
	//cerr<<n<<endl;
	//for(i = 1;i <= n;++i){
	//	for(j = 1;j <= n;++j) cerr<<gx[i][j]<<" ";cerr<<endl;
	//}
	for(i = 1;i <= n;++i){
		memset(f,0x3f,sizeof(f));
		for(j = 2;j <= n;++j) f[1][1][j] = vl[i] + gx[i][jj[i][j]];
		for(j = 1;j <= n;++j) for(l = 1;l <= n;++l) if(a[i] <= a[jj[i][l]]) for(u = l + 1;u <= n + 1;++u) if(a[i] <= a[jj[i][u]]){
			//if(i == 5 && j <= 3) cerr<<i<<":"<<j<<" "<<jj[i][l]<<" "<<jj[i][u]<<" "<<f[j][l][u]<<endl;
			for(v = u + 1;v <= n + 1;++v) if(a[i] <= a[jj[i][v]] && (a[jj[i][v]] - a[jj[i][u]]) * (a[jj[i][l]] - a[jj[i][u]]) > 0){
				f[j + 1][u][v] = min(f[j + 1][u][v],f[j][l][u] + gx[jj[i][u]][jj[i][v]]);
				//if(i == 5 && j == 2 && u == 4 && v == 6) cerr<<jj[i][l]<<"(**)"<<gx[5][1]<<" "<<f[j - 1][1][l]<<" "<<f[j][l][u]<<" "<<gx[jj[i][u]][jj[i][v]]<<endl;
			}
		} 
		for(j = 3;j <= n;++j) for(l = 1;l <= n;++l) as[j] = min(as[j],f[j][l][n + 1]);
		//for(l = 1;l <= n;++l) if(f[3][l][n + 1] == 0) cerr<<i<<" "<<l<<" "<<jj[i][l]<<endl;
	}
	for(i = 3;i <= n;++i) print(as[i] >= 1e8 ? -1 : as[i]),pc(' ');
	return 0;
}
