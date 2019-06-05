#include<map>
#include<cmath>
#include<ctime>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define qmin(x,y) (x=min(x,y))
#define qmax(x,y) (x=max(x,y))
#define mp(x,y) make_pair(x,y)
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
inline int read(){
	int ans=0,fh=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		ans=ans*10+ch-'0',ch=getchar();
	return ans*fh;
}
const int maxn=1e6+100;
struct quest{
	int l,r,id;
}q[maxn];
int n,m,a[maxn],cnt[maxn],M,L,R,c[12];
char ans[maxn][12];
bool cmp(quest x,quest y){
	if(x.l/M==y.l/M) return (x.l/M&1)?x.r<y.r:x.r>y.r;
	return x.l<y.l;
}
inline void ins(int x){
	cnt[x]++;
	if(cnt[x]>1) return;
	int l1=0,l2=0,lim=max(0,x-11);
	for(int i=x-1;i>=lim;i--)
		if(cnt[i]) l1++;
		else break;
	for(int i=x+1;i<=x+11;i++)
		if(cnt[i]) l2++;
		else break;
	if(l1&&l1<=10) c[l1]--;
	if(l2&&l2<=10) c[l2]--;
	if(l1+l2+1<=10) c[l1+l2+1]++;
}
inline void del(int x){
	cnt[x]--;
	if(cnt[x]) return;
	int l1=0,l2=0,lim=max(0,x-11);
	for(int i=x-1;i>=lim;i--)
		if(cnt[i]) l1++;
		else break;
	for(int i=x+1;i<=x+11;i++)
		if(cnt[i]) l2++;
		else break;
	if(l1+l2+1<=10) c[l1+l2+1]--;
	if(l1&&l1<=10) c[l1]++;
	if(l2&&l2<=10) c[l2]++;
}
inline void work(int l,int r){
	while(L>l) ins(a[--L]);
	while(R<r) ins(a[++R]);
	while(L<l) del(a[L++]);
	while(R>r) del(a[R--]);
}
int main(){
	freopen("shinku.in","r",stdin);
	freopen("shinku.out","w",stdout);
	n=read(),m=read(),M=sqrt(n);
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=m;i++){
		int l=read(),r=read();
		q[i]=(quest){l,r,i};
	}
	sort(q+1,q+m+1,cmp),L=1,R=0;
	for(int i=1;i<=m;i++){
		work(q[i].l,q[i].r);
		for(int j=1;j<=10;j++)
			ans[q[i].id][j]='0'+c[j]%10;
	}
	for(int i=1;i<=m;i++)
		puts(ans[i]+1);
	return 0;
}











