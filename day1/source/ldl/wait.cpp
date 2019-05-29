#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define int long long
const int N=102018;
int m,n,sz,top;
int th[N][2],a[N],stk[N<<2];
struct qes{int l,r,val;}q[N];
void lisan(){
	sort(stk+1,stk+top+1);
	sz=unique(stk+1,stk+top+1)-(stk+1);
	for(int i=1;i<=m;i++){
		q[i].l=lower_bound(stk+1,stk+sz+1,q[i].l)-stk;
		q[i].r=lower_bound(stk+1,stk+sz+1,q[i].r)-stk;
	}
}
int my_abs(int x){return x<0?-x:x;}
void check(){
	for(int i=0;i<=sz;i++)th[i][0]=th[i][1]=0;
	for(int i=1;i<=m;i++){
		int col=q[i].val==-1?a[i]:q[i].val;
		++th[q[i].l][col]; --th[q[i].r+1][col];
	}
	int t0=0,t1=0;
	for(int i=1;i<=sz;i++){
		t0+=th[i][0]; t1+=th[i][1];
		if(my_abs(t0-t1)>1)return;
	}
	for(int i=1;i<=m;i++){
		int col=q[i].val==-1?a[i]:q[i].val;
		printf("%lld ",col);
	}
	exit(0);
}
void dfs(int step){
	if(step>m)return check(),void();
	if(q[step].val!=-1)dfs(step+1);
	a[step]=1; dfs(step+1);
	a[step]=0; dfs(step+1);
}
#undef int
int main()
{
	#define int long long
	freopen("wait.in","r",stdin);
	freopen("wait.out","w",stdout);
	cin>>m>>n;
	for(int i=1;i<=m;i++){
		cin>>q[i].l>>q[i].r>>q[i].val;
		stk[++top]=q[i].l,stk[++top]=q[i].r;
		stk[++top]=q[i].l+1,stk[++top]=q[i].r+1;
	}
	lisan();
	if(m>30)return cout<<"-1",0;
	dfs(1);
	cout<<"-1"<<endl;
	fclose(stdin); fclose(stdout);
	return 0;
}
