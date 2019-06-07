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
	freopen("distribution.in","r",stdin);
	freopen("distribution.out","w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int t,n;
double a[100010],p;
long double f[110][110];
int fb[110];
int main(){
	srand(time(0));rd();
	file();
	int i,j,k;
	t = read();scanf("%lf",&p);
	int sm = 0;
	while(t--){
		n = read();
		//int m = read();
		for(i = 1;i <= n;++i) scanf("%lf",a + i);
		sort(a + 1,a + n + 1);
		double fc = 0,nwas = 0;
		double nwwc = 0;
		for(i = 1;i <= n;++i) fc += a[i] * a[i];
		fc /= n;
		//cerr<<fc<<endl;
		int as = 1;
		int dyl = 0;
		for(i = 1;i <= n;++i) dyl += (a[i] > 0);
		bool gf = 1;
		for(i = 1;i <= 100;++i){
			memset(f,0,sizeof(f));
			f[0][0] = 1;
			for(j = 0;j < i;++j){
				for(k = 0;k <= j;++k){
					f[j + 1][k + 1] += f[j][k] * p;
					f[j + 1][k] += f[j][k] * (1 - p);
				}
			}
			//for(j = 0;j <= i;++j) cerr<<f[i][j]<<" ";cerr<<endl;
			double aa = 1.0l / 12 - i * i * p * p;
			for(j = 0;j <= i;++j) aa += j * j * f[i][j];
			double bb = 0;
			for(j = i;j > i * p;--j) bb += f[i][j];
			//cerr<<m<<" "<<bb<<" "<<dyl<<endl;
			aa /= i * p * (1 - p);
			//cerr<<i<<":"<<aa<<endl;
			int wc = 0;
			double uu = 0,fu = 0;
			long double tmp = sqrtl(i * p * (1 - p)),t2 = i * p;
			for(j = 0,k = 1;j <= i;++j){
				double sj = (j + 0.5 - t2) / tmp;
				int sl = 0,qw = (int)(f[i][j] * n + 0.5);
				while(k <= n && a[k] <= sj){
					++sl;
					double nu =  a[k] * tmp + t2 - j;
					uu += nu;fu += nu * nu;
					++k;
				} 
				wc += abs(qw - sl);
			}
			/*if(i == 1 || abs(fc - aa) < abs(fc - nwas)){
				as = i;nwas = aa;
			}*/
			uu = abs(uu);
			//cerr<<i<<":"<<wc<<" "<<nwwc<<" "<<uu<<" "<<wc + uu<<" "<<sqrtl(fu / n)<<" "<<sqrtl(1.0l / 12)<<endl;
			if(gf || (wc / sqrtl(i) <= nwwc)){
				//if(i == 1 && wc > 30) continue;
				//if(i <= 3 && wc > 50) continue;
				//if(i <= 5 && wc > 100) continue;
				//if(i <= 10 && wc > 200) continue;
				if(uu > 100) continue;
				gf = 0;
				nwwc = wc / sqrtl(i);as = i;nwas = aa;
			}
		}
		//sm += abs(m - as);
		//cerr<<as<<" "<<m<<" "<<fc<<" "<<nwwc<<" "<<nwas<<endl;
		print(as);pc('\n');
	}
	//cerr<<sm<<endl;
	return 0;
}

