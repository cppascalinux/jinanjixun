#include<iostream>
#include<cstdio>
#include<set>
using namespace std;
const int N=2018;
int n,m,q,ans,th,tm,top,col[N],map[N][N],stk[N];bool xuan[N];
void dfs(int x){
	col[x]=tm; ++th;
	ans=max(ans,th);
	for(int i=0;i<n;i++)
		if(col[i]<tm && map[x][i])dfs(i);
}
void tongji(){
	int res=0;
	for(int i=1;i<=n;i++)
		if(xuan[i])res^=stk[i];
	if(col[res]<tm)col[res]=tm,++ans;
}
void dfs1(int x){
	if(x>top)return tongji(),void();
	xuan[x]=1; dfs1(x+1);
	xuan[x]=0; dfs1(x+1);
}
set<int> S;
void work1(){
	
	while(q--){
		int opt,x; ans=0;++tm;
		scanf("%d%d",&opt,&x);
		if(opt==1)S.insert(x);
		else S.erase(x);
		top=0;
		for(set<int>::iterator it=S.begin();it!=S.end();++it)
			stk[++top]=*it;
		dfs1(1);
		printf("%d\n",ans);
	}
}
int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	scanf("%d%d",&m,&q);
	n=1<<m;
	if(n<=13){
		while(q--){
			int opt,x; ans=0;++tm;
			scanf("%d%d",&opt,&x);
			opt%=2;
			for(int i=0;i<n;i++)
				if(i^x<n && i^x>=0)
					map[i][i^x]=map[i^x][i]=opt;
			for(int i=0;i<n;i++)
				if(col[i]<tm)th=0,dfs(i);
			printf("%d\n",ans);
		}
	}
	else{
		work1();
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
