#include<cstdio>
int main(){
	freopen("game.in","r",stdin),freopen("game.out","w",stdout);
	int T,n,m;
	scanf("%d",&T);
	while(T--){
		int s=0,x,f=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n+1;i++){scanf("%d",&x);if(x&1) s++;else f+=!(s&1),s=0;}
		if(m) printf(!(n&1)&&f==1?"B":"A");
		else printf(n&1&&!f?"B":"A");
	}
	return 0;
}
