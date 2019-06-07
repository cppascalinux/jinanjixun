#include<iostream>
#include<cstdio>
#include<ctime>
#include<cstdlib>
using namespace std;
double random(int mod){
	int fz=rand()%2; if(!fz)fz=-1;
	return fz*(rand()*rand()%mod+rand()*rand()%mod)%mod+1;
}
int main()
{
	freopen("distribution.in","r",stdin);
	freopen("distribution.out","w",stdout);
	srand((unsigned)time(NULL));
	int T; double p; scanf("%d%lf",&T,&p);
	while(T--){
		int m; scanf("%d",&m);
		double u=0,x; long long pc=0;
		for(int i=1;i<=m;i++){
			scanf("%lf",&x);
			u=random(50)/100;
			double ans=u*u*1.0/(p*p*(1-p)*x*x);
//			printf("ans:%0.2lf\n",ans);
			pc+=(long long)ans; //cout<<"pc:"<<pc<<endl;
		}
		pc/=m; pc=(pc%100+100)%100;
		printf("%lld\n",pc);
	}fclose(stdin); fclose(stdout);
	return 0;
}
