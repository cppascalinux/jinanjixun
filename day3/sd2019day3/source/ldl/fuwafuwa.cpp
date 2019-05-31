#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define int long long
const int N=2018;
int n,a,b,mod;
struct nd{int c[2],val,dep,id;}tr[N];
void insert(int now,int fa,nd x){
	if(!now){
		tr[x.id]=x; tr[x.id].dep=tr[fa].dep+1;
		tr[fa].c[x.val>tr[fa].val]=x.id;
		return;
	}
	insert(tr[now].c[x.val>tr[now].val],now,x);
}
void clear(){
	tr[1].c[0]=tr[1].c[1]=0;
	memset(tr,0,sizeof tr);
}
#undef int
int main()
{
	#define int long long
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
	int T; scanf("%lld",&T);
	while(T--){
		clear();
		scanf("%lld%lld%lld%lld",&a,&b,&mod,&n);
		nd x; tr[1].val=(a+b)%mod; tr[1].id=1; tr[1].dep=0;
		x.c[0]=x.c[1]=0; x.dep=0;
		for(int k=2;k<=n;k++){
			x.val=(a+b*k)%mod;
			x.id=k; insert(1,0,x);
		}
		cout<<tr[n].dep<<endl;
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
