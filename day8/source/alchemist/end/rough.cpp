#include <bits/stdc++.h>

using namespace std;

int S,n,k,len,ans;
char s[51];
int cnt[51];

void check(){
	for (int i=1;i<=len;++i)
	if (cnt[i]&1) return;
	ans++;
}

void Dfs(int v,int low){
	if (v>n) return check();
	for (int i=low;i<S-n+v;++i){
		int x=i,top=0;
		while(x)cnt[++top]+=x&1,x>>=1;
		Dfs(v+1,i+1);
		x=i,top=0;
		while(x)cnt[++top]-=x&1,x>>=1;
	}
}

int main(){
//	freopen("end.in","r",stdin);
//	freopen("std.out","w",stdout);
	scanf("%d%d",&n,&k);
	scanf("%s",s+1);
	len=strlen(s+1);
	for (int i=1;i<=len;++i)
	S=(S<<1)+s[i]-'0';
	Dfs(1,0);
	printf("%d\n",ans);
}
