#include <bits/stdc++.h>
using namespace std;
const int maxn=1e4+1;

double real_x[maxn];
double cur[maxn];
int p,N;
double real_p;
double cur_tot,cur_mid,cur_sqt;

inline int make(){
	int seed=rand()%100+1;
	return int(seed<=p);
}

inline double getu(){
	return (double)(rand()%101-50)/(double)(100);
}

inline double Calc(int n){
	double son=0;
	for (register int i=1;i<=n;++i) son+=make();
	son+=getu()-(double)n*real_p;
	double mother=sqrt(double(n)*(real_p)*(1-real_p));
	return son/mother;
}

void Solve(){
	int n=0;
	scanf("%d",&N);
	double real_tot=0,real_sqt=0;
	for (register int i=1;i<=N;++i)
		scanf("%lf",real_x+i),
		real_tot+=abs(real_x[i]);
	double real_mid=real_tot/(double)N;
	for (int i=1;i<=N;++i)
	real_sqt+=(real_x[i]-real_mid)*(real_x[i]-real_mid);
	double best_gap=1e13;
	for (register int i=1;i<=100;i+=17){
		cur_tot=0;cur_sqt=0;
		for (register int k=1;k<=N;++k){
			int tmp=Calc(i)*100;
			cur[k]=(double)tmp/100;
			cur_tot+=abs((double)tmp/100);
		}
		cur_mid=cur_tot/(double)N;
		for (register int i=1;i<=N;++i)
			cur_sqt+=(cur[i]-cur_mid)*(cur[i]-cur_mid);
		double gap=abs(cur_tot-real_tot)*0.5+abs(cur_sqt-real_sqt)*0.5;
		if (gap<best_gap) n=i,best_gap=gap;
	}
	printf("%d\n",n);
}

int main(){
	freopen("distribution.in","r",stdin);
	freopen("distribution.out","w",stdout);
	srand((int)time(0));
	int T;scanf("%d",&T);
	scanf("%lf",&real_p);p=real_p*100;
	while(T--) Solve();
}
