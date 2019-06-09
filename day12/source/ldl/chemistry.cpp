#include<iostream>
#include<cstdio>
using namespace std;
const int N=1002019;
int n,k,ans,tot,now,cnt,a[50];
struct node{int to,from;}c[N];
bool fenjie(int x){
	while(x)
		a[tot++]=x&1,cnt+=x&1,x>>=1;
	if(cnt==1)return (now=k)<=n;
	return (now=(1<<tot))<=n;
}
void endwork(){//return;
	puts("-1");
	fclose(stdin); fclose(stdout);
	exit(false);
}
void print(int l,int r){//cout<<"l:"<<l<<" r:"<<r<<endl;
	if(l==r)return;
	int mid=(l+r)>>1;
	print(l,mid); print(mid+1,r);
	c[++ans]=(node){mid+1,l};
}
int main()
{
	freopen("chemistry.in","r",stdin);
	freopen("chemistry.out","w",stdout);
	cin>>n>>k;
	if(!fenjie(k))endwork();
	int x=1;
	for(int i=0;i<tot-(cnt==1);i++){
		print(x+1,x+(1<<i));
		c[++ans]=(node){x+1,1}; x+=(1<<i);
	}
	tot=0; fenjie(now-k);
	for(int i=0;i<tot;i++){
		if(!a[i])continue;
		print(x+1,x+(1<<i));
		if(x+1>n)endwork();
		c[++ans]=(node){1,x+1}; x+=(1<<i);
	}
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++)
		printf("%d %d\n",c[i].to,c[i].from);
	fclose(stdin); fclose(stdout);
	return 0;
}
