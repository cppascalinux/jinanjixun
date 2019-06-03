#include <bits/stdc++.h>
using namespace std;
const int inf=INT_MAX;
const int maxn=51;
const int maxs=2000001;
typedef long long ll;

int read(){
	int x=0,flag=1;char ch=getchar();
	while(!isdigit(ch)&&ch!='-') ch=getchar();
	if (ch=='-') flag=-1,ch=getchar();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x*flag;
}

struct node{
	double x,y;
	int id;
	node (double a=0,double b=0,int c=0){
		x=a,y=b,id=c;
	}
	bool operator < (const node &q) const{
		return x==q.x?y<q.y:x<q.x;
	}
	node operator - (const node &q) const{
		return node(x-q.x,y-q.y);
	}
	double operator * (const node &q) const{
		return x*q.y-y*q.x;
	}
}a[maxn],sta[maxn];
int n,top;
int inc[maxs],val[maxn]; 
node cur[maxn];

inline void Update(node *a,int n){
	sta[top=1]=a[1];
	for (register int i=2;i<=n;++i){
		while(top>1&&(a[i]-sta[top])*(sta[top-1]-sta[top])<=0) top--;
		sta[++top]=a[i];
	}
	int lim=top;
	for (register int i=n;i>=1;--i){
		while(top>lim&&(a[i]-sta[top])*(sta[top-1]-sta[top])<=0) top--;
		sta[++top]=a[i];
	}
	int idS=0;
	for (int i=1;i<=top;++i)
	idS|=1<<(sta[i].id-1);
	for (int i=1;i<=n;++i)
	inc[idS]|=1<<(a[i].id-1);
}

int ans[maxn];

int main(){
	freopen("but.in","r",stdin);
	freopen("but.out","w",stdout);
	n=read();
	for (int i=1;i<=n;++i){
		int x=read(),y=read(),w=read();
		a[i]=node(x,y,i);val[i]=w;
		ans[i]=inf;
	}
	for (int S=0;S<1<<n;++S){
		int cnt=0;
		for (int i=1;i<=n;++i)
		if ((S>>(i-1))&1) cur[++cnt]=a[i];
		sort(cur+1,cur+1+cnt);
		Update(cur,cnt);
	}
	for (int S=0;S<1<<n;++S){
		int cnt=0,tem=0;
		for (int i=1;i<=n;++i)
		if ((S>>(i-1))&1) cnt++;
		for (int i=1;i<=n;++i)
		if ((inc[S]>>(i-1))&1) tem+=val[i];
		if (!tem) continue;
		ans[cnt]=min(ans[cnt],tem);
	}
	for (int i=3;i<=n;++i)
	printf("%d ",ans[i]==inf?-1:ans[i]);
}
