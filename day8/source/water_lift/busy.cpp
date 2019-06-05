#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[100001];
int fir[100001],to[100001],when[100001],nxt[100001],cnt;
inline void solve(int l,int r,int x,int y,int&ans,int&lx,int&ly,int&rx,int&ry);
inline int calc(int num){
	register int tim=0;
	while(fir[num]){
		register int p=fir[num];
		while(when[p]<tim&&nxt[p])p=nxt[p];
		if(when[p]<tim)break;
		if(to[p]==num)break;
		num=to[p];
		tim=when[p];
	}
	return num;
}
int main(){
	freopen("busy.in","r",stdin);
	freopen("busy.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	register int la=0;
	for(register int mm=1;mm<=m;mm++){
		register int opt,x,y;
		scanf("%d%d%d",&opt,&x,&y);
		x^=la;
		y^=la;
		if(opt==1){
			to[++cnt]=y;
			when[cnt]=mm;
			int p=fir[x];
			if(!p)fir[x]=cnt;
			else{
				while(nxt[p])p=nxt[p];
				nxt[p]=cnt;
			}
		}else if(opt==2){
			register int ans,lx,ly,rx,ry;
			solve(1,n,x,y,ans,lx,ly,rx,ry);
			if(ans==-1)printf("Chtholly\n"),la=0;
			else printf("%d\n",ans),la=ans;
		}
	}
}
inline void solve(int l,int r,int x,int y,int&ans,int&lx,int&ly,int&rx,int&ry){
	if(l==r){
		ans=-1;
		if(calc(a[l])==x)lx=rx=l;
		else lx=rx=-1;
		if(calc(a[r])==y)ly=ry=r;
		else ly=ry=-1;
		if(x==y&&x==calc(a[l])){
			ans=0;
			lx=rx=l;
			ly=ry=r;
		}
		return;
	}
	register int mid=(l+r)/2;
	register int lans,llx,lly,lrx,lry;
	register int rans,rlx,rly,rrx,rry;
	solve(l,mid,x,y,lans,llx,lly,lrx,lry);
	solve(mid+1,r,x,y,rans,rlx,rly,rrx,rry);
	ans=INT_MAX;
	if(lans!=-1&&lans<ans)ans=lans;
	if(rans!=-1&&rans<ans)ans=rans;
	if(llx==-1)lx=rlx;else lx=llx;
	if(lly==-1)ly=rly;else ly=lly;
	if(rrx==-1)rx=lrx;else rx=rrx;
	if(rry==-1)ry=lry;else ry=rry;
	if(lrx!=-1&&rly!=-1)ans=min(ans,rly-lrx);
	if(lry!=-1&&rlx!=-1)ans=min(ans,rlx-lry);
	if(ans==INT_MAX)ans=-1;
}
