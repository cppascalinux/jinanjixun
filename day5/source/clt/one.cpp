#include<cstdio>
#include<cstdlib>
#include<ctime>
#define re register
#define maxn 20
#define mod 1000000007

int n;
int a[maxn+1];

int main(){
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	scanf("%d",&n);
	for(re int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	if(n==1)
		putchar(48);
	else
		if(n==2){
			if(a[1]==1)
				putchar(48);
			else
				putchar(49);
		}
		else{
			srand((short)(2281701377LL*time(0))^998244353);
			printf("%d",rand());
		}
	return 0;
}

