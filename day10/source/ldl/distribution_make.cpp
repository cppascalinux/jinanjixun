#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;
int main()
{
	freopen("distribution.in","w",stdout);
	srand((unsigned)time(NULL));
	int n=rand()*rand()%100+1;double p=0.1,m=10000,T=1;
	n=30;
	cout<<"1"<<endl<<p<<endl<<m<<" ";
	while(T--){
		double ans=0;
		for(int i=1;i<=m;i++){
			ans=0;
			for(int j=1;j<=n;j++){
				int rd=rand()*rand()%1000+1;
				if(rd<=p*1000)++ans;
			}
			double u=(rand()*rand()%500+1)/1000; int fz=rand()%2;
			if(fz)u=-u;
			double X=(1.0*ans+1.0*u-1.0*n*p)/sqrt(1.0*n*p*(1.0-p));
			printf("%0.2lf ",X);
		}
	}
	return 0;
}
