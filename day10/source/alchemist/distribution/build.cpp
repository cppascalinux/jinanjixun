#include <bits/stdc++.h>
using namespace std;

vector<int>ans;

double real_tot;

int p=10;

int make(){
	int seed=rand()%100+1;
	return int(seed<=p);
}

double getu(){
	return (double)(rand()%101-50)/(double)(100);
}

double Calc(int n){
	double son=0;
	for (int i=1;i<=n;++i) son+=make();
	son+=getu()-(double)n*(0.1);
	double mother=sqrt(double(n)*(0.1)*(0.9));
	return son/mother;
}

void Build(){
	int N=10000;printf("%d ",N);
	int n=rand()%100+1;ans.push_back(n);
	for (int k=1;k<=N;++k){
		int tmp=Calc(k)*100;
		real_tot+=(double)tmp/100;
		printf("%.2f ",(double)tmp/100);
	}
	puts("");
}

int main(){
	srand((int)time(0));
	freopen("distribution.in","w",stdout);
	int T=30;
	cout<<T<<" "<<0.1<<endl;
	while(T--) Build();
	fclose(stdout);
	freopen("all.ans","w",stdout);
	for (auto v:ans) cout<<v<<endl;
	fclose(stdout);
}
