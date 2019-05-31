#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a,b,n,m,iv,g;
ll exgcd(ll a,ll b,ll& x,ll& y){
	if(b==0){
		x=1,y=0;
	} else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll ginv(ll x,ll mod){
	ll iv,tmp;
	exgcd(x,mod,iv,tmp);
	return iv<0?iv+mod:iv;
}
ll sol(ll mod,ll d,ll l,ll r,ll op=0){
	// min x->dx mod m\in[l,r]
	if(l==0)return 0;
	if(op==0&&(l-1)/__gcd(mod,d)>=r/__gcd(mod,d))return -1e9;
	if((l-1)/d<r/d)return (l+d-1)/d;
	if(2*d>mod)return sol(mod,mod-d,mod-r,mod-l,1);
	ll k=sol(d,d-mod%d,l%d,r%d,1);
	return (l+k*mod+d-1)/d;
}
ll cal1(ll a,ll b,ll l,ll r){
	if(l>r)return -1e9;
//	for(ll i=1;i<=m;++i)if((a+i*b)%m>=l&&(a+i*b)%m<=r)return printf("{%lld}",i),(a+i*b)%m;
//	return -1e9;
	a=(a%m+m)%m,b=(b%m+m)%m;
	// min x-->a+b+bx mod m<=v-->-X<=bx<=v-X;-->m-X<=bx<=m-1||0<=bx<=v-X
	l=l-(a+b)%m,r=r-(a+b)%m;
	if(l<=0&&r>=0)return (a+b)%m;
	ll x=sol(m,b,(m+l)%m,(m+r)%m);
	if(x<0)return -1e9;
	return (a+b+x*b)%m;
} 
ll gettim(ll val,ll cir){
	ll nw=((val-a+m)/g*iv%cir+cir)%cir;
	if(nw==0)nw=cir;
	return nw;
}
void sol(){
	scanf("%lld%lld%lld%lld",&a,&b,&m,&n);
	a%=m,b%=m;
	if(b==0){
		printf("%lld\n",n-1);
		return ;
	}
	ll ans=1;
	ll val=((n%m)*b+a)%m;
	g=__gcd(b,m);
	ll cir=m/g;
	iv=ginv(b/g,m/g);
	// for all t'<t:no a[t]<a[t']<=x----> a[t]>=a[t']||a[t']>x,a[t]<=x
	ll st=cal1(a,b,0,val);
//	fprintf(stderr,"{%lld,%lld(%lld,%lld,%lld)}",st,val,1ll*iv*(b/g)%(m/g),cir,g);
	while(st<val){
		ll z=cal1(st,b,st+1,val);
		if(z<0)break;
		z=(z-st+m)%m;
//		fprintf(stderr,"[%lld]",z);
		ans+=(val-st)/z;
		st+=(val-st)/z*z;
	} 	
	// in one circle.
	// a[t]==x;
	ll nw=(1ll*(val-a+m)/g*iv%cir+cir)%cir;
	if(nw==0)nw=cir;
	ans+=(n-nw)/cir-1;
//	printf("{val=%lld,ans=%lld}",val,ans);
	//for all t'<t:no x<a[t']<=a[t]---->a[t']<=x||a[t']>a[t],a[t]>x
	st=cal1(a,b,val+1,m-1);
//	fprintf(stderr,"<%lld>",st);
	if(st>=0&&gettim(st,cir)<n){
		ans++;
		ll nw=gettim(st,cir);
		while(st>val+1){
			ll z=cal1(st,b,val+1,st-1);
			if(z<0)break;
			z=(st-z+m)%m;
//			fprintf(stderr,"{%lld,%lld,%lld(%lld)}",st,val,z,nw);
			ll t=gettim((m-z+a)%m,cir);
			ll d=(st-val-1)/z;
//			printf("[%lld,%lld,%lld]\n",z,t,d);
			if(nw+t*d>n){
				d=(n-nw)/t;
				ans+=d,st-=z*d,nw+=t*d;
				break;
			} else {
				ans+=d,st-=z*d,nw+=t*d;
			}
		}
	}// in one circle.
	printf("%lld\n",ans);
}
int main(){
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--)sol();//,fprintf(stderr,"[%d]",T); 
} 
