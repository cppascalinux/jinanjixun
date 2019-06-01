#include<bits/stdc++.h>
using namespace std;
int a[35],b[100005],s,n;
inline void ins(int x){
	for(int i=n-1;~i;i--) if(x>>i) if(!a[i]){a[i]=x,s++;break;}
	else x^=a[i];
}
int main(){
	freopen("xor.in","r",stdin),freopen("xor.out","w",stdout);
	int m,x,y,k=0;
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d%d",&y,&x);
		if(y==1) ins(x),b[++k]=x;
		else{int p=k;s=0,k=0,memset(a,0,sizeof a);for(int i=1;i<=p;i++) if(b[i]!=x) ins(b[i]),b[++k]=b[i];}
		printf("%d\n",1<<s);
	}
	return 0;
}
