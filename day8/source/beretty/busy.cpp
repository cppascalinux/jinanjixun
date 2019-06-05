#include<bits/stdc++.h>
#define Rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;
int a[101010],n,m,Last,T[1001010];
int main(){
	freopen("busy.in","r",stdin);
	freopen("busy.out","w",stdout);
	scanf("%d %d",&n,&m);
	Rep(i,1,n) scanf("%d",&a[i]);
	while (m--){
		int op,x,y;
		scanf("%d %d %d",&op,&x,&y);
		x^=Last; y^=Last;
		
		if (op==1){
			Rep(i,1,n) if (a[i]==x) a[i]=y;
			continue;
		}
		int cnt=0;
		Rep(i,1,n) if (a[i]==x) T[++cnt]=i;
		if (!cnt){
			printf("Chtholly\n"); Last=0; continue;
		}
		
		if (x==y){
			Last=0; printf("0\n"); continue;
		}
		int ans=21001010;
		int pt=1;
		Rep(i,1,n) if (a[i]==y){
			while (pt<cnt&&T[pt+1]<i) pt++;
			ans=min(ans,abs(T[pt]-i));
			if (pt<cnt) ans=min(ans,abs(T[pt+1]-i));
		}
		if (ans==21001010){
			printf("Chtholly\n"); Last=0; continue;
		}
		Last=ans;
		printf("%d\n",ans);
	}
}
