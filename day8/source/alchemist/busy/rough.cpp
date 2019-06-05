#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+1;

int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}

int n,m;
int val[maxn];

void Rough(){
	int lastans=0;
	for (int k=1;k<=m;++k){
		int op=read(),x=read(),y=read();
		x^=lastans,y^=lastans;
		if (op==1){
			for (int i=1;i<=n;++i)
			if (val[i]==x) val[i]=y;
		}
		if (op==2){
			int res=n;
			bool flag=0;
			for (int i=1;i<=n;++i) if (val[i]==x){
				for (int j=1;j<=n;++j) if (val[j]==y){
					flag=1;res=min(res,abs(i-j));
				}
			}
			if (!flag){lastans=0;puts("Chtholly");continue;}
			printf("%d\n",lastans=res);
		}
	}
}

void Solve(){
	
}

int main(){
	freopen("busy.in","r",stdin);
	freopen("std.out","w",stdout);
	n=read(),m=read();
	for (int i=1;i<=n;++i)
	val[i]=read();
	if (n<=100000&&m<=100000) Rough();
	else Solve();
}
