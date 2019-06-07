#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int n,cnt=0,root[1000010],minn,p,ans;
int sum[1000010],num[1000010];
char s[1000010];
struct Tree{
	int l,r,sum;
}t[10000010];
inline void updata(int now){
	t[now].sum=t[t[now].l].sum+t[t[now].r].sum;
}
void insert(int v,int &u,int l,int r,int pos,int x){
	t[++cnt]=t[v];
	u=cnt;
	if(l==r){
		t[u].sum=x;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)insert(t[v].l,t[u].l,l,mid,pos,x);
	else insert(t[v].r,t[u].r,mid+1,r,pos,x);
	updata(u);
}
void query(int u,int v,int ll,int rr,int l,int r,int tot,int now){
	int res=t[t[v].l].sum-t[t[u].l].sum;
	//cout<<l<<" "<<r<<" "<<now<<" "<<res<<endl;
	if(l==r){
		if(l>=ll&&l<=rr&&abs(now-(tot-now-num[l]))<minn){
			minn=abs(now-(tot-now-num[l]));
			p=l;
		}
		return;
	}
	int mid=(l+r)>>1;
	if(mid>=ll&&mid<=rr&&abs((now+res-num[mid])-(tot-now-res))<minn){
		minn=abs((now+res-num[mid])-(tot-now-res));
		p=mid;
	}
	if(mid+1>=ll&&mid+1<=rr&&abs((now+res)-(tot-now-res-num[mid+1]))<minn){
		minn=abs((now+res)-(tot-res-num[mid+1]));
		p=mid+1;
	}
	if(mid<ll){
		query(t[u].r,t[v].r,ll,rr,mid+1,r,tot,now);
		return;
	}
	if(mid>rr){
		query(t[u].l,t[v].l,ll,rr,l,mid,tot,now);
		return;
	}
	if(now+res<tot-now-res-num[mid+1])query(t[u].r,t[v].r,ll,rr,mid+1,r,tot,now+res);
	else query(t[u].l,t[v].l,ll,rr,l,mid,tot,now);
}
int main(){
	freopen("Guess.in","r",stdin);
	freopen("Guess.out","w",stdout);
	//freopen("outdata.txt","w",stdout);
	scanf("%s",s);
	n=strlen(s);
	for(register int i=1;i<=n;i++){
		sum[i]=sum[i-1]+s[i-1]-'0';
		num[i]=s[i-1]-'0';
		insert(root[i-1],root[i],1,n,i,s[i-1]-'0');
	}
	//**
	/*minn=1e9;p=0;
	query(root[0],root[2],1,2,1,n,sum[2],0);
	cout<<"p="<<p<<endl;*/
	//**
	ans=-1;
	for(register int i=1;i<=n;i++){
		int l=1,r=n,mid,res=0;
		while(l<=r){
			p=0;minn=1e9;
			//cout<<"query "<<l<<" "<<r<<" "<<sum[r]-sum[l-1]<<endl;
			query(root[l-1],root[r],l,r,1,n,sum[r]-sum[l-1],0);
			//cout<<"p="<<p<<endl;
			mid=p;
			res+=num[mid];
			if(mid<i){
				l=mid+1;
			}
			else{
				r=mid-1;
			}
		}
		ans=max(ans,res);
	}
	printf("%d\n",ans);
	return 0;
}
