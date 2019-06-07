#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;
double x[1000000],xx[1000000]; int m;
double fangcha(double pj){
	double res=0;
	for(int i=1;i<=m;i++)res+=(xx[i]-pj)*(xx[i]-pj);
	return res;
}
int main()
{
	freopen("distribution.in","r",stdin);
	freopen("distribution.out","w",stdout);
	srand((unsigned)time(NULL));
	int T; double p; scanf("%d%lf",&T,&p);
	while(T--){
		double ans=0,zn=0,mx=1e9;
		int pr=0; scanf("%d",&m);
		for(int i=1;i<=m;i++)scanf("%lf",&x[i]),zn+=x[i];
		zn/=m;
		for(int n=0;n<=100;n+=10){
			for(int i=1;i<=m;i++){
				ans=0;
				for(int j=1;j<=n;j++){
					int rd=rand()*rand()%100+1;
					if(rd<=p*100)ans+=1;
				}
				double u=(rand()*rand()%5+1)/10; int fz=rand()%2;
				if(fz)u=-u;
				double X=(1.0*ans+1.0*u-1.0*n*p)/sqrt(1.0*n*p*(1.0-p));
				xx[i]=X;
			}
			double th=fangcha(zn);
			if(th<mx)mx=th,pr=n;
		}
		printf("%d\n",pr);
	}fclose(stdin); fclose(stdout);
	return 0;
}
