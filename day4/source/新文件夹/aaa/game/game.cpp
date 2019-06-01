#include<bits/stdc++.h>
using namespace std;
int T;
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%i",&T);
	for(int i=0;i<T;i++){
		int a=0,m,n,b,c=0;
		scanf("%i%i",&n,&m);
		a+=m;
		for(int i=0;i<n;i++){
			scanf("%i",&b);
			if(b%2){
				a++;
			}else{
				c++;
			}
		}
		if(a>c&&(a%2)){
			printf("B\n");
		}else{
			printf("A\n");
		}
	}
	return 0;
}

