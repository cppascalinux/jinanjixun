#include <bits/stdc++.h>
#define ll long long
#define maxn 1000100
using namespace std;

ll a[maxn],b[maxn],n,m,L;
ll sum[maxn],dp[maxn],ans=1e15,bestcut;
int nxt[maxn],que[maxn],tim[maxn],fa[maxn];
int ranid[maxn];
vector<ll>pospos;

ll Cal(int l,int r){
	int mid=((l+r+1)>>1),flag=((r-l+1)&1);
	return sum[r]-sum[mid]-(a[mid]*flag)-sum[mid-1]+sum[l];
}

bool Check(int i,int j,int k){
	ll val1=dp[i]+Cal(i,k),val2=dp[j]+Cal(j,k);
	if (val1==val2) return tim[i]<tim[j];
	return val1<val2;
}

int Solve(ll val){
	memset(dp,0x3f,sizeof(dp));
	memset(tim,0,sizeof(tim));
	int h=1,t=1;
	que[h]=dp[0]=0,nxt[h]=1;
	for (int i=1;i<=n;++i){
		while(h<t&&nxt[h+1]<=i) h++;
		dp[i]=dp[que[h]]+Cal(que[h],i)+val;
		tim[i]=tim[que[h]]+1;fa[i]=que[h];
		while(h<=t&&Check(i,que[t],nxt[t])) t--;
		int l=nxt[t],r=n+1;
		while(l<r){
			int mid=((l+r)>>1);
			if (Check(i,que[t],mid)) r=mid;
			else l=mid+1;
		}
		if (l<=n) que[++t]=i,nxt[t]=l;
	}
	return tim[n];
}

ll Doit(){
	sort(a+1,a+1+n);
	for (int i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i];
	ll l=0,r=sum[n]+1;
	while(l<r){
		ll mid=((l+r)>>1);
		if (Solve(mid)<=m) r=mid;
		else l=mid+1;
	}
	Solve(l);
	dp[n]-l*m<ans?ans=dp[n]-l*m:0;
	return dp[n]-l*m;
}

int main(){
	freopen("post.in","r",stdin);
	freopen("post.out","w",stdout);
	srand((int)time(0));
	scanf("%lld%lld%lld",&n,&m,&L);
	for (int i=1;i<=n;++i)
		scanf("%lld",a+i),b[i]=a[i];
	for (int i=1;i<=n;++i)
		ranid[i]=i;
	int l=1,r=n,res=1;
	while(l<r){
		int lmid=l+((r-l+1)/3);
		int rmid=r-((r-l+1)/3);
		int len=b[lmid];
		for (int k=1;k<=n;++k)
		a[k]=(b[k]-len+L)%L;
		ll val1=Doit();
		len=b[rmid];
		for (int k=1;k<=n;++k)
		a[k]=(b[k]-len+L)%L;
		ll val2=Doit();
		if (val1>val2) l=lmid+1,res=rmid;
		else r=rmid-1,res=lmid;
	}
	for (int i=1;i<=n;++i){
		a[i]=(b[i]-b[res]+L)%L;
	}
	Doit();
	int pos=n,top=1;
	for (;pos;pos=fa[pos]){
		pospos.push_back((a[(fa[pos]+pos+1)/2]+b[res])%L);
		top++;
	}
	printf("%lld\n",ans);
	sort(pospos.begin(),pospos.end());
	for (auto v:pospos)
		printf("%d ",v);
}
