#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=102018;
int n,blo,m,bl[N],val[N],a[N],tag[N],siz[N];
void make_blocks(){
	for(int i=1;i<=blo+1;i++)val[i]=tag[i]=0;
	for(int i=1;i<=n;i++)val[bl[i]]^=a[i];
}
int query(int l,int r){
	int c,ret=0;
	for(int i=l;i<=min(blo*bl[l],r);i++)
		ret^=a[i]^tag[bl[i]];
	if(bl[l]!=bl[r])
		for(int i=r;i>blo*(bl[r]-1);i--)
			ret^=a[i]^tag[bl[r]];
	for(int i=bl[l]+1;i<bl[r];i++){
		ret^=val[i];
		if(siz[i]&1)ret^=tag[i];
	}
	return ret;
}
void change(int l,int r){
	int c; cin>>c;
	for(int i=l;i<=min(blo*bl[l],r);i++)
		a[i]^=c,val[bl[i]]^=c;
	if(bl[l]!=bl[r])
		for(int i=r;i>blo*(bl[r]-1);i--)
			a[i]^=c,val[bl[i]]^=c;
	for(int i=bl[l]+1;i<bl[r];i++)
		tag[i]^=c;
}
int main()
{
	freopen("save.in","r",stdin);
	freopen("save.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>n>>m; blo=sqrt(n+1);
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
		bl[i]=(i-1)/blo+1,val[bl[i]]^=a[i],++siz[bl[i]];
	while(m--){
		int opt,l,r,x; cin>>opt>>l>>r;
		if(opt==1)change(l,r);
		else if(opt==2){
			for(int i=1;i<=n;i++)a[i]^=tag[bl[i]];
			sort(a+l,a+r+1),make_blocks();
		}
		else printf("%d\n",query(l,r));
	}
	return 0;
}
